module mealy_ex( input clk,
				 input reset,
				 input x,
				 output reg y );
		
	parameter S0 = 2'b00, S1 = 2'b01, S2 = 2'b10;
	reg [1:0] current_state, next_state;
	reg y_temp;
	
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
					next_state = S0;
				end
				else begin
					next_state = S2;
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
				if(x) begin
					y_temp = 1'b0;
				end
				else begin
					y_temp = 1'b0;
				end
			S1:
				if(x) begin
					y_temp = 1'b0;
				end
				else begin
					y_temp = 1'b0;
				end
			S2:
				if(~x) begin
					y_temp = 1'b1;
				end
				else begin
					y_temp = 1'b0;
				end
			default:
				y_temp = 1'b0;
		endcase
	end
		
	always@(posedge clk) begin
		if(reset) begin
			y <= 1'b0;
		end
		else begin	
			y <= y_temp;
		end
	end
		
endmodule
		
	
	