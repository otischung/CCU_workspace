`timescale 1ns / 1ps
`include "4bit_CLA.v"

module CLA_16bit(a, b, cin, s, GP, GG);

    input [15:0] a, b;
    input cin;
    output [15:0] s;
    output GP, GG;

	wire [2:0] c; // c[0] = c4, c[1] = c8, c[2] = c12
    wire [3:0] gp, gg;  // gp[0] = P3:0, gp[1] = P7:4, ...

	CLA_4bit CLA04(a[3:0], b[3:0], cin, s[3:0], gp[0], gg[0]);
	CLA_4bit CLA08(a[7:4], b[7:4], c[0], s[7:4], gp[1], gg[1]);
	CLA_4bit CLA12(a[11:8], b[11:8], c[1], s[11:8], gp[2], gg[2]);
	CLA_4bit CLA16(a[15:12], b[15:12], c[2], s[15:12], gp[3], gg[3]);
    PG4bitToGroup G1(gp, gg, cin, GP, GG, c);

endmodule
