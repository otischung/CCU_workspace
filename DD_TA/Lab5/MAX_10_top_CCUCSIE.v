// ============================================================================
//   Ver  :| Author					:| Mod. Date :| Changes Made:
//   V1.1 :| Alexandra Du			:| 06/01/2016:| Added Verilog file
// ============================================================================


//=======================================================
//  This code is generated by Terasic System Builder
//=======================================================

`define ENABLE_ADC_CLOCK
`define ENABLE_CLOCK1
`define ENABLE_CLOCK2
`define ENABLE_SDRAM
`define ENABLE_HEX0
`define ENABLE_HEX1
`define ENABLE_HEX2
`define ENABLE_HEX3
`define ENABLE_HEX4
`define ENABLE_HEX5
`define ENABLE_KEY
`define ENABLE_LED
`define ENABLE_SW
`define ENABLE_VGA
`define ENABLE_ACCELEROMETER
`define ENABLE_ARDUINO
`define ENABLE_GPIO

module DE10_LITE_Golden_Top(

	//////////// ADC CLOCK: 3.3-V LVTTL //////////
`ifdef ENABLE_ADC_CLOCK
	input 		          		ADC_CLK_10,
`endif
	//////////// CLOCK 1: 3.3-V LVTTL //////////
`ifdef ENABLE_CLOCK1
	input 		          		MAX10_CLK1_50,
`endif
	//////////// CLOCK 2: 3.3-V LVTTL //////////
`ifdef ENABLE_CLOCK2
	input 		          		MAX10_CLK2_50,
`endif

	//////////// SDRAM: 3.3-V LVTTL //////////
`ifdef ENABLE_SDRAM
	output		    [12:0]		DRAM_ADDR,
	output		     [1:0]		DRAM_BA,
	output		          		DRAM_CAS_N,
	output		          		DRAM_CKE,
	output		          		DRAM_CLK,
	output		          		DRAM_CS_N,
	inout 		    [15:0]		DRAM_DQ,
	output		          		DRAM_LDQM,
	output		          		DRAM_RAS_N,
	output		          		DRAM_UDQM,
	output		          		DRAM_WE_N,
`endif

	//////////// SEG7: 3.3-V LVTTL //////////
`ifdef ENABLE_HEX0
	output		     [7:0]		HEX0,
`endif
`ifdef ENABLE_HEX1
	output		     [7:0]		HEX1,
`endif
`ifdef ENABLE_HEX2
	output		     [7:0]		HEX2,
`endif
`ifdef ENABLE_HEX3
	output		     [7:0]		HEX3,
`endif
`ifdef ENABLE_HEX4
	output		     [7:0]		HEX4,
`endif
`ifdef ENABLE_HEX5
	output		     [7:0]		HEX5,
`endif

	//////////// KEY: 3.3 V SCHMITT TRIGGER //////////
`ifdef ENABLE_KEY
	input 		     [1:0]		KEY,
`endif

	//////////// LED: 3.3-V LVTTL //////////
`ifdef ENABLE_LED
	output		     [9:0]		LEDR,
`endif

	//////////// SW: 3.3-V LVTTL //////////
`ifdef ENABLE_SW
	input 		     [9:0]		SW,
`endif

	//////////// VGA: 3.3-V LVTTL //////////
`ifdef ENABLE_VGA
	output		     [3:0]		VGA_B,
	output		     [3:0]		VGA_G,
	output		          		VGA_HS,
	output		     [3:0]		VGA_R,
	output		          		VGA_VS,
`endif

	//////////// Accelerometer: 3.3-V LVTTL //////////
`ifdef ENABLE_ACCELEROMETER
	output		          		GSENSOR_CS_N,
	input 		     [2:1]		GSENSOR_INT,
	output		          		GSENSOR_SCLK,
	inout 		          		GSENSOR_SDI,
	inout 		          		GSENSOR_SDO,
`endif

	//////////// Arduino: 3.3-V LVTTL //////////
`ifdef ENABLE_ARDUINO
	inout 		    [15:0]		ARDUINO_IO,
	inout 		          		ARDUINO_RESET_N,
`endif

	//////////// GPIO, GPIO connect to GPIO Default: 3.3-V LVTTL //////////
`ifdef ENABLE_GPIO
	inout 		    [35:0]		GPIO
`endif
);


	
	reg [7:0] seg;
	wire clk_1hz;
	reg [2:0] cnt;
	wire rst;
	
	assign rst = KEY[0] && KEY[1];

	div_clk d1(.clk(MAX10_CLK2_50), .rst(rst), .clk_1hz(clk_1hz));
	assign HEX0 = seg;
	assign HEX1 = 8'b1111_1111;
	assign HEX2 = 8'b1111_1111;
	assign HEX3 = 8'b1111_1111;
	assign HEX4 = 8'b1111_1111;
	assign HEX5 = 8'b1111_1111;
	// assign clk_1hz = clk;
	initial begin
		cnt <= 3'b000;
	end

	always @(posedge clk_1hz or negedge rst) begin
		if (!rst) begin
			seg <= 8'b1111_1111;
		end else begin
			case (cnt)
				3'd0: seg <= 8'b1100_0110;  // C
				3'd1: seg <= 8'b1100_0110;  // C
				3'd2: seg <= 8'b1100_0001;  // U
				3'd3: seg <= 8'b1100_0110;  // C
				3'd4: seg <= 8'b1001_0010;  // S
				3'd5: seg <= 8'b1111_1001;  // I
				3'd6: seg <= 8'b1000_0110;  // E
				default: seg <= 8'b1111_1111;
			endcase
		end
	end
	
	always @(posedge clk_1hz or negedge rst) begin
		if (!rst) begin
			cnt <= 3'b000;
		end else begin
			if (cnt < 3'd6) begin
				cnt <= cnt + 1;
			end else begin
				cnt <= 3'b000;
			end
		end
	end
endmodule

module div_clk(clk, rst, clk_1hz);
	input rst;
	input clk;
	output reg clk_1hz;
	integer counter;

	always @(posedge clk or negedge rst) begin  
		if (!rst)
			clk_1hz <= 0;
		else if (counter >= 25000000)
			clk_1hz <= ~clk_1hz;
	end

	always @(posedge clk or negedge rst) begin  
		if (!rst)
			counter <= 0;
		else if (counter >= 25000000)
			counter <= 0;
		else
			counter <= counter + 1;
	end
endmodule