`timescale 1ns / 1ps
`include "16bit_CLA.v"

module CLA_32bit(a, b ,cin, sum, cout, gp, gg);

	input [31:0] a, b;
	input cin;
	output [31:0] sum;
	output cout, gp, gg;

	wire c;
	wire [1:0] GP, GG;  // GP[0] = [15:0] GP, GP[1] = [31:15] GP...

	CLA_16bit CLA16(a[15:0], b[15:0], cin, sum[15:0], c, GP[0], GG[0]);
	CLA_16bit CLA32(a[31:16], b[31:16], c, sum[31:16], cout, GP[1], GG[1]);

	assign gp = GP[1] & GP[0];
	assign gg = GG[1] | (GP[1] & GG[0]);

endmodule
