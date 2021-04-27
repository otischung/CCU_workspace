`timescale 1ns / 1ps
`include "4bit_CLA.v"

module CLA_16bit(a, b, cin, s, p, g, cout);

    input [15:0] a, b;
    input cin;
    output [15:0] s, p, g;
    output cout;

	wire [2:0] c; // c[0] = c4, c[1] = c8, c[2] = c12
	wire [3:0] check_c;
    wire [3:0] GP, GG;

	CLA_4bit CLA04(a[3:0], b[3:0], cin, s[3:0], p[3:0], g[3:0], check_c[0]);
	PG2Group G1(p[3:0], g[3:0], GP[0], GG[0]);
    PG2C C1(cin, GP[0], GG[0], c[0]);
	CLA_4bit CLA08(a[7:4], b[7:4], c[0], s[7:4], p[7:4], g[7:4], check_c[1]);
	PG2Group G2(p[7:4], g[7:4], GP[1], GG[1]);
    PG2C C2(c[0], GP[1], GG[1], c[1]);
	CLA_4bit CLA12(a[11:8], b[11:8], c[1], s[11:8], p[11:8], g[11:8], check_c[2]);
	PG2Group G3(p[11:8], g[11:8], GP[2], GG[2]);
    PG2C C3(c[1], GP[2], GG[2], c[2]);
	CLA_4bit CLA16(a[15:12], b[15:12], c[2], s[15:12], p[15:12], g[15:12], check_c[3]);
	PG2Group G4(p[15:12], g[15:12], GP[3], GG[3]);
    PG2C C4(c[2], GP[3], GG[3], cout);
    

    // assign s = a ^ b ^ {c, cin};

    // wire [2:0] c;
	// wire [3:0] GP, GG;  // GP[0] = [3:0] GP, GP[1] = [7:4] GP...
	
	// CLA_4bit CLA04(a[3:0], b[3:0], cin, nsum[3:0], c[0], GP[0], GG[0]);
	// CLA_4bit CLA08(a[7:4], b[7:4], c[0], sum[7:4], c[1], GP[1], GG[1]);
	// CLA_4bit CLA12(a[11:8], b[11:8], c[1], sum[11:8], c[2], GP[2], GG[2]);
	// CLA_4bit CLA16(a[15:12], b[15:12], c[2], sum[15:12], cout, GP[3], GG[3]);

	// assign gg = GG[3] | (GP[3] & GG[2]) | (GP[3] & GP[2] & GG[1]) | (GP[3] & GP[2] & GP[1] & GG[0]);
	// assign gp = GP[3] & GP[2] & GP[1] & GP[0];

endmodule

// module CLA_16bit(a, b, cin, sum, cout, gp, gg);

//     input [15:0] a, b;
//     input cin;
//     output [15:0] sum;
//     output cout, gp, gg;

//     wire [2:0] c;
// 	wire [3:0] GP, GG;  // GP[0] = [3:0] GP, GP[1] = [7:4] GP...
	
// 	CLA_4bit CLA04(a[3:0], b[3:0], cin, sum[3:0], c[0], GP[0], GG[0]);
// 	CLA_4bit CLA08(a[7:4], b[7:4], c[0], sum[7:4], c[1], GP[1], GG[1]);
// 	CLA_4bit CLA12(a[11:8], b[11:8], c[1], sum[11:8], c[2], GP[2], GG[2]);
// 	CLA_4bit CLA16(a[15:12], b[15:12], c[2], sum[15:12], cout, GP[3], GG[3]);

// 	assign gg = GG[3] | (GP[3] & GG[2]) | (GP[3] & GP[2] & GG[1]) | (GP[3] & GP[2] & GP[1] & GG[0]);
// 	assign gp = GP[3] & GP[2] & GP[1] & GP[0];

// endmodule


// module CLA_4bit(A, B, Cin, Sum, Cout, GP, GG);
	
// 	input [3:0] A, B;
// 	input Cin;
// 	output [3:0] Sum;
// 	output Cout, GP, GG;

// 	wire [3:0] G, P, C;

// 	assign G = A & B;  // Generate
// 	assign P = A | B;  // Propagate
// 	assign GG = G[3] | (P[3] & G[2]) | (P[3] & P[2] & G[1]) | (P[3] & P[2] & P[1] & G[0]);  // Group Generate
// 	assign GP = P[3] & P[2] & P[1] & P[0];  // Group Propagate
// 	assign C[0] = Cin;
// 	assign C[1] = G[0] | (P[0] & C[0]);
// 	assign C[2] = G[1] | (P[1] & G[0]) | (P[1] & P[0] & C[0]);
// 	assign C[3] = G[2] | (P[2] & G[1]) | (P[2] & P[1] & G[0]) | (P[2] & P[1] & P[0] & C[0]);
// 	assign Cout = GG | (GP & C[0]);
// 	assign Sum = A ^ B ^ C;
	
	
// endmodule
