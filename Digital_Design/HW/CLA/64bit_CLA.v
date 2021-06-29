`timescale 1ns / 1ps
`include "16bit_CLA.v"

module CLA_64bit(a, b, cin, s, GP, GG);

    input [63:0] a, b;
    input cin;
    output [63:0] s;
    output GP, GG;

	wire [2:0] c; // c[0] = c16, c[1] = c32, c[2] = c48
    wire [3:0] gp, gg;  // gp[0] = P15:0, gp[1] = P31:16, ...

	CLA_16bit CLA16(a[15:0], b[15:0], cin, s[15:0], gp[0], gg[0]);
	CLA_16bit CLA32(a[31:16], b[31:16], c[0], s[31:16], gp[1], gg[1]);
	CLA_16bit CLA48(a[47:32], b[47:32], c[1], s[47:32], gp[2], gg[2]);
	CLA_16bit CLA60(a[63:48], b[63:48], c[2], s[63:48], gp[3], gg[3]);
    PG4bitToGroup G1(gp, gg, cin, GP, GG, c);

endmodule
