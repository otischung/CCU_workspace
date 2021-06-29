//以前者(1ns)為單位，以後者(1ps)的時間，查看一次電路的行為
`timescale 1ns/1ps

//宣告module名稱,輸出入名稱
module lab9_serial_radix_4_booth_multiplier(
	clk, 
	rst, 
	in_a, 
	in_b, 
	outProduct, 
	Product_Valid
);
// in_a * in_b = Product
// in_a is Multiplicand , in_b is Multiplier
					
//定義port, 包含input, output
input clk, rst;
input [7:0] in_a;			// Multiplicand
input [7:0] in_b;			// Multiplier
output [15:0] outProduct;
output Product_Valid;

reg [9:0] Mplicand;		//被乘數
reg [9:0] Mplier;		//乘數
reg [9:0] SignMplicand;
reg [19:0] Product;
reg Product_Valid;
reg [5:0] Counter;
reg sign;			//正負號判斷 (signed)
reg radix_bit;

assign outProduct = Product[15:0];

//Counter
always @(posedge clk or posedge rst) begin
	if (rst)
		Counter <= 6'b0;
	else
		Counter <= Counter + 6'b1;
end

//Product
always @(posedge clk or posedge rst) begin
	//初始化數值
	if (rst) begin
		Mplicand <= 10'b0;
		Mplier <= 10'b0;
        SignMplicand <= 10'b0;
        Product <= 20'b0;
        radix_bit <= 1'b0;
	end 
	//輸入乘數與被乘數
	else if (Counter == 6'd0) begin
		Mplicand <= { 2'b0, in_a };
		Mplier <= { 2'b0, in_b };
        SignMplicand <= { 2'b0, in_b };
        Product <= { 12'b0, in_b };
        radix_bit <= 1'b0;
	end 
	//乘法與數值移位
	else if (Counter <= 6'd5) begin
        // $display("Product: %d, round %d", Product, Counter);
		if ({ Product[1:0], radix_bit } == 3'b001 || { Product[1:0], radix_bit } == 3'b010) begin
            // $display("Before + A: %d", Product);
            // $display("A =  %d", { Mplicand, 10'b0 });
            Product = Product + { Mplicand, 10'b0 };
            // $display("After + A: %d", Product);
        end
        else if ({ Product[1:0], radix_bit } == 3'b101 || { Product[1:0], radix_bit } == 3'b110) begin
            // $display("Before - A: %d", Product);
            // $display("A =  %d", { Mplicand, 10'b0 });
            SignMplicand = ~Mplicand + 1;
            // $display("-A =  %d", { SignMplicand, 10'b0 });
            Product = Product + { SignMplicand, 10'b0 };
            // $display("After - A: %d", Product);
        end
        else if ({ Product[1:0], radix_bit } == 3'b011) begin
            // $display("Before + 2A: %d", Product);
            // $display("A =  %d", { Mplicand, 10'b0 });
            SignMplicand = Mplicand * 2;
            Product = Product + { SignMplicand, 10'b0 };
            // $display("After + 2A: %d", Product);
        end
        else if ({ Product[1:0], radix_bit } == 3'b100) begin
            // $display("Before - 2A: %d", Product);
            // $display("A =  %d", { Mplicand, 10'b0 });
            SignMplicand = ~(Mplicand * 2) + 1;
            // $display("-A =  %d", { SignMplicand, 10'b0 });
            Product = Product + { SignMplicand, 10'b0 };
            // $display("After - 2A: %d", Product);
        end
        else begin
            Product = Product;
        end
        
        // if (Product[19] == 1) begin  // sign extension
        //     { Product, radix_bit } = { Product, radix_bit } >> 2;
        //     Product[18] <= 1;
        //     Product[19] <= 1;
        // end
        // else begin
        //     { Product, radix_bit } = { Product, radix_bit } >> 2;
        // end

        { Product, radix_bit } = { Product, radix_bit } >> 2;
        if (Product[17] == 1) begin  // sign extension
            Product[18] <= 1;
            Product[19] <= 1;
        end

        // $display("After shift: %d", Product);
	end 
	else begin
		Product <= Product;
		Mplicand <= Mplicand;
		Mplier <= Mplier;
        radix_bit <= radix_bit;
	end
end

//Product_Valid
always @(posedge clk or posedge rst) begin
	if (rst)
		Product_Valid <= 1'b0;
	else if (Counter == 6'd6)
		Product_Valid <= 1'b1;
	else
		Product_Valid <= 1'b0;
end

endmodule
