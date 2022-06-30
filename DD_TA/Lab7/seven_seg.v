module seven_seg(clk, seg_number, seg_data);
	input  clk;
	input  [3:0] seg_number;
	output reg [7:0] seg_data;

	always @(posedge clk) begin
		case (seg_number)
			4'd0: seg_data <= 8'b1100_0000;
			4'd1: seg_data <= 8'b1111_1001;
			4'd2: seg_data <= 8'b1010_0100;
			4'd3: seg_data <= 8'b1011_0000;
			4'd4: seg_data <= 8'b1001_1001;
			4'd5: seg_data <= 8'b1001_0010;
			4'd6: seg_data <= 8'b1000_0010;
			4'd7: seg_data <= 8'b1101_1000;
			4'd8: seg_data <= 8'b1000_0000;
			4'd9: seg_data <= 8'b1001_0000;
			4'd10: seg_data <= 8'b1111_1111;
			4'd11: seg_data <= 8'b1111_1111;
			4'd12: seg_data <= 8'b1010_0011;  // o
			4'd13: seg_data <= 8'b1000_1100;  // P
			4'd14: seg_data <= 8'b1000_0110;  // E
			4'd15: seg_data <= 8'b1010_1011;  // n
			default: seg_data <= seg_data;
		endcase
	end
endmodule
