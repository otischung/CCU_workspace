module multiplier(clk, rst, A, B, P);
	input clk;
	input rst;
	input [3:0] A;
	input [3:0] B;
	output reg [7:0] P;
	reg ov;
	reg [3:0] cnt;

	initial begin
		P <= 8'b0000_0000;
		ov <= 1'b0;
		cnt <= 4'b0000;
	end

	always @(posedge clk or negedge rst) begin
		if (!rst) begin
			cnt <= 4'b0000;
		end else if (cnt == 9) begin
			cnt <= 4'd9;
		end else begin
			cnt <= cnt + 1;
		end
	end

	always @(posedge clk or negedge rst) begin
		if (!rst) begin
			P <= 8'b0000_0000;
			ov <= 1'b0;
		end else begin
			if (cnt == 0) begin
				{ov, P} <= {ov, P} + B;
			end else if (cnt == 9) begin
				{ov, P} <= {ov, P};
			end else if (cnt % 2) begin
				if (P[0]) begin
					{ov, P} <= {ov, P} + {1'b0, A, 4'b0000};
				end else begin
					{ov, P} <= {ov, P};
				end
			end else begin
				{ov, P} <= {ov, P} >> 1;
			end
		end
	end
endmodule
