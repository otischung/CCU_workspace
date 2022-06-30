// module RCA(A, B, cin, S, cout);  // Combinational
// 	input [3:0] A, B;
// 	input cin;
// 	output [3:0] S;
// 	output cout;
// 	wire [3:1] c;

// 	FA FA0(A[0], B[0], cin, S[0], c[1]);
// 	FA FA1(A[1], B[1], c[1], S[1], c[2]);
// 	FA FA2(A[2], B[2], c[2], S[2], c[3]);
// 	FA FA3(A[3], B[3], c[3], S[3], cout);

// endmodule

// module FA(A, B, cin, S, cout);  // Combinational
// 	input A, B, cin;
// 	output S, cout;

// 	assign S = A ^ B ^ cin;
// 	assign cout = (A & B) | (A & cin) | (B & cin);
// endmodule

module RCA(clk, rst, A, B, carry, Y);
	input clk;
	input rst;
	input [3:0] A;
	input [3:0] B;
	input carry;
	output [4:0] Y;

	reg	[4:0] S;
	reg	[4:0] C;

	assign Y = S;

	always @(posedge clk or negedge rst) begin
		if (!rst) begin
			S <= 5'd0;
			C <= 5'd0;
		end else begin
			S[0] <= A[0] ^ B[0] ^ carry;
			C[1] <= (A[0] & B[0]) | (A[0] & carry) | (B[0] & carry);
			S[1] <= A[1] ^ B[1] ^ C[1];
			C[2] <= (A[1] & B[1]) | (A[1] & C[1]) | (B[1] & C[1]);
			S[2] <= A[2] ^ B[2] ^ C[2];
			C[3] <= (A[2] & B[2]) | (A[2] & C[2]) | (B[2] & C[2]);
			S[3] <= A[3] ^ B[3] ^ C[3];
			S[4] <= (A[3] & B[3]) | (A[3] & C[3]) | (B[3] & C[3]);
		end
	end
endmodule
