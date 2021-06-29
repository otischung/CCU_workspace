module moore_ex( input clk,
				 input reset,
				 input x,
				 output reg y );
		
	reg [1:0] current_state, next_state;
	
	parameter S0 = 2'd0;
	parameter S1 = 2'd1;
	parameter S2 = 2'd2; 
	parameter S3 = 2'd3;
	
	always@(*) begin
		case(current_state)
			S0:
				if(x) begin
					next_state = S1;
				end
				else begin
					next_state = S0;
				end
			S1:
				if(x) begin
					next_state = S2;
				end
				else begin
					next_state = S0;
				end
			S2:
				if(~x) begin
					next_state = S3;
				end
				else begin
					next_state = S2;
				end
			S3:
				if(x) begin
					next_state = S1;
				end
				else begin
					next_state = S0;
				end
			default:
				next_state = S0;
		endcase
	end

	always@(posedge clk) begin
		if(reset) begin
			current_state <= S0;
		end
		else begin
			current_state <= next_state;
		end
	end

	always@(*) begin
		case(current_state)
			S0:
				y = 1'b0;
			S1:
				y = 1'b0;
			S2:
				y = 1'b0;
			S3:
				y = 1'b1;
			default:
				y = 1'b0;
		endcase
	end
		
endmodule
		
	
	