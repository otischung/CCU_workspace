`timescale 1ns/ 10ps
`include "moore_ex.v"

module moore_ex_tb;

	reg clk, reset, x;
	wire y;
	
	moore_ex moore1(clk, reset, x, y);
	
	initial begin
		$dumpfile("moore_ex.fsdb");
		$dumpvars;
	end
	
	initial begin
		clk <= 1'b1;
		reset <= 1'b0;
		x <= 1'b0;
	end
	
	always #10 clk = ~clk;
	
	initial begin
		#5  reset <= 1'b1;
		#20 reset <= 1'b0;
	end
	
	
	initial begin
		repeat(3)@(posedge clk);
		x <= 1'b0;
		repeat(2)@(posedge clk);
		x <= 1'b1;
		@(posedge clk);
		x <= 1'b0;
		repeat(2)@(posedge clk);
		x <= 1'b1;
		repeat(4)@(posedge clk);
		x <= 1'b0;
		repeat(3)@(posedge clk);
		x <= 1'b1;
		repeat(2)@(posedge clk);
		x <= 1'b0;
		repeat(3)@(posedge clk);
		x <= 1'b1;
		repeat(2)@(posedge clk);
		x <= 1'b0;
		@(posedge clk);
		x <= 1'b1;
		#200 $finish;
	end
		
		
endmodule
		
		
		
		