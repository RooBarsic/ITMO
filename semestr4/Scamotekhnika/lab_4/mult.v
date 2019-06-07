`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 20.05.2019 23:58:44
// Design Name: 
// Module Name: mult
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


module mult(
	input clk_i,
	input rst_i,
	input [7:0] a_bi,
	input [7:0] b_bi,
	input start_i,
	output busy_o,
	output reg [15:0] y_bo
);

localparam IDLE = 1'b0;
localparam WORK = 1'b1;

reg [2:0] ctr;
wire [2:0] ctr_next, end_step;
wire [7:0] part_sum;
wire [15:0] shifted_p;
reg [7:0] a, b;
reg [15:0] part_res;
reg state;

assign part_sum = a & {8{b[ctr]}};
assign shifted_p = part_sum << ctr;
assign ctr_next = ctr + 1;
assign end_step = (ctr == 3'h7);
assign busy_o = state;

//always@(negedge clk_i)
    //$display(" mul clk == negative, busy = %d ", busy_o );

always@(posedge clk_i) begin
    //$display(" mul clk == positiv  busy = %d ", busy_o );
	if(rst_i) begin
		ctr <= 0;
		part_res <= 0;
		y_bo <= 0;
		state <= IDLE;
	end else begin
		case(state)
			IDLE:
				if(start_i) begin
					state <= WORK;
					a <= a_bi;
					b <= b_bi;
					ctr <= 0;
					part_res <= 0;
				end
			WORK: begin
				if(end_step) begin
					state <= IDLE;
					y_bo <= part_res;
				end
				part_res = part_res + shifted_p;
				ctr <= ctr + 1;
			end
		endcase
	end
end
endmodule 
