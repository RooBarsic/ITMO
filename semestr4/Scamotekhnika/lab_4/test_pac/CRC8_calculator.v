`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05.06.2019 14:43:06
// Design Name: 
// Module Name: CRC8_calculator
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


module CRC8_calculator(
    input clk,
    input rst,
    input [7:0] data,
    input new_data,
    output reg busy,
    output reg [7:0] result_crc8
);

// сигнал new_data - должен быть 1 на всём промежутке обработки данных
// чтобы обеспечить что данные не изменятся в ходе их обработки
localparam IDLE = 2'b00;
localparam DO_XOR = 2'b01;
localparam DO_SHIFT = 2'b10;
localparam FINISH = 2'b11;

reg inside_access;
reg [7:0] polynom = 8'b11010001;
reg [7:0] buff;
reg reseted;
reg [7:0] state; 
reg [7:0] id;

always@(posedge clk) begin
    //$display(" ~ %%%%% CRC new_data = %b inside_access = %b", new_data, inside_access); 
    if(rst) begin
        buff <= 0;
        busy <= 0;
        reseted <= 1;
        inside_access <= 1;
        state <= IDLE;
        id <= 0;
     end
    else if(new_data == 0) inside_access <= 1;
    else if((new_data == 1) && (inside_access == 1)) begin
        case(state)
            IDLE : begin
                //$display("  reseted = %d busy = %d", reseted, busy);
                if(reseted == 1) begin
                    reseted <= 0;
                    buff <= data;
                    busy <= 1;
                    state <= FINISH;
                 end
                else begin
                    id <= 7; 
                    busy <= 1;
                    state <= DO_XOR;
                 end
             end
            DO_XOR : begin
                //$display(" %%% CRC  id = %d buff = %b", id, buff);
                if(buff[7] == 1) begin
                    //$display(" %%% CRC  do xor ");
                    buff <= buff ^ polynom;
                 end
                state <= DO_SHIFT;
             end
            DO_SHIFT : begin
                buff[7] <= buff[6];
                buff[6] <= buff[5];
                buff[5] <= buff[4];
                buff[4] <= buff[3];
                buff[3] <= buff[2];
                buff[2] <= buff[1];
                buff[1] <= buff[0];
                buff[0] <= data[id];
                if(id == 0) state <= FINISH;
                else begin
                    id = id - 1;
                    state <= DO_XOR;
                 end
             end
            FINISH : begin
                busy <= 0;
                inside_access <= 0;
                state <= IDLE;
                result_crc8 <= buff;
                //$display(" %%% CRC   resultt = %b", buff);
             end
        endcase
    end
end
endmodule

























