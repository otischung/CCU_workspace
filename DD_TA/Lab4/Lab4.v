`include "sample.v"

module Lab4(a, b, p);
	input [3:0] a, b;
	output [7:0] p;
	wire [3:0] w[0:4];
	wire [7:0] s[0:2];
	wire c[0:3];

	MUX_4bit M1(a, 4'b0000, b[0], w[0]);
	MUX_4bit M2(a, 4'b0000, b[1], w[1]);
	MUX_4bit M3(a, 4'b0000, b[2], w[2]);
	MUX_4bit M4(a, 4'b0000, b[3], w[3]);
	ADD_8bit A1({4'b0000, w[0]}, {3'b000, w[1], 1'b0}, 1'b0, s[0], c[0]);
	ADD_8bit A2(s[0], {2'b00, w[2], 2'b00}, 1'b0, s[1], c[1]);
	ADD_8bit A3(s[1], {1'b0, w[3], 3'b000}, 1'b0, p, c[2]);
endmodule

module ADD_8bit(a, b, cin, s, cout);
	input [7:0] a, b;
	input cin;
	output [7:0] s;
	output cout;
	wire c;

	ADD_4bit A1(a[3:0], b[3:0], cin, s[3:0], c);
	ADD_4bit A2(a[7:4], b[7:4], c, s[7:4], cout);
endmodule

module ADD_4bit(a, b, cin, s, cout);
	input [3:0] a, b;
	input cin;
	output [3:0] s;
	output cout;
	wire [3:1] c;

	FA FA1(a[0], b[0], cin, s[0], c[1]);
	FA FA2(a[1], b[1], c[1], s[1], c[2]);
	FA FA3(a[2], b[2], c[2], s[2], c[3]);
	FA FA4(a[3], b[3], c[3], s[3], cout);
endmodule

module MUX_4bit(a, b, sel, out);
	input [3:0] a, b;
	input sel;
	output [3:0] out;

	MUX M1(a[0], b[0], sel, out[0]);
	MUX M2(a[1], b[1], sel, out[1]);
	MUX M3(a[2], b[2], sel, out[2]);
	MUX M4(a[3], b[3], sel, out[3]);
endmodule

module MUX(a, b, sel, out);  // sel = 1 -> out = a
	input a, b, sel;
	output out;
	wire aa, ba;

	AND2X1 A1(a, sel, aa);
	AND2X1 A2(b, ~sel, ba);
	OR2X1 O1(aa, ba, out);
endmodule


module FA(a, b, cin, s, cout);
	input a, b, cin;
	output s, cout;
	wire x, a1, a2;

	XOR2X1 X1(a, b, x);
	XOR2X1 X2(x, cin, s);
	AND2X1 A1(a, b, a1);
	AND2X1 A2(x, cin, a2);
	OR2X1 O1(a1, a2, cout);
endmodule
