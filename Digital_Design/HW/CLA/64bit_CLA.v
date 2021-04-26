`timescale 1ns / 1ps
`include "16bit_CLA.v"

module CLA_64bit(a, b ,cin, sum, cout, gp, gg);

	input [63:0] a, b;
	input cin;
	output [63:0] sum;
	output cout, gp, gg;

	wire [2:0] c;
	wire [3:0] GP, GG;  // GP[0] = [15:0] GP, GP[1] = [31:15] GP...

	CLA_16bit CLA16(a[15:0], b[15:0], cin, sum[15:0], c[0], GP[0], GG[0]);
	CLA_16bit CLA32(a[31:16], b[31:16], c[0], sum[31:16], c[1], GP[1], GG[1]);
	CLA_16bit CLA48(a[47:32], b[47:32], c[1], sum[47:32], c[2], GP[2], GG[2]);
	CLA_16bit CLA64(a[63:48], b[63:48], c[2], sum[63:48], cout, GP[3], GG[3]);

	assign gg = GG[3] | (GP[3] & GG[2]) | (GP[3] & GP[2] & GG[1]) | (GP[3] & GP[2] & GP[1] & GG[0]);
	assign gp = GP[3] & GP[2] & GP[1] & GP[0];

endmodule
