`timescale 1ns / 1ps
`include "16bit_CLS.v"

module CLS_64bit(x, y, bin, d, GP, GG);

    input [63:0] x, y;
    input bin;
    output [63:0] d;
    output GP, GG;

	wire [2:0] b; // c[0] = c16, c[1] = c32, c[2] = c48
    wire [3:0] gp, gg;  // gp[0] = P15:0, gp[1] = P31:16, ...

	CLS_16bit CLS16(x[15:0], y[15:0], bin, d[15:0], gp[0], gg[0]);
	CLS_16bit CLS32(x[31:16], y[31:16], b[0], d[31:16], gp[1], gg[1]);
	CLS_16bit CLS48(x[47:32], y[47:32], b[1], d[47:32], gp[2], gg[2]);
	CLS_16bit CLS60(x[63:48], y[63:48], b[2], d[63:48], gp[3], gg[3]);
    PG4bitToGroup G1(gp, gg, bin, GP, GG, b);

endmodule
