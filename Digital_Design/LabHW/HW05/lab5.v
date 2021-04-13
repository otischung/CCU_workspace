module lab5_birth(	
		input [2:0] cnt,
		output [3:0] birth_num,
		output reg [3:0] seg_data
	);

	reg [3:0] seg_number;

	//**CODE_CONVERTER**//
	assign birth_num[3] = (~cnt[2] & cnt[1]) | (~cnt[2] & cnt[0]);
	assign birth_num[2] = 0;
	assign birth_num[1] = (cnt[2] & ~cnt[1] & cnt[0]) | (cnt[2] & cnt[1] & ~cnt[0]);
	assign birth_num[0] = ~cnt[2] | cnt[0];
	/////////////////////

	always @(*) begin
		seg_data <= birth_num;
	end

	//**BCD_to_7SEG**//
	// always @(*) begin
	// 	case (seg_number)
	// 		4'd0: seg_data <= 7'b100_0000;
	// 		4'd1: seg_data <= 7'b111_1001;
	// 		4'd2: seg_data <= 7'b010_0100;
	// 		4'd3: seg_data <= 7'b011_0000;
	// 		4'd4: seg_data <= 7'b001_1001;
	// 		4'd5: seg_data <= 7'b001_0010;
	// 		4'd6: seg_data <= 7'b000_0010;
	// 		4'd7: seg_data <= 7'b101_1000;
	// 		4'd8: seg_data <= 7'b000_0000;
	// 		4'd9: seg_data <= 7'b001_0000;
	// 		default: seg_number <= seg_number;
	// 	endcase
	// end
	///////////////////
	
endmodule