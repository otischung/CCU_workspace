module mealy_hw(clk, rst, x, y);

	input clk;
	input rst;
	input x;
	output reg y;
		
	parameter S0 = 3'b000;
	parameter S1 = 3'b001;
	parameter S2 = 3'b010;
	parameter S3 = 3'b011;
	parameter S4 = 3'b100;

	reg [2:0] current_state, next_state;
	reg y_temp;

	always @(posedge clk) begin
		if (rst) begin
			current_state <= S0;
			y <= 1'b0;
		end
		else begin
			current_state <= next_state;
			y <= y_temp;
		end
	end
	
	always @(*) begin
		case (current_state)
			S0: begin
				if (x) begin
					next_state = S1;
					y_temp = 1'b0;
				end
				else begin
					next_state = S0;
					y_temp = 1'b0;
				end
			end
			S1: begin
				if (x) begin
					next_state = S1;
					y_temp = 1'b0;
				end
				else begin
					next_state = S2;
					y_temp = 1'b0;
				end
			end
			S2: begin
				if (x) begin
					next_state = S1;
					y_temp = 1'b0;
				end
				else begin
					next_state = S3;
					y_temp = 1'b0;
				end
			end
			S3: begin
				if (x) begin
					next_state = S4;
					y_temp = 1'b0;
				end
				else begin
					next_state = S0;
					y_temp = 1'b0;
				end
			end
			S4: begin
				if (x) begin
					next_state = S1;
					y_temp = 1'b0;
				end
				else begin
					next_state = S2;
					y_temp = 1'b1;
				end
			end
			default: begin
				next_state = S0;
				y_temp = 1'b0;
			end
		endcase
	end
		
endmodule
