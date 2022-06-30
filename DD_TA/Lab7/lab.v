module lab(
	input  CLOCK_50,
	input  [1:0] KEY,
	input  [9:0] SW,
	output [9:0] LEDR,
	output [7:0] HEX0,
	output [7:0] HEX1,
	output [7:0] HEX2,
	output [7:0] HEX3,
	output [7:0] HEX4,
	output [7:0] HEX5
);

	//		declaration 
	wire press;
	wire rst;
	wire [8:0] bright;
	reg  [3:0] state;
	reg  [3:0] nstate;
	reg  [3:0] counter;
	reg  [4:0] num[0:5];
	reg  [3:0] maxCnt;
	reg  [3:0] showCnt;
	//		end of declaration
	
	//		assignment 		//dont touch
	assign bright = SW[9:1];
	assign clk = CLOCK_50;
	assign {rst, press} = KEY;
	assign LEDR = SW;
	//		end of assignment
	
	//		sample
	// assign LEDR[0] = state[0] & state[1];
	//

	always @(posedge clk or negedge rst) begin
		if (!rst) begin
			showCnt <= 4'd0;
			maxCnt <= 4'd0;
		end else if (bright == 9'd0) begin  // brightness = 100%
			showCnt <= 4'd0;
			maxCnt <= 4'd0;
		end else if (bright == 9'd1) begin  // brightness = 90%
			showCnt <= 4'd1;
			maxCnt <= 4'd10;
		end else if (bright < 9'd4) begin  // brightness = 80%
			showCnt <= 4'd1;
			maxCnt <= 4'd5;
		end else if (bright < 9'd8) begin  // brightness = 70%
			showCnt <= 4'd3;
			maxCnt <= 4'd10;
		end else if (bright < 9'd16) begin  // brightness = 60%
			showCnt <= 4'd2;
			maxCnt <= 4'd5;
		end else if (bright < 9'd32) begin  // brightness = 50%
			showCnt <= 4'd1;
			maxCnt <= 4'd2;
		end else if (bright < 9'd64) begin  // brightness = 40%
			showCnt <= 4'd3;
			maxCnt <= 4'd5;
		end else if (bright < 9'd128) begin  // brightness = 30%
			showCnt <= 4'd7;
			maxCnt <= 4'd10;
		end else if (bright < 9'd256) begin  // brightness = 20%
			showCnt <= 4'd4;
			maxCnt <= 4'd5;
		end else begin  // brightness = 10%
			showCnt <= 4'd9;
			maxCnt <= 4'd10;
		end
	end

	always @(posedge clk or negedge rst) begin  // brightness
		if (!rst)
			counter <= 0;
		else if (counter == maxCnt)
			counter <= 0;
		else
			counter <= counter + 1;
	end
	
	// always @(posedge clk_1hz or negedge rst) begin
	always @(posedge clk or negedge rst) begin
		if (!rst)
			state <= 0;
		else
			state <= nstate;
	end
	
	always @(negedge press or negedge rst) begin
		if (!rst)
			nstate <= 0;
		else begin
			case (state)
				// Mon. password: 1010010
				4'h0: nstate <= (SW[0]) ? 4'h1 : 4'h0;
				4'h1: nstate <= (SW[0]) ? 4'h1 : 4'h2;
				4'h2: nstate <= (SW[0]) ? 4'h3 : 4'h0;
				4'h3: nstate <= (SW[0]) ? 4'h1 : 4'h4;
				4'h4: nstate <= (SW[0]) ? 4'h3 : 4'h5;
				4'h5: nstate <= (SW[0]) ? 4'h6 : 4'h0;
				4'h6: nstate <= (SW[0]) ? 4'h1 : 4'h7;
				4'h7: nstate <= (SW[0]) ? 4'h3 : 4'h0;

				// Wed. password: 1010100
				// 4'h0: nstate <= (SW[0]) ? 4'h1 : 4'h0;
				// 4'h1: nstate <= (SW[0]) ? 4'h1 : 4'h2;
				// 4'h2: nstate <= (SW[0]) ? 4'h3 : 4'h0;
				// 4'h3: nstate <= (SW[0]) ? 4'h1 : 4'h4;
				// 4'h4: nstate <= (SW[0]) ? 4'h5 : 4'h0;
				// 4'h5: nstate <= (SW[0]) ? 4'h1 : 4'h6;
				// 4'h6: nstate <= (SW[0]) ? 4'h5 : 4'h7;
				// 4'h7: nstate <= (SW[0]) ? 4'h1 : 4'h0;
				default: nstate <= nstate;
			endcase
		end
	end
	
	always @(posedge clk or negedge rst) begin  // brightness
		if (!rst) begin
			num[0] <= 0;
			num[1] <= 10;
			num[2] <= 10;
			num[3] <= 10;
			num[4] <= 10;
			num[5] <= 10;
		end else if (counter >= showCnt) begin  // show
			if (state == 7) begin  // success
				num[0] <= state;
				num[1] <= 10;
				num[2] <= 15;
				num[3] <= 14;
				num[4] <= 13;
				num[5] <= 12;
			end else begin
				num[0] <= state;
				num[1] <= 10;
				num[2] <= 10;
				num[3] <= 10;
				num[4] <= 10;
				num[5] <= 10;
			end
		end else begin  // don't show
			num[0] <= 10;
			num[1] <= 10;
			num[2] <= 10;
			num[3] <= 10;
			num[4] <= 10;
			num[5] <= 10;
		end
	end
	
	//		clock divider				//	dont touch
	div_clk		xc0(.clk(clk), .rst(rst), .clk_1hz(clk_1hz));
		
	//		seven segment decoder	//	dont touch
	seven_seg 	xs0(.clk(clk), .seg_number(num[0]), .seg_data(HEX0));
	seven_seg 	xs1(.clk(clk), .seg_number(num[1]), .seg_data(HEX1));
	seven_seg 	xs2(.clk(clk), .seg_number(num[2]), .seg_data(HEX2));
	seven_seg 	xs3(.clk(clk), .seg_number(num[3]), .seg_data(HEX3));
	seven_seg 	xs4(.clk(clk), .seg_number(num[4]), .seg_data(HEX4));
	seven_seg 	xs5(.clk(clk), .seg_number(num[5]), .seg_data(HEX5));
endmodule
