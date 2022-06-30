// module CLA(A, B, cin, S, cout);  // Combinational
// 	input [3:0] A, B;
// 	input cin;
// 	output [3:0] S;
// 	output cout;
// 	wire [3:1] c;
// 	wire [3:0] P, G;

// 	assign P = A | B;
// 	assign G = A & B;
// 	assign c[1] = G[0] | (P[0] & cin);
// 	assign c[2] = G[1] | (P[1] & G[0]) | (P[1] & P[0] & cin);
// 	assign c[3] = G[2] | (P[2] & G[1]) | (P[2] & P[1] & G[0]) | (P[2] & P[1] & P[0] & cin);
// 	assign cout = G[3] | (P[3] & G[2]) | (P[3] & P[2] & G[1]) | (P[3] & P[2] & P[1] & G[0]) | (P[3] & P[2] & P[1] & P[0] & cin);
// 	assign S[0] = A[0] ^ B[0] ^ cin;
// 	assign S[1] = A[1] ^ B[1] ^ c[1];
// 	assign S[2] = A[2] ^ B[2] ^ c[2];
// 	assign S[3] = A[3] ^ B[3] ^ c[3];
// endmodule

module CLA(clk, rst, A, B, carry, Y);
	input clk;
	input rst;
	input [3:0] A;
	input [3:0] B;
	input carry;
	output [4:0] Y;

	reg	[3:0] P;
	reg	[3:0] G;
	reg	[4:0] S;
	reg	[4:0] C;

	assign Y = S;

	always @(posedge clk or negedge rst) begin
		if (!rst) begin
			P <= 4'd0;
			G <= 4'd0;
			S <= 5'd0;
			C <= 5'd0;
		end else begin
			// P <= A | B;
			P <= A ^ B;
			G <= A & B;
			C[1] <= G[0] | (P[0] & carry);
			C[2] <= G[1] | (P[1] & G[0]) | (P[1] & P[0] & carry);
			C[3] <= G[2] | (P[2] & G[1]) | (P[2] & P[1] & G[0]) | (P[2] & P[1] & P[0] & carry);
			S[4] <= G[3] | (P[3] & G[2]) | (P[3] & P[2] & G[1]) | (P[3] & P[2] & P[1] & G[0]) | (P[3] & P[2] & P[1] & P[0] & carry);
			// S[0] <= A[0] ^ B[0] ^ carry;
			// S[1] <= A[1] ^ B[1] ^ C[1];
			// S[2] <= A[2] ^ B[2] ^ C[2];
			// S[3] <= A[3] ^ B[3] ^ C[3];
			S[0] <= P[0] ^ carry;
			S[1] <= P[1] ^ C[1];
			S[2] <= P[2] ^ C[2];
			S[3] <= P[3] ^ C[3];
		end
	end
endmodule
