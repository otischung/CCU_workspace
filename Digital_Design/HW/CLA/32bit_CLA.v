`timescale 1ns / 1ps
`include "16bit_CLA.v"

module CLA_32bit(a, b, cin, s, GP, GG, cout);

    input [31:0] a, b;
    input cin;
    output [31:0] s;
    output GP, GG, cout;

	wire c; // c = c16
	wire [1:0] check_c;
    wire [1:0] gp, gg;  // gp[0] = P15:0, gp[1] = P31:16

	CLA_16bit CLA16(a[15:0], b[15:0], cin, s[15:0], gp[0], gg[0], check_c[0]);
    PG2C C1(cin, gp[0], gg[0], c);
	CLA_16bit CLA32(a[31:16], b[31:16], c, s[31:16], gp[1], gg[1], check_c[1]);
    // PG2C C2(c[0], gp[1], gg[1], cout);
	assign GP = gp[1] & gp[0];
	assign GG = gg[1] | (gp[1] & gg[0]);
	PG2C C0(cin, GP, GG, cout);

endmodule
