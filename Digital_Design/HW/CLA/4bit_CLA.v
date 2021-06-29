`timescale 1ns / 1ps
`include "PG_converter.v"

module CLA_4bit(a, b, cin, s, GP, GG);
	
	input [3:0] a, b;
	input cin;
	output [3:0] s;
	output GP, GG;

	wire [2:0] c;
    wire [3:0] p, g;

    FA4bitToPG T1(.a, .b, .p, .g);
    PG4bitToGroup G1(.p, .g, .cin, .P(GP), .G(GG), .c);
    assign s = a ^ b ^ {c, cin};
	
endmodule
