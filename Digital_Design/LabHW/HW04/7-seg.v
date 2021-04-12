module top(clk, sw, CA, CB, CC, CD, CE, CF, CG,
		   AN0, AN1, AN2, AN3, AN4, AN5, AN6, AN7);
    
	input clk;
	input [11:0] sw;
	output CA,CB,CC,CD,CE,CF,CG;
	output AN0,AN1,AN2,AN3,AN4,AN5,AN6,AN7;
	
	wire [5:0] num1;
	wire [5:0] num2;
	wire [6:0] sum;
	reg [2:0] state;
	reg [6:0] seg_number,seg_data;
	reg [20:0] counter;
	reg [7:0] scan;
	reg invert;
	
	assign num1 = sw[11:6];
	assign num2 = sw[5:0];
	assign sum = num1 + num2;
	assign {AN7,AN6,AN5,AN4,AN3,AN2,AN1,AN0} = scan;
	assign {CG,CF,CE,CD,CC,CB,CA} = seg_data;
	
	always@(posedge clk) begin
	  counter <= (counter <= 100000) ? (counter + 1) : 0;
	  state <= (counter == 100000) ? (state + 1) : state;  // 每100000個clk改變一次state
		case(state)
			0:begin
				seg_number <= sum % 10;
				scan <= 8'b0111_1111;  // scan (update) from left to right.
				invert <= 1;
			end
			1:begin
				seg_number <= (sum / 10 ) % 10;
				scan <= 8'b1011_1111;
				invert <= 1;
			end
			2:begin
				seg_number <= (sum / 100 ) % 10;
				scan <= 8'b1101_1111;
				invert <= 1;
			end
			3:begin
				seg_number <= sum / 1000;
				scan <= 8'b1110_1111;
				invert <= 1;
			end
	
			4:begin
				seg_number <= sum / 1000;
				scan <= 8'b1111_0111;
				invert <= 0;
			end
			5:begin
				seg_number <= (sum / 100) % 10;
				scan <= 8'b1111_1011;
				invert <= 0;
			end
			6:begin
				seg_number <= (sum / 10) % 10;
				scan <= 8'b1111_1101;
				invert <= 0;
			end
			7:begin
				seg_number <= sum % 10;
				scan <= 8'b1111_1110;
				invert <= 0;
			end
	
			default: state <= state;
		endcase 
	end  
	
	always@(posedge clk) begin
		if (invert) begin
			case(seg_number)
			16'd0:seg_data <= 7'b100_0000;
			16'd1:seg_data <= 7'b100_1111;
			16'd2:seg_data <= 7'b001_0010;
			16'd3:seg_data <= 7'b000_0110;
			16'd4:seg_data <= 7'b000_1101;
			16'd5:seg_data <= 7'b010_0100;
			16'd6:seg_data <= 7'b010_0000;
			16'd7:seg_data <= 7'b100_1100;
			16'd8:seg_data <= 7'b000_0000;
			16'd9:seg_data <= 7'b000_0100;
			default: seg_number <= seg_number;
	  		endcase
		end
		else begin
			case(seg_number)
			16'd0:seg_data <= 7'b100_0000;
			16'd1:seg_data <= 7'b111_1001;
			16'd2:seg_data <= 7'b010_0100;
			16'd3:seg_data <= 7'b011_0000;
			16'd4:seg_data <= 7'b001_1001;
			16'd5:seg_data <= 7'b001_0010;
			16'd6:seg_data <= 7'b000_0010;
			16'd7:seg_data <= 7'b101_1000;
			16'd8:seg_data <= 7'b000_0000;
			16'd9:seg_data <= 7'b001_0000;
			default: seg_number <= seg_number;
			endcase
		end
	end 

endmodule
