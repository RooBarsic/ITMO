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
reg lsfr_clk;
reg lsfr_rst;
reg lsfr_access;
reg [7:0] lsfr_base_number;
wire lsfr_busy;
wire [7:0] lsfr_out;

generate_next_LSFR dut2(
    .clk(lsfr_clk),
    .rst(lsfr_rst),
    .outside_access(lsfr_access),
    .base_number(lsfr_base_number),
    .busy(lsfr_busy),
    .generated_number(lsfr_out)
);

reg crc_clk;
reg crc_rst;
reg [7:0] crc_data;
reg crc_new_data;
wire crc_busy;
wire [7: 0] crc_out;
reg [7:0] polynom = 8'b11010001;
reg [7:0] crc_base;
CRC8_calculator dut3(
    .clk(crc_clk),
    .rst(crc_rst),
    .data(crc_data),
    .new_data(crc_new_data),
    .busy(crc_busy),
    .result_crc8(crc_out)
);

reg lg_rst;
reg lg_clk;
reg lg_testing_button;
reg lg_start_calc;
reg lg_lsfr_base;
reg [7:0] lg_data;
wire lg_busy;
wire [3:0] lg_kol_testing;
wire [7:0] lg_result;
control_logic dut4(
    .rst (lg_rst),
    .clk (lg_clk),
    .start_stop_testing (lg_testing_button),
    .start_calculation (lg_start_calc),
    .get_lsfr_base_from_data (lg_lsfr_base),
    .input_data (lg_data),
    .busy(lg_busy),
    .number_of_testing(lg_kol_testing),
    .result(lg_result)
);
    

integer i, xx, bb, kol_ok, kol_error;
integer base, buff, j;

initial
	begin
	    $display(" ~~ @@  Start testing simulation " );
	    //* testing control_logic
        kol_ok = 0;
	    kol_error = 0;
	    
	    
        #10 lg_clk = 1; lg_rst = 1;
        #10 lg_clk = 0; lg_rst = 1;
	    #10 lg_clk = 1; lg_rst = 0;
	    
	    /*   
	    for(xx = 0; xx <= 255; xx = xx + 1) begin
            lg_data = xx;
            #10 lg_clk = 1; 
            lg_start_calc = 1;
            for (i = 0; i < 400; i = i + 1) begin
                #5 lg_clk = 1;
                #5 lg_clk = 0;
            end
            lg_start_calc = 0;
            #5 lg_clk = 1;
            #5 lg_clk = 0;
            
            bb = 0;
            while(bb * bb * bb <= xx) begin
                bb = bb + 1;
            end
            bb = bb - 1;
            
            $display("~~~ %%% lg_busy = %b ", lg_busy);
            if(bb != lg_result) begin 
                kol_error = kol_error + 1; 
                $display("~~~ Error number x = %d, real result = %d, expected result = %d", xx, lg_result, bb);
            end 
            else begin
                kol_ok = kol_ok + 1;
                //$display("~~~ OK number x = %d, real result = %d, expected result = %d", xx, lg_result, bb);
            end
	   end
	   $display(" ~~ Testing sqrt ---  kol_ok = %d kol_error = %d", kol_ok, kol_error);
	    //*/
	    
	    lg_testing_button = 0;
	   
        lg_testing_button = 1;
        lg_start_calc = 0;
        lg_lsfr_base = 0;
        lg_data = 0;
        #10 lg_clk = 1; 
        #10 lg_clk = 0;
        #10 lg_clk = 1; 
        #10 lg_clk = 0;
        
        for (i = 0; i < 100; i = i + 1) begin
            #5 lg_clk = 1;
            #5 lg_clk = 0;
        end
	    $display(" ~~~ Test testing in schema   busy = %b result = %b kol_testing = %b", lg_busy, lg_result, lg_kol_testing);
	    
        /* testing CRC8_calculator
        kol_ok = 0;
	    kol_error = 0;
	    
	    crc_new_data = 0;
	    #10 
	    #10 crc_clk = 0; crc_rst = 0;
        #10 crc_clk = 1; crc_rst = 1;
        #10 crc_clk = 0; crc_rst = 0;
	       
	    crc_base = 0;
	    for(buff = 0; buff <= 255; buff = buff + 1) begin
	       $display(" buff = %d", buff);
	       crc_data = buff;
	       crc_new_data = 1;
	       
	       for(j = 1; j <= 20; j = j + 1) begin
               #5 crc_clk = 1;
               #5 crc_clk = 0;
            end
           #5 crc_new_data = 0; crc_clk = 1;
           #5 crc_new_data = 0; crc_clk = 0;
           
           for(j = 7; j >= 0; j = j - 1) begin
               if(crc_base[7] == 1) crc_base = crc_base ^ polynom;
               crc_base = (crc_base << 1);
               crc_base[0] = buff[j];
            end
               
           if(crc_base == crc_out) kol_ok = kol_ok + 1;
           else begin 
              $display(" ~~ Error buff = %10b crc_base = %10b crc_out = %b ", buff, crc_base, crc_out);
              kol_error = kol_error + 1;
           end
           base = lsfr_out;
	    end
	    $display(" kol_ok = %d kol_error = %d  result = %b", kol_ok, kol_error, crc_out);
	    //*/
        

	    /* testing -- generate_next_LSFR 
	    kol_ok = 0;
	    kol_error = 0;
	    for(buff = 1; buff <= 256; buff = buff + 1) begin
	       $display(" buff = %d", buff);
	       base = buff;
	       lsfr_base_number = buff;
	       lsfr_clk = 0; lsfr_rst = 1;
	       #10 lsfr_clk = 1; lsfr_rst = 1;
	       #10 lsfr_clk = 0; lsfr_rst = 0;
	       for(j = 1; j <= 100; j = j + 1) begin
               #5 lsfr_access = 0; lsfr_clk = 1;
               #5 lsfr_access = 0; lsfr_clk = 0;
               #5 lsfr_access = 1;
               for(i = 0; i <= 10; i = i + 1) begin
                   #5 lsfr_clk = 1;
                   #5 lsfr_clk = 0;
               end
               
               if((base[0] == lsfr_out[1]) && (base[1] == lsfr_out[2]) && (base[2] == lsfr_out[3]) &&
                  (base[3] == lsfr_out[4]) && (base[4] == lsfr_out[5]) && (base[5] == lsfr_out[6]) && 
                  (base[6] == lsfr_out[7]) && (lsfr_out[0] == (base[0] ^ base[1] ^ base[2] ^ base[4] ^ base[7])))
                     kol_ok = kol_ok + 1;
               else begin 
                  $display(" ~~ Error base = %b lsfr_out = %b", base, lsfr_out);
                  kol_error = kol_error + 1;
               end
               base = lsfr_out;
	       end
	    end
	    $display(" kol_ok = %d kol_error = %d", kol_ok, kol_error);
	     // End testing lsfr */

        /*	
        // sqrt3 - testing
		$display("Start testing ");
		// $monitor("c = %b, res = %d, r = %b, time = %0d", clk_c_i, s_o, res_o, $time);
		kol_ok = 0;
		kol_error = 0;
		for(xx = 0; xx <= 255; xx = xx + 1) begin
            clk_c_i = 0; rst_c_i = 1; start_c_i=0; x_i = xx;
            #10 clk_c_i = 1; rst_c_i = 1;
            #10 clk_c_i = 0; rst_c_i = 0;
            start_c_i = 1;
            #5
            for (i = 0; i < 400; i = i + 1) begin
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
	//01100101   */
	   #10 $stop;
	end
endmodule 

