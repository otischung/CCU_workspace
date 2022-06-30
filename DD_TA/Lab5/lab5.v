// `include "divider.v"
module lab5(clk, rst, seg);
	input clk;
	input rst;
	output reg [7:0] seg;
	wire clk_1hz;
	reg [2:0] cnt;

	div_clk d1(.clk(clk), .rst(rst), .clk_1hz(clk_1hz));
	// assign clk_1hz = clk;
	initial begin
		cnt <= 0;
	end

	always @(posedge clk_1hz or negedge rst) begin
		case (cnt)
			3'd0: seg <= 8'b1111_1111;
			3'd1: seg <= 8'b1100_0110;  // C
			3'd2: seg <= 8'b1111_1111;
			3'd3: seg <= 8'b1001_0010;  // S
			3'd4: seg <= 8'b1111_1111;
			3'd5: seg <= 8'b1111_1001;  // I
			3'd6: seg <= 8'b1111_1111;
			3'd7: seg <= 8'b1000_0110;  // E
		endcase
		cnt = cnt + 1;
	end
	// seven_seg (.clk(), .seg_number(), .seg_data());
endmodule
