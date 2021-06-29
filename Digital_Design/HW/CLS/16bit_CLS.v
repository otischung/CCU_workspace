`timescale 1ns / 1ps
`include "4bit_CLS.v"

module CLS_16bit(x, y, bin, d, GP, GG);

    input [15:0] x, y;
    input bin;
    output [15:0] d;
    output GP, GG;

	wire [2:0] b; // c[0] = c4, c[1] = c8, c[2] = c12
    wire [3:0] gp, gg;  // gp[0] = P3:0, gp[1] = P7:4, ...

	CLS_4bit CLS04(x[3:0], y[3:0], bin, d[3:0], gp[0], gg[0]);
	CLS_4bit CLS08(x[7:4], y[7:4], b[0], d[7:4], gp[1], gg[1]);
	CLS_4bit CLS12(x[11:8], y[11:8], b[1], d[11:8], gp[2], gg[2]);
	CLS_4bit CLS16(x[15:12], y[15:12], b[2], d[15:12], gp[3], gg[3]);
    PG4bitToGroup G1(gp, gg, bin, GP, GG, b);

endmodule
