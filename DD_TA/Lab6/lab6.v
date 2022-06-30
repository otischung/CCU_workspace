module lab6(clk, rst, A, B, HEX0, HEX1, HEX2, HEX3, HEX4, HEX5, cnt);
	input clk;
	input rst;
	input [3:0] A;
	input [3:0] B;
	output [7:0] HEX0;
	output [7:0] HEX1;
	output [7:0] HEX2;
	output [7:0] HEX3;
	output [7:0] HEX4;
	output [7:0] HEX5;
	output reg [9:0] cnt;

	//		declaration 		//dont touch
	wire [4:0] CLAout;
	wire [4:0] RCAout;
	wire [7:0] multiout;
	wire [4:0] num0;
	wire [4:0] num1;	
	wire [4:0] num2;
	wire [4:0] num3;
	wire [4:0] num4;
	wire [4:0] num5;
	//		end of declaration
	
	
	//		sample code RCA			//	dont touch
	// RCA xl0(A, B, 1'b0, RCAout[3:0], RCAout[4]);  // Combinational
	RCA xl0(clk_1hz, rst, A, B, 1'b0, RCAout);
	
	//		lab 6-1 CLA
	// CLA xl1(A, B, 1'b0, CLAout[3:0], CLAout[4]);  // Combinational
	CLA xl1(clk_1hz, rst, A, B, 1'b0, CLAout);
	
	//		lab 6-2 multiplier
	// multiplier xl2(clk, rst, A, {1'b0, B[2:0]}, multiout);
	multiplier xl2(clk_1hz, rst, A, {1'b0, B[2:0]}, multiout);
	
	//		clock divider				//	dont touch
	div_clk	xc0(.clk(clk), .rst(rst), .clk_1hz(clk_1hz));
	
	//		binary to decimal			//	dont touch
	bin2dec	xb0(.A(RCAout  ), .D1(num1), .D0(num0));
	bin2dec	xb1(.A(CLAout  ), .D1(num3), .D0(num2));
	bin2dec	xb2(.A(multiout), .D1(num5), .D0(num4));
	
	//		seven segment decoder	//	dont touch
	seven_seg xs0(.clk(clk), .seg_number(num0), .seg_data(HEX0));
	seven_seg xs1(.clk(clk), .seg_number(num1), .seg_data(HEX1));
	seven_seg xs2(.clk(clk), .seg_number(num2), .seg_data(HEX2));
	seven_seg xs3(.clk(clk), .seg_number(num3), .seg_data(HEX3));
	seven_seg xs4(.clk(clk), .seg_number(num4), .seg_data(HEX4));
	seven_seg xs5(.clk(clk), .seg_number(num5), .seg_data(HEX5));

	initial begin
		cnt <= 10'b00000_00000;
	end

	always @(posedge clk_1hz or negedge rst) begin
		if (!rst) begin
			cnt <= 10'b00000_00000;
		end else begin
			cnt <= cnt + 1;
		end
	end
endmodule
