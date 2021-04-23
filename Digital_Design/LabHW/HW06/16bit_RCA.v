`timescale 1ns / 1ps

module RCA_16bit(a, b, cin, sum, cout);  // sum = 448ns, cout = 288ns

    input [15:0] a, b;
    input cin;
    output [15:0] sum;
    output cout;
    wire [14:0] c;
	// --- Write down your design here --- //
	fulladder FA01(a[0], b[0], cin,  sum[0], c[0]);
	fulladder FA02(a[1], b[1], c[0], sum[1], c[1]);
	fulladder FA03(a[2], b[2], c[1], sum[2], c[2]);
	fulladder FA04(a[3], b[3], c[2], sum[3], c[3]);
	fulladder FA05(a[4], b[4], c[3], sum[4], c[4]);
	fulladder FA06(a[5], b[5], c[4], sum[5], c[5]);
	fulladder FA07(a[6], b[6], c[5], sum[6], c[6]);
	fulladder FA08(a[7], b[7], c[6], sum[7], c[7]);
	fulladder FA09(a[8], b[8], c[7], sum[8], c[8]);
	fulladder FA10(a[9], b[9], c[8], sum[9], c[9]);
	fulladder FA11(a[10], b[10], c[9], sum[10], c[10]);
	fulladder FA12(a[11], b[11], c[10], sum[11], c[11]);
	fulladder FA13(a[12], b[12], c[11], sum[12], c[12]);
	fulladder FA14(a[13], b[13], c[12], sum[13], c[13]);
	fulladder FA15(a[14], b[14], c[13], sum[14], c[14]);
	fulladder FA16(a[15], b[15], c[14], sum[15], cout);
	// ----------------------------------- //

endmodule

// FA module
module fulladder(a, b, cin, sum, cout);  // sum = 28ns, cout = 18ns
	
	input a, b, cin;
	output sum, cout;

	wire s, c1, c2, c3, c4;

	// --- Write down your design here --- //
	// assign sum = a ^ b ^ cin;
	// assign cout = (a & b) | (a & cin) | (b & cin);

	xorgate fas1(a, b, s);		// 14ns
	xorgate fas2(s, cin, sum);	// 14ns

	andgate fac1(a, b, c1);		// 10ns
	andgate fac2(a, cin, c2);	// 10ns
	andgate fac3(b, cin, c3);	// 10ns
	orgate fac4(c1, c2, c4);	// 4ns	
	orgate fac5(c3, c4, cout);	// 4ns
	// ----------------------------------- //

endmodule

// xor gate
module xorgate (a, b, out);		// 14ns
	
	input a, b;
	output out;

	wire w1, w2;

	// --- Write down your design here --- //
	// assign out = (a & ~b) | (~a & b);

	andgate xor1(a, ~b, w1);	// 10ns
	andgate xor2(~a, b, w2);	// 10ns
	orgate xor3(w1, w2, out);	// 4ns
	// ----------------------------------- //

endmodule

// and gate
module andgate (a, b, out);
	
	input a, b;
	output reg out;

	always @(*) begin
		#10 out <= a & b; // #10ns 為 and gate's gate delay
	end

endmodule

// or gate
module orgate (a, b, out);
	
	input a, b;
	output reg out;

	always @(*) begin
		#4 out <= a | b; // #4ns 為 or gate's gate delay
	end

endmodule