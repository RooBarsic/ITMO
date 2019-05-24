`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 21.05.2019 00:01:52
// Design Name: 
// Module Name: sqrt3_tb
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


module sqrt3_tb;
reg clk_c_i;
reg rst_c_i;
reg start_c_i;
reg [7:0] x_i;
wire res_o;
wire [7:0] s_o;

sqrt3 dut(.clk_c(clk_c_i),
		  .rst_c(rst_c_i),
		  .start_c(start_c_i),
		  .x(x_i),
		  .busy(res_o),
		  .result(s_o)
);

integer i, xx, bb, kol_ok, kol_error;

initial
	begin
		$display("Start testing ");
		// $monitor("c = %b, res = %d, r = %b, time = %0d", clk_c_i, s_o, res_o, $time);
		kol_ok = 0;
		kol_error = 0;
		for(xx = 0; xx <= 255; xx = xx + 1) begin
            clk_c_i = 0; rst_c_i = 1; start_c_i=1; x_i = xx;
            #10 clk_c_i = 1; rst_c_i = 1;
            #10 clk_c_i = 0; rst_c_i = 0;
            for (i = 0; i < 300; i = i + 1) begin
                #5 clk_c_i = 1;
                #5 clk_c_i = 0;
            end
            
            bb = 0;
            while(bb * bb * bb <= xx) begin
                bb = bb + 1;
            end
            bb = bb - 1;
            
            if(bb != s_o) begin 
                kol_error = kol_error + 1; 
                $display("~~~ Error number x = %d, real result = %d, expected result = %d, time = %0d", xx, s_o, bb, $time);
            end 
            else begin
                kol_ok = kol_ok + 1;
                $display("~~~ OK number x = %d, real result = %d, expected result = %d, time = %0d", xx, s_o, bb, $time);
            end
	   end
	   $display(" ~~~ Testing is finished ");
	   $display(" ~~~ kol_OK = %d, kol_Error = %d ", kol_ok, kol_error);
	   #10 $stop;
	end
endmodule 




