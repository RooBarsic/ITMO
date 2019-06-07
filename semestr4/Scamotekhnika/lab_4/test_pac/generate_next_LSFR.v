`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04.06.2019 19:26:32
// Design Name: 
// Module Name: generate_next_LSFR
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


module generate_next_LSFR(
    input clk,
    input rst,
    input outside_access,
    input [7:0] base_number,
    output reg busy,
    output reg [7:0] generated_number
    );
reg [7:0] num;
reg state;
reg inside_access;
localparam CALC = 1'b0;
localparam SAVE = 1'b1;
always@(posedge clk) begin
    //$display(" ~ LSFR  rst = %b busy = %b inside_access = %b outside_access = %b", rst, busy, inside_access, outside_access);
    if(rst) begin 
        num <= base_number;
        state <= CALC;
        inside_access <= 1;
        busy <= 0;
    end
    else if((outside_access == 1) && (inside_access == 1)) 
        case(state) 
          CALC : begin
             //  Last BUG    ??????????????????   $display(" ================= LSFR first num_b = %b num_d = %d", num, num); 
             state <= SAVE;
             busy <= 1;
             num[0] <= (num[0] ^ num[1] ^ num[2] ^ num[4] ^ num[7]);
             num[1] <= num[0];
             num[2] <= num[1];
             num[3] <= num[2];
             num[4] <= num[3];
             num[5] <= num[4];
             num[6] <= num[5];
             num[7] <= num[6];
           end
          SAVE : begin
             //$display(" next num = %b", num);
             busy <= 0;
             inside_access <= 0;
             state <= CALC;
             generated_number <= num;
           end
        endcase
     else if(outside_access == 0) inside_access <= 1;
end
endmodule





















