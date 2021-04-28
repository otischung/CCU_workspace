`timescale 1ns / 1ps
`include "16bit_CLA.v"

module CLA_32bit(a, b, cin, s, GP, GG);

    input [31:0] a, b;
    input cin;
    output [31:0] s;
    output GP, GG;

	wire c; // c = c16
    wire [1:0] gp, gg;  // gp[0] = P3:0, gp[1] = P7:4, ...

	CLA_16bit CLA16(a[15:0], b[15:0], cin, s[15:0], gp[0], gg[0]);
	CLA_16bit CLA32(a[31:16], b[31:16], c, s[31:16], gp[1], gg[1]);
    PG2bitToGroup G1(gp, gg, cin, GP, GG, c);

endmodule
