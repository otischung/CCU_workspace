module JAM (
	input CLK,
	input RST,
	output reg [2:0] W,
	output reg [2:0] J,
	input [6:0] Cost,
	output reg [3:0] MatchCount,
	output reg [9:0] MinCost,
	output reg Valid
);

	initial begin
		$dumpfile("JAM.vcd");
		$dumpvars(0, testfixture);
		for (i = 0; i < 8; i = i + 1)
			$dumpvars(1, num[i]);
	end

	reg [5:0] state;
	integer i;

	reg [5:0] num [0:7];
	reg [5:0] ix;
	reg [19:0] maxcount;
	reg [19:0] total;
	always @(posedge CLK or posedge RST) begin
		if (RST) begin
			state <= 0;
			ix <= 0;
			total <= 0;
			MinCost <= 999;
			maxcount <= 0;
			Valid <= 0;
		end else begin
			case (state)
				// 6'd0: begin
				// 	state <= 1;
				// end
				// 6'd1: begin
				// 	state <= 2;
				// end
				// 6'd2: begin
				// 	state <= 3;
				// end

				6'd0: begin
					state <= 1;
					total <= 0;
					W <= ix;
					J <= num[ix];
					ix <= ix + 1;
					maxcount <= maxcount + 1;
				end
				6'd1: begin
					if (ix >= 8) begin
						ix <= 0;
						state <= 3;
						total <= total + Cost;
					end else begin
						ix <= ix + 1;
						W <= ix;
						J <= num[ix];
						total <= total + Cost;
					end
				end
				6'd3: begin
					if (maxcount == 40320) begin
						state <= 4;
					end else if (MinCost > total) begin
						MinCost <= total;
						MatchCount <= 1;
						state <= 0;
					end else if(MinCost == total) begin
						MatchCount <= MatchCount + 1;
						state <= 0;
					end else begin
						state <= 0;
					end
				end
				6'd4: begin
					Valid <= 1;
					state <= 5;
				end
				6'd5: begin
					Valid <= 0;
				end
			endcase
		end
	end


	reg [3:0]step;
	reg [3:0]ron;

	always @(posedge CLK or posedge RST) begin
		if (RST) begin
			step <= 0;
		end else if (state == 0)
			step <= 0;
		else begin
			step <= step + 1;
		end
	end

	
	// always @(posedge CLK or posedge RST) begin
	// 	if (RST) begin
	// 		data0 <= 0;
	// 		data1 <= 1;
	// 		data2 <= 2;
	// 		data3 <= 3;
	// 		data4 <= 4;
	// 		data5 <= 5;
	// 		data6 <= 6;
	// 		data7 <= 7;
	// 	end else if (step == 4) begin
	// 		data0 <= outdata0;
	// 		data1 <= outdata1;
	// 		data2 <= outdata2;
	// 		data3 <= outdata3;
	// 		data4 <= outdata4;
	// 		data5 <= outdata5;
	// 		data6 <= outdata6;
	// 		data7 <= outdata7;
	// 	end
	// end
	

	always @(posedge CLK or posedge RST) begin
		if (RST) begin
			num[0] <= 0;
			num[1] <= 1;
			num[2] <= 2;
			num[3] <= 3;
			num[4] <= 4;
			num[5] <= 5;
			num[6] <= 6;
			num[7] <= 7;
		end else if (state == 3) begin
			if (num[6] < num[7]) begin  // 01234567
				num[0] <= num[0];
				num[1] <= num[1];
				num[2] <= num[2];
				num[3] <= num[3];
				num[4] <= num[4];
				num[5] <= num[5];
				num[6] <= num[7];
				num[7] <= num[6];
			end
			else if (num[5] < num[6]) begin  // 01234576
				if (num[7] < num[5]) begin
					num[0] <= num[0];
					num[1] <= num[1];
					num[2] <= num[2];
					num[3] <= num[3];
					num[4] <= num[4];
					num[5] <= num[6];
					num[6] <= num[7];
					num[7] <= num[5];
				end else begin
					num[0] <= num[0];
					num[1] <= num[1];
					num[2] <= num[2];
					num[3] <= num[3];
					num[4] <= num[4];
					num[5] <= num[7];
					num[6] <= num[5];
					num[7] <= num[6];
				end
			end else if (num[4] < num[5]) begin  // 51234760
				if (num[6] < num[4]) begin
					num[0] <= num[0];
					num[1] <= num[1];
					num[2] <= num[2];
					num[3] <= num[3];
					num[4] <= num[5];
					num[5] <= num[7];
					num[6] <= num[6];
					num[7] <= num[4];
				end else if(num[7] < num[4]) begin
					num[0] <= num[0];
					num[1] <= num[1];
					num[2] <= num[2];
					num[3] <= num[3];
					num[4] <= num[6];
					num[5] <= num[7];
					num[6] <= num[4];
					num[7] <= num[5];
				end else begin
					num[0] <= num[0];
					num[1] <= num[1];
					num[2] <= num[2];
					num[3] <= num[3];
					num[4] <= num[7];
					num[5] <= num[4];
					num[6] <= num[6];
					num[7] <= num[5];
				end
			end else if (num[3] < num[4]) begin  // 01237654
				if (num[5] < num[3]) begin
					num[0] <= num[0];
					num[1] <= num[1];
					num[2] <= num[2];
					num[3] <= num[4];
					num[4] <= num[7];
					num[5] <= num[6];
					num[6] <= num[5];
					num[7] <= num[3];
				end else if (num[6] < num[3]) begin
					num[0] <= num[0];
					num[1] <= num[1];
					num[2] <= num[2];
					num[3] <= num[5];
					num[4] <= num[7];
					num[5] <= num[6];
					num[6] <= num[3];
					num[7] <= num[4];
				end else if (num[7] < num[3]) begin
					num[0] <= num[0];
					num[1] <= num[1];
					num[2] <= num[2];
					num[3] <= num[6];
					num[4] <= num[7];
					num[5] <= num[3];
					num[6] <= num[5];
					num[7] <= num[4];
				end else begin
					num[0] <= num[0];
					num[1] <= num[1];
					num[2] <= num[2];
					num[3] <= num[7];
					num[4] <= num[3];
					num[5] <= num[6];
					num[6] <= num[5];
					num[7] <= num[4];
				end
			end else if (num[2] < num[3]) begin  // 01276543
				if (num[4] < num[2]) begin
					num[0] <= num[0];
					num[1] <= num[1];
					num[2] <= num[3];
					num[3] <= num[7];
					num[4] <= num[6];
					num[5] <= num[5];
					num[6] <= num[4];
					num[7] <= num[2];
				end else if (num[5] < num[2]) begin
					num[0] <= num[0];
					num[1] <= num[1];
					num[2] <= num[4];
					num[3] <= num[7];
					num[4] <= num[6];
					num[5] <= num[5];
					num[6] <= num[2];
					num[7] <= num[3];
				end else if (num[6] < num[2]) begin
					num[0] <= num[0];
					num[1] <= num[1];
					num[2] <= num[5];
					num[3] <= num[7];
					num[4] <= num[6];
					num[5] <= num[2];
					num[6] <= num[4];
					num[7] <= num[3];
				end else if (num[7] < num[2]) begin
					num[0] <= num[0];
					num[1] <= num[1];
					num[2] <= num[6];
					num[3] <= num[7];
					num[4] <= num[2];
					num[5] <= num[5];
					num[6] <= num[4];
					num[7] <= num[3];
				end else begin
					num[0] <= num[0];
					num[1] <= num[1];
					num[2] <= num[7];
					num[3] <= num[2];
					num[4] <= num[6];
					num[5] <= num[5];
					num[6] <= num[4];
					num[7] <= num[3];
				end
			end else if (num[1] < num[2]) begin  // 01765432
				if (num[3] < num[1]) begin
					num[0] <= num[0];
					num[1] <= num[2];
					num[2] <= num[7];
					num[3] <= num[6];
					num[4] <= num[5];
					num[5] <= num[4];
					num[6] <= num[3];
					num[7] <= num[1];
				end else if (num[4] < num[1]) begin
					num[0] <= num[0];
					num[1] <= num[3];
					num[2] <= num[7];
					num[3] <= num[6];
					num[4] <= num[5];
					num[5] <= num[4];
					num[6] <= num[1];
					num[7] <= num[2];
				end else if (num[5] < num[1]) begin
					num[0] <= num[0];
					num[1] <= num[4];
					num[2] <= num[7];
					num[3] <= num[6];
					num[4] <= num[5];
					num[5] <= num[1];
					num[6] <= num[3];
					num[7] <= num[2];
				end else if (num[6] < num[1]) begin
					num[0] <= num[0];
					num[1] <= num[5];
					num[2] <= num[7];
					num[3] <= num[6];
					num[4] <= num[1];
					num[5] <= num[4];
					num[6] <= num[3];
					num[7] <= num[2];
				end else if (num[7] < num[1]) begin
					num[0] <= num[0];
					num[1] <= num[6];
					num[2] <= num[7];
					num[3] <= num[1];
					num[4] <= num[5];
					num[5] <= num[4];
					num[6] <= num[3];
					num[7] <= num[2];
				end else begin
					num[0] <= num[0];
					num[1] <= num[7];
					num[2] <= num[1];
					num[3] <= num[6];
					num[4] <= num[5];
					num[5] <= num[4];
					num[6] <= num[3];
					num[7] <= num[2];
				end
			end else if (num[0] < num[1]) begin  // 07654321
				if (num[2] < num[0]) begin
					num[0] <= num[1];
					num[1] <= num[7];
					num[2] <= num[6];
					num[3] <= num[5];
					num[4] <= num[4];
					num[5] <= num[3];
					num[6] <= num[2];
					num[7] <= num[0];
				end else if (num[3] < num[0]) begin
					num[0] <= num[2];
					num[1] <= num[7];
					num[2] <= num[6];
					num[3] <= num[5];
					num[4] <= num[4];
					num[5] <= num[3];
					num[6] <= num[0];
					num[7] <= num[1];
				end else if (num[4] < num[0]) begin
					num[0] <= num[3];
					num[1] <= num[7];
					num[2] <= num[6];
					num[3] <= num[5];
					num[4] <= num[4];
					num[5] <= num[0];
					num[6] <= num[2];
					num[7] <= num[1];
				end else if(num[5] < num[0]) begin
					num[0] <= num[4];
					num[1] <= num[7];
					num[2] <= num[6];
					num[3] <= num[5];
					num[4] <= num[0];
					num[5] <= num[3];
					num[6] <= num[2];
					num[7] <= num[1];
				end
				else if (num[6] < num[0]) begin
					num[0] <= num[5];
					num[1] <= num[7];
					num[2] <= num[6];
					num[3] <= num[0];
					num[4] <= num[4];
					num[5] <= num[3];
					num[6] <= num[2];
					num[7] <= num[1];
				end else if (num[7] < num[0]) begin
					num[0] <= num[6];
					num[1] <= num[7];
					num[2] <= num[0];
					num[3] <= num[5];
					num[4] <= num[4];
					num[5] <= num[3];
					num[6] <= num[2];
					num[7] <= num[1];
				end else begin
					num[0] <= num[7];
					num[1] <= num[0];
					num[2] <= num[6];
					num[3] <= num[5];
					num[4] <= num[4];
					num[5] <= num[3];
					num[6] <= num[2];
					num[7] <= num[1];
				end
			end else begin  // down
				num[0] <= num[0];
				num[1] <= num[1];
				num[2] <= num[2];
				num[3] <= num[3];
				num[4] <= num[4];
				num[5] <= num[5];
				num[6] <= num[6];
				num[7] <= num[7];
			end
		end
	end
	
	// reg [5:0] rightflag;
	// reg [5:0] findswap;

	// always @(posedge CLK or posedge RST) begin
	// 	if (RST) begin
	// 		num[0] <= 0;
	// 		num[1] <= 1;
	// 		num[2] <= 2;
	// 		num[3] <= 3;
	// 		num[4] <= 4;
	// 		num[5] <= 5;
	// 		num[6] <= 6;
	// 		num[7] <= 7;
	// 	end else if (state == 2 && ron) begin
	// 		num[rightflag] <= num[findswap];
	// 		num[findswap] <= num[rightflag];
	// 	end else if (state == 3 && ron) begin
	// 		if (rightflag == 5) begin
	// 			num[6] <= num[7];
	// 			num[7] <= num[6];
	// 		end else if (rightflag == 4) begin
	// 			num[5] <= num[7];
	// 			num[7] <= num[5];
	// 		end else if (rightflag == 3) begin
	// 			num[4] <= num[7];
	// 			num[5] <= num[6];
	// 			num[6] <= num[5];
	// 			num[7] <= num[4];
	// 		end else if (rightflag == 2) begin
	// 			num[3] <= num[7];
	// 			num[4] <= num[6];
	// 			num[6] <= num[4];
	// 			num[7] <= num[3];
	// 		end else if (rightflag == 1) begin
	// 			num[2] <= num[7];
	// 			num[3] <= num[6];
	// 			num[4] <= num[5];
	// 			num[5] <= num[4];
	// 			num[6] <= num[3];
	// 			num[7] <= num[2];
	// 		end else if (rightflag == 0) begin
	// 			num[1] <= num[7];
	// 			num[2] <= num[6];
	// 			num[3] <= num[5];
	// 			num[5] <= num[3];
	// 			num[6] <= num[2];
	// 			num[7] <= num[1];
	// 		end
	// 	end
	// end


	// always @(posedge CLK or posedge RST) begin
	// 	if (RST) begin
	// 		rightflag <= 6;
	// 	end else if (state == 0) begin
	// 		if (num[6] < num[7])		rightflag <= 6;
	// 		else if (num[5] < num[6])	rightflag <= 5;
	// 		else if (num[4] < num[5])	rightflag <= 4;
	// 		else if (num[3] < num[4])	rightflag <= 3;
	// 		else if (num[2] < num[3])	rightflag <= 2;
	// 		else if (num[1] < num[2])	rightflag <= 1;
	// 		else if (num[0] < num[1])	rightflag <= 0;
	// 	end
	// end

	// always @(posedge CLK or posedge RST) begin
	// 	if (RST) begin
	// 		findswap <= 0;
	// 	end else if (state == 1) begin
	// 		if (num[rightflag] <= num[7])		findswap <= 7;
	// 		else if (num[rightflag] <= num[6])	findswap <= 6;
	// 		else if (num[rightflag] <= num[5])	findswap <= 5;
	// 		else if (num[rightflag] <= num[4])	findswap <= 4;
	// 		else if (num[rightflag] <= num[3])	findswap <= 3;
	// 		else if (num[rightflag] <= num[2])	findswap <= 2;
	// 		else if (num[rightflag] <= num[1])	findswap <= 1;
	// 		else if (num[rightflag] <= num[0])	findswap <= 0;
	// 	end
	// end

endmodule
