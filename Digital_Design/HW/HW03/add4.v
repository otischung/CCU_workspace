//`timescale 1ns / 1ps
//module add(
//	input [15:0] SW,
//	input CLK100MHZ,
//	input BTNC,
//	output reg [15:0] LED
//    );
	
//	always@(posedge CLK100MHZ) begin
//	   if (BTNC) begin
//	       LED = SW[3:0] + SW[7:4] + SW[11:8] + SW[15:12];
//	   end
//	end
	
//endmodule

`timescale 1ns / 1ps
module add(
	input [15:0] SW,
	input CLK100MHZ,
	input BTNC,
	output [15:0] LED
    );
    
    wire [3:0] a, b, c, d;
    wire [15:0] sum;
    reg [15:0] tmp;
    assign a = SW[3:0];
    assign b = SW[7:4];
    assign c = SW[11:8];
    assign d = SW[15:12];
    assign sum = a + b + c + d;
    assign LED = tmp;
    
	
	always@(posedge CLK100MHZ) begin
	   if (BTNC) begin
	       tmp = sum;
	   end
	end
	
endmodule