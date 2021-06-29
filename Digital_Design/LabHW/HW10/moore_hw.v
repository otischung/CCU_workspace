module moore_hw(clk, rst, x, y);
	
	input clk;
	input rst;
	input x;
	output reg y;
		
	reg [2:0] current_state, next_state;
	
	parameter S0 = 3'd0;
	parameter S1 = 3'd1;
	parameter S2 = 3'd2; 
	parameter S3 = 3'd3;
	parameter S4 = 3'd4;
	parameter S5 = 3'd5;

	always @(posedge clk) begin
		if (rst) begin
			current_state <= S0;
			y <= 1'b0;
		end
		else begin
			current_state <= next_state;
			y <= y;
		end
	end
	
	always @(*) begin
		case (current_state)
			S0: begin
				if (x) begin
					next_state = S1;
				end
				else begin
					next_state = S0;
				end
				y = 1'b0;
			end
			S1: begin
				if (x) begin
					next_state = S1;
				end
				else begin
					next_state = S2;
				end
				y = 1'b0;
			end
			S2: begin
				if (x) begin
					next_state = S1;
				end
				else begin
					next_state = S3;
				end
				y = 1'b0;
			end
			S3: begin
				if (x) begin
					next_state = S4;
				end
				else begin
					next_state = S0;
				end
				y = 1'b0;
			end
			S4: begin
				if (x) begin
					next_state = S1;
				end
				else begin
					next_state = S5;
				end
				y = 1'b0;
			end
			S5: begin
				if (x) begin
					next_state = S1;
				end
				else begin
					next_state = S3;
				end
				y = 1'b1;
			end
			default: begin
				next_state = S0;
				y = 1'b0;
			end
		endcase
	end
		
endmodule
