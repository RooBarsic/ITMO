`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 21.05.2019 00:00:19
// Design Name: 
// Module Name: sqrt3
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

module sqrt3(
	input clk_c,
	input rst_c,
	input start_c,
	input [7:0] x,
	output reg [7:0] result,
	output reg busy
);

localparam STAGE_0 = 2'b00;
localparam STAGE_1 = 2'b01;
localparam STAGE_2 = 2'b10;
localparam FINISH = 2'b11;
reg [1:0] state;

reg [7:0] y;

reg mul_rst;
reg mul_start;
reg [15:0] mul_a;
reg [15:0] mul_b;
wire mul_busy;
wire [15:0] mul_result;


mult multiplay(
    .clk_i(clk_c),
	.rst_i(mul_rst),
	.a_bi(mul_a),
	.b_bi(mul_b),
	.start_i(mul_start),
	.busy_o(mul_busy),
	.y_bo(mul_result)
);

integer i, access;

always@(posedge clk_c) begin    
    $display(" $$$ sqrt3 data : rst = %b, acces = %3b, start = %b, x = %b, busy = %b, i = %d", rst_c, access, start_c, x, busy, i);
    if (rst_c == 1) begin
           //$display( " ## new rst " );
           busy <= 0;
           state <= STAGE_0;
           y <= 6;
           result <= 0;
           mul_rst <= 0;
           i <= 0;
           access <= 1;
    end 
	else if((access == 1) && (busy == 0) && (start_c == 1)) begin
        //$display(" !!!! ## result <= 0,  access = %d, busy = %d, satart = %d result = %d", access, busy, start_c, result);
        busy <= 1;
        state <= STAGE_0;
        y <= 6;
        result <= 0;
        mul_rst <= 0;
        i <= 0;
        access <= 0;
    end	 
    else if((access == 0) && (start_c == 0))
        access <= 1;
	else if((busy == 1) && (i <= 1)) begin
	       if(i == 0) mul_rst <= 0;
	       //$display(" %%%%% mul_rst == 1, i = %d ", i);
	       i <= i + 1;
     end  
	else if((busy == 1) && (start_c == 1)) begin
		case(state)
			STAGE_0: if (start_c) begin
					//$display(" ## state = STAGE_0,  x = %d ", x);
					// calc y^2 = y * y
					i <= 0;
					mul_rst <= 1; 
					mul_a <= y; 
					mul_b <= y;
					mul_start <= 1;
					
					state <= STAGE_1;
					
					//$display(" ## from STAGE_0 go to state = STAGE_1 ");
			    end
			
			STAGE_1: if(mul_busy == 0) begin
				    //$display(" ## state = %d, x = %d ", state, x);
					// calc y^3 = y^2 * y 
					//$display(" ##  y_bo = %d ", mul_result);
					
					i <= 0;
					mul_rst <= 1; 
					mul_start <= 1;
					mul_a <= mul_result; 
					mul_b <= y;
					
					state <= STAGE_2;
					
					//$display(" ## from STAGE_1 go to state = STAGE_2 "); 
				  end 
				else begin 
				    //$display(" ## waiting in state = STAGE_1     real_state = %d", state);
				  end
				
			STAGE_2 : if(mul_busy == 0) begin
			    //$display(" ## state = %d  mul_result = %d  x = %d y = %d", state, mul_result, x, y);
				if (mul_result <= x) begin
                    y <= y;
                    busy <= 0;
    			    access <= 0;
                    result <= y;
                    state <= FINISH;
                    //$display(" ## from STAGE_2 go to state = FINISH "); 
                  end
                else begin 
				    y <= y - 1;
                    state <= STAGE_0;
                    //$display(" ## from STAGE_1 go to state = STAGE_0 "); 
                  end
			  end 
			else begin
			    //$display(" ## waitng in state = STAGE_2 real_state = %d", state);
			  end
			FINISH : begin
			    result <= y;
			    busy <= 0;
			    access <= 0;
			end
		endcase
	end
end
endmodule
