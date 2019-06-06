`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05.06.2019 17:42:57
// Design Name: 
// Module Name: control_logic
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module control_logic(
    input rst,
    input clk,
    input start_stop_testing,
    input start_calculation,
    input get_lsfr_base_from_data,
    input [7:0] input_data,
    output reg busy,
    output reg [3:0] number_of_testing,
    output reg [7:0] result
);

reg lsfr_rst;
reg lsfr_access;
reg [7:0] lsfr_base_number;
wire lsfr_busy;
wire [7:0] lsfr_result;
generate_next_LSFR div1(
    .clk(clk),
    .rst(lsfr_rst),
    .outside_access(lsfr_access),
    .base_number(lsfr_base_number),
    .busy(lsfr_busy),
    .generated_number(lsfr_result)
);

reg sqrt3_rst;
reg sqrt3_start;
reg [7:0] sqrt3_data;
wire sqrt3_busy;
wire [7:0] sqrt3_result;
sqrt3 div2(
    .clk_c(clk),
    .rst_c(sqrt3_rst),
    .start_c(sqrt3_start),
    .x(sqrt3_data),
    .result(sqrt3_result),
    .busy(sqrt3_busy)
);

reg crc_rst;
reg [7:0] crc_data;
reg crc_new_data;
wire crc_busy;
wire [7:0] crc_result;
CRC8_calculator driv3(
    .clk(clk),
    .rst(crc_rst),
    .data(crc_data),
    .new_data(crc_new_data),
    .busy(crc_busy),
    .result_crc8(crc_result)
);

reg testing;
reg testing_access;
reg calc_access;
reg [3:0] kol_testing;
reg [8:0] id_test;

reg [7:0] stage;
localparam WAITING = 4'b0000;
localparam CALC_IDLE = 4'b0001;
localparam TESTING_IDLE = 4'b0010;
localparam SET_CALC_ACCESS = 4'b0011;
localparam CALC_WAITING = 4'b0100;
localparam TESTING_GENERATE_NUMBER = 4'b0101;
localparam TESTING_WAITING_GENERATOR = 4'b0110;
localparam TESTING_WAITING_SQRT3 = 4'b0111;
localparam TESTING_WAITING_CRC = 4'b1000;
localparam TESTING_FINISH = 4'b1001;

always@(posedge clk) begin
    $display(" ~~~~~~~~~~~~ control logic info : id_test = %d", id_test);
    if(rst) begin
        stage <= WAITING;
        
        testing <= 0;
        testing_access <= 1;
        calc_access <= 1;
        kol_testing <= 0;
        id_test <= 0;
        
        busy <= 0;
        number_of_testing <= 0;
        result <= 0;
        
        lsfr_rst <= 1;
        lsfr_access <= 0;
        lsfr_base_number <= 0;
    
        sqrt3_rst <= 1;
        sqrt3_start <= 0;
        sqrt3_data <= 0;
        
        crc_rst <= 1;
        crc_data <= 0;
        crc_new_data <= 0;

     end
    else begin
        sqrt3_rst <= 0;
        crc_rst <= 0;
        lsfr_rst <= 0;
        if((start_calculation == 1) && (calc_access == 1) && (busy == 0)) begin
            calc_access <= 0;
            busy <= 1;
            stage <= CALC_IDLE;
         end
        else if(start_calculation == 0) calc_access <= 1;
        
        if((start_stop_testing == 1) && (testing_access == 1)) begin
            $display(" testing ... ");
            testing_access <= 0;
            if(testing == 0) begin
                busy <= 1;
                stage <= TESTING_IDLE;
             end
            else begin
                busy <= 0;
                result <= 0;
                
                lsfr_rst <= 0;
                lsfr_access <= 0;
                lsfr_base_number <= 0;
            
                sqrt3_rst <= 0;
                sqrt3_start <= 0;
                sqrt3_data <= 0;
                
                crc_rst <= 0;
                crc_data <= 0;
                crc_new_data <= 0;
                stage <= WAITING;
             end
         end
        else if(start_stop_testing == 0) testing_access <= 1;
     end
    case(stage)
        WAITING : begin
            //$display(" %%% stage = WAITING");
         end
        CALC_IDLE : begin
            //$display(" %%% stage = CALC_IDLE");
            sqrt3_rst <= 1;
            stage <= SET_CALC_ACCESS;
         end
        SET_CALC_ACCESS : begin 
            //$display(" %%% stage = SET_CALC_ACCESS   resultt = %b input = %b", sqrt3_result, input_data);
            sqrt3_rst <= 0;
            if(sqrt3_busy == 0) begin
                sqrt3_start <= 1;
                sqrt3_data <= input_data;
             end
            else if(sqrt3_busy == 1) stage <= CALC_WAITING;
         end
        CALC_WAITING : begin
            //$display(" %%% stage = CALC_WAITING  resultt = %b input = %b", sqrt3_result, input_data);
            if(sqrt3_busy == 0) begin
                sqrt3_start <= 0;
                result <= sqrt3_result;
                busy <= 0;
                stage <= WAITING;
             end
         end
        TESTING_IDLE : begin
            $display(" %%% stage = TESTING_IDLE");
            id_test <= 256;
            crc_rst <= 1;
            lsfr_rst <= 1;
            if(get_lsfr_base_from_data) lsfr_base_number <= input_data;
            else lsfr_base_number <= 0;
            stage <= TESTING_GENERATE_NUMBER;
         end
        TESTING_GENERATE_NUMBER : begin
            $display(" %%% stage = TESTING_GENERATE_NUMBER     id_test = %d  next_num = %b", id_test, lsfr_result);
            lsfr_rst <= 0;
            lsfr_access <= 1;
            if(lsfr_busy == 1) begin 
                id_test <= id_test - 1;
                stage <= TESTING_WAITING_GENERATOR;
             end
         end
        TESTING_WAITING_GENERATOR : begin
            $display(" %%% stage = TESTING_WAITING_GENERATOR  id_test = %d  next_num = %b  busy = %b", id_test, lsfr_result, lsfr_busy);
            if(lsfr_busy == 0) begin
                lsfr_access <= 0;
                sqrt3_rst <= 0;
                sqrt3_start <= 1;
                sqrt3_data <= lsfr_result;
                if(sqrt3_busy == 1) stage <= TESTING_WAITING_SQRT3;
             end
         end
        TESTING_WAITING_SQRT3 : begin
            $display(" %%% stage = TESTING_WAITING_SQRT3");
            if(sqrt3_busy == 0) begin
                sqrt3_start <= 0;
                crc_new_data <= 1;
                crc_rst <= 0;
                crc_data <= sqrt3_result;
                $display("    num = %b sqrt = %b", lsfr_result, sqrt3_result);
                stage <= TESTING_WAITING_CRC;
             end
         end
        TESTING_WAITING_CRC : begin
            crc_rst <= 0;
            $display(" %%% stage = TESTING_WAITING_CRC");         
            if(crc_busy == 0) begin
                crc_new_data <= 0;
                result <= crc_result;
                if(id_test == 0) begin // Finish
                    kol_testing <= kol_testing + 1;
                    stage <= TESTING_FINISH;
                 end
                else stage <= TESTING_GENERATE_NUMBER; 
             end
        end
       TESTING_FINISH : begin
            $display(" %%% stage = TESTING_FINISH");
            number_of_testing <= kol_testing;
            stage <= WAITING;
            busy <= 0;
        end
     endcase
    
end    
endmodule





























