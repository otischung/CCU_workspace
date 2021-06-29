`timescale 1ns / 10ps
`include "mealy_hw.v"
// `include "moore_hw.v"

module tb;

	reg clk, rst, x;
	wire y;
	
	mealy_hw mealy(clk, rst, x, y); // module
	// moore_hw moore(clk, rst, x, y); // module
	
	initial begin
		$dumpfile("hw_mealy.fsdb");
		// $dumpfile("hw_moore.fsdb");
		$dumpvars;
		clk <= 1'b1;
		rst <= 1'b0;
		x <= 1'b0;
		#5  rst <= 1'b1;
		#20 rst <= 1'b0;
	end
	
	always #10 clk = ~clk;

	// always @(posedge clk) begin
	// 	$display("%d", x);
	// end
	
	initial begin
		repeat(3) @(posedge clk);
		x <= 1'b0;
		repeat(2) @(posedge clk);
		x <= 1'b1;
		@(posedge clk);
		x <= 1'b0;
		repeat(2) @(posedge clk);
		x <= 1'b1;
		@(posedge clk);
		x <= 1'b0;
		repeat(2) @(posedge clk);
		x <= 1'b1;
		@(posedge clk);
		x <= 1'b0;
		repeat(3) @(posedge clk);
		x <= 1'b1;
		repeat(2) @(posedge clk);
		x <= 1'b0;
		repeat(3) @(posedge clk);
		x <= 1'b1;
		repeat(2) @(posedge clk);
		x <= 1'b0;
		@(posedge clk);
		x <= 1'b1;
		@(posedge clk);
		x <= 1'b0;
		repeat(2) @(posedge clk);
		x <= 1'b1;
		@(posedge clk);
		x <= 1'b0;
		@(posedge clk);
		x <= 1'b1;
		#200 $finish;
	end
		
endmodule
