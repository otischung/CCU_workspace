`timescale 1ns / 1ps
`include "PG_converter.v"

module CLA_4bit(a, b, cin, s, p, g, cout);
	
	input [3:0] a, b;
	input cin;
	output [3:0] s, p, g;
	output cout;

	wire [2:0] c;
    wire GP, GG;

    FAPG T1(a[0], b[0], cin, p[0], g[0]);
    assign c[0] = g[0] | (p[0] & cin);
    FAPG T2(a[1], b[1], c[0], p[1], g[1]);
    assign c[1] = g[1] | (p[1] & g[0]) | (p[1] & p[0] & cin);
    FAPG T3(a[2], b[2], c[1], p[2], g[2]);
    assign c[2] = g[2] | (p[2] & g[1]) | (p[2] & p[1] & g[0]) | (p[2] & p[1] & p[0] & cin);
    FAPG T4(a[3], b[3], c[2], p[3], g[3]);
    PG2Group G1(p, g, GP, GG);
    PG2C C1(cin, GP, GG, cout);
    assign s = a ^ b ^ {c, cin};
	
endmodule
