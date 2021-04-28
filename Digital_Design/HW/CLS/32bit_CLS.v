`timescale 1ns / 1ps
`include "16bit_CLS.v"

module CLS_32bit(x, y, bin, d, GP, GG);

    input [31:0] x, y;
    input bin;
    output [31:0] d;
    output GP, GG;

	wire b; // c = c16
    wire [1:0] gp, gg;  // gp[0] = P3:0, gp[1] = P7:4, ...

	CLS_16bit CLS16(x[15:0], y[15:0], bin, d[15:0], gp[0], gg[0]);
	CLS_16bit CLS32(x[31:16], y[31:16], b, d[31:16], gp[1], gg[1]);
    PG2bitToGroup G1(gp, gg, bin, GP, GG, b);

endmodule
