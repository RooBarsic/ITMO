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
    input testing_button_status,
    input sqrt3_button_status,
    input get_lsfr_base_from_data,
    input [7:0] input_data,
    output reg busy,
    output reg [3:0] number_of_testing,
    output reg [7:0] result
);

reg lsfr_rst;
reg lsfr_start;
reg [7:0] lsfr_base_number;
wire lsfr_busy;
wire [7:0] lsfr_result;
generate_next_LSFR div1(
    .clk(clk),
    .rst(lsfr_rst),
    .outside_access(lsfr_start),
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
reg crc_start;
wire crc_busy;
wire [7:0] crc_result;
CRC8_calculator driv3(
    .clk(clk),
    .rst(crc_rst),
    .data(crc_data),
    .new_data(crc_start),
    .busy(crc_busy),
    .result_crc8(crc_result)
);

reg testing_access;
reg sqrt3_access;
reg [3:0] kol_testing = 0;
reg [8:0] id_test;

reg [7:0] commutator;
localparam WAITING = 4'b0000;
localparam CALC_SQRT = 4'b0001;
localparam DO_TESTING = 4'b0010;

reg [7:0] sqrt_stage;
localparam SQRT_INIT = 4'b0000;
localparam WAITING_SQRT = 4'b0001;

reg [7:0] testing_stage;
localparam TEST_INIT_BEGIN = 4'b0000;
localparam TEST_INIT_FINISH = 4'b0001;
localparam TEST_GENERATE_NUMBER = 4'b0010;
localparam TEST_WAIT_GENERATOR = 4'b0011;
localparam TEST_CALC_SQRT3 = 4'b0100;
localparam TEST_WAIT_SQRT3 = 4'b0101;
localparam TEST_CALC_CRC = 4'b0110;
localparam TEST_WAIT_CRC = 4'b0111;
localparam TEST_FINISH = 4'b1000;

always@(posedge clk) begin
    //$display(" ~~~~~~~~~~~~ control logic info : id_test = %d", id_test);
    number_of_testing <= kol_testing;
    if(rst) begin
        busy <= 0;
        result <= 0;
        commutator <= WAITING;
        
        testing_access <= 1;
        sqrt3_access <= 1;
        
        lsfr_rst <= 1;
        lsfr_start <= 0;
        
        sqrt3_rst <= 1;
        sqrt3_start <= 0;
        
        crc_rst <= 1;
        crc_start <= 0;
     end
    else begin
        lsfr_rst <= 0;
        sqrt3_rst <= 0;
        crc_rst <= 0;
     end
    
    if((sqrt3_access == 1) && (sqrt3_button_status == 1) && (busy == 0)) begin
        // начинаем шитать sqrt3
        busy <= 1;
        sqrt3_access <= 0;
        commutator <= CALC_SQRT;
        sqrt_stage <= SQRT_INIT;
     end
    else if((testing_access == 1) && (testing_button_status == 1)) begin
        if(busy == 0) begin
            // начинаем тест
            busy <= 1;
            testing_access <= 0;
            commutator <= DO_TESTING;
            testing_stage <= TEST_INIT_BEGIN;
         end
        else if((commutator == DO_TESTING) && (testing_stage != TEST_FINISH)) begin
            // останавливаем тест
            busy <= 0;
            testing_access <= 0;
            commutator <= WAITING;
         end
     end
    
    if((sqrt3_button_status == 0) && (busy == 0)) sqrt3_access <= 1; // даём разрешение на подсчёт sqrt3
    if((testing_button_status == 0) && (busy == 0)) testing_access <= 1; // даём разрешение на тестирование
    
    case(commutator)
        WAITING : begin
            // ждём команды от пользователя
         end
        CALC_SQRT : begin
            // дали команду на подсчёт sqrt3
            //$display(" ~~~ ## CALC_SQRT ");
            case(sqrt_stage)
                SQRT_INIT : begin
                    // инициализация для подсчёта sqrt3
                    //$display(" ~~~ ## # SQRT INIT");
                    if(sqrt3_start == 0) begin
                        sqrt3_data <= input_data;
                        sqrt3_start <= 1;
                     end
                    else if(sqrt3_busy == 1) sqrt_stage <= WAITING_SQRT;
                 end
                WAITING_SQRT : begin
                    // ждём окончания вычислений
                    //$display(" ~~~ ## # SQRT WAITING ");
                    if(sqrt3_busy == 0) begin
                        //$display(" ~~~ ## # % SQRT busy = 0 data = %d sqrt_result = %d", input_data, sqrt3_result);
                        sqrt3_start <= 0;
                        busy <= 0;
                        commutator <= WAITING;
                        result <= sqrt3_result;
                     end
                 end
             endcase
         end
        DO_TESTING : begin
            // дали команду на тестирование
            //$display(" ~~~ @@ DO_TESTING ");
            case(testing_stage)
                TEST_INIT_BEGIN : begin
                    //$display(" ~~~ @@ @ TEST_INIT_BEGIN");
                    id_test <= 255; /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    crc_rst <= 1;
                    lsfr_rst <= 1;
                    lsfr_start <= 0;
                    if(get_lsfr_base_from_data) lsfr_base_number <= input_data;
                    else lsfr_base_number <= 1;
                    testing_stage <= TEST_INIT_FINISH;
                 end
                TEST_INIT_FINISH : begin
                    //$display(" ~~~ @@ @ TEST_INIT_FINISH");
                    crc_rst <= 0;
                    lsfr_rst <= 0;
                    testing_stage <= TEST_GENERATE_NUMBER;
                 end
                TEST_GENERATE_NUMBER : begin
                    //$display(" ~~~ @@ @ TEST_GENERATE_NUMBER");
                    if(lsfr_start == 0) lsfr_start <= 1;
                    else if(lsfr_busy == 1) testing_stage <= TEST_WAIT_GENERATOR;
                 end
                TEST_WAIT_GENERATOR : begin
                    //$display(" ~~~ @@ @ TEST_WAIT_GENERATOR");
                    if(lsfr_busy == 0) begin
                        //$display(" ~~~ @@ @ % TEST GENERATOR busy = 0 ");
                        lsfr_start <= 0;
                        testing_stage <= TEST_CALC_SQRT3;
                     end
                 end
                TEST_CALC_SQRT3 : begin
                    //$display(" ~~~ @@ @ TEST_CALC_SQRT");
                    sqrt3_data <= lsfr_result;
                    if(sqrt3_start == 0) sqrt3_start <= 1;
                    else if(sqrt3_busy == 1) testing_stage <= TEST_WAIT_SQRT3;
                 end
                TEST_WAIT_SQRT3 : begin
                    //$display(" ~~~ @@ @ TEST_WAIT_SQRT");
                    if(sqrt3_busy == 0) begin
                        //  Last BUG    ??????????????????   $display(" KUKUKUKUKUKU ~~~ @@ @ % TEST SQRT FINISH     x = %d sqrt_result = %d ", lsfr_result, sqrt3_result);
                        sqrt3_start <= 0;
                        testing_stage <= TEST_CALC_CRC;
                     end
                 end
                TEST_CALC_CRC : begin
                    //$display(" ~~~ @@ @ TEST_CALC_CRC   crc_start = %d crc_busy = %d", crc_start, crc_busy);
                    crc_data <= sqrt3_result;
                    if(crc_start == 0) crc_start <= 1;
                    else if(crc_busy == 1) testing_stage <= TEST_WAIT_CRC;
                 end
                TEST_WAIT_CRC : begin
                    //$display(" ~~~ @@ @ TEST_WAIT_CRC");
                    if(crc_busy == 0) begin
                        //  Last BUG    ??????????????????   $display(" ~~~ @@ @ % TEST CRC FINISH");
                        crc_start <= 0;
                        result <= crc_result;
                        if(id_test == 0) begin
                            testing_stage <= TEST_FINISH;
                            kol_testing <= kol_testing + 1;
                         end
                        else begin
                            id_test <= id_test - 1;
                            testing_stage <= TEST_GENERATE_NUMBER;
                         end
                     end
                 end
                TEST_FINISH : begin
                    $display(" ~~~ @@ @ TEST_FINISH");
                    busy <= 0;
                    number_of_testing <= kol_testing;
                    result <= crc_result;
                    commutator <= WAITING;
                 end
             endcase
         end
     endcase
end    
endmodule





























