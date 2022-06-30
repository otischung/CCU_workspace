/**
 *
 * @author : 409412345, 409412346
 * @latest changed : 2022/5/8 12:34
 */

module lab10(
	input clk,
	input reset,
	input [3:0] code_pos,
	input [2:0] code_len,
	input [7:0] chardata,
	output reg finish,
	output reg [7:0] char_nxt
);

	initial begin
		$dumpfile("Lab.vcd");
		$dumpvars(0, lab10tb);
	end

	reg [2:0] state;
	reg [7:0] window [0:9];
	reg [5:0] ix;

	always @(posedge clk or posedge reset) begin
		if (reset) begin	
			window[8] <= 0;
			window[7] <= 0;
			window[6] <= 0;
			window[5] <= 0;
			window[4] <= 0;
			window[3] <= 0;
			window[2] <= 0;
			window[1] <= 0;
		end else begin
			window[8] <= window[7];
			window[7] <= window[6];
			window[6] <= window[5];
			window[5] <= window[4];
			window[4] <= window[3];
			window[3] <= window[2];
			window[2] <= window[1];
			window[1] <= char_nxt;
		end
	end

	always @(posedge clk or posedge reset) begin
		if (reset) begin	
			state <= 0;
			ix <= 0;
			finish <= 0;
		end else begin
			case (state)
				3'd0: begin
					if (code_len == 0 && code_pos == 0) begin
						char_nxt <= chardata;
						if (chardata == 36)
							state <= 2;
					end else begin
						char_nxt <= (code_pos) ? window[code_pos] : char_nxt;
						state <= 1;
						ix <= 1;
					end
				end
				3'd1: begin
					if (ix < code_len) begin
						ix <= ix + 1;
						char_nxt <= (code_pos) ? window[code_pos] : char_nxt;
					end else if (chardata != 36) begin
						char_nxt <= chardata;
						state <= 0;
					end else begin
						char_nxt <= chardata;
						state <= 2;
					end
				end
				3'd2:
					finish <= 1;
			endcase
		end
	end

endmodule
