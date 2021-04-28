`timescale 1ns / 1ps
`include "PG_converter.v"

module CLS_4bit(x, y, bin, d, GP, GG);
	
	input [3:0] x, y;
	input bin;
	output [3:0] d;
	output GP, GG;

	wire [2:0] b;
    wire [3:0] p, g;

    FS4bitToPG T1(x, y, p, g);
    PG4bitToGroup G1(p, g, bin, GP, GG, b);
    assign d = x ^ y ^ {b, bin};
	
endmodule
