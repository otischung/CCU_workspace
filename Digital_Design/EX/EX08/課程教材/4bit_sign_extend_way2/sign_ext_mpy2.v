`include "FA.v"
`include "HA.v"
module MPY(clk, a, b, product);
    input clk;
    input [3:0] a, b;
    wire [7:0] ab0, ab1, ab2, ab3, ab4, ab5, ab6, ab7;
    // wire [7:0] add0, add1, add2, add3;
    // wire [7:0] ext0, ext1, ext2, ext3;
    wire [7:0] sum0, sum1, sum2, sum3, sum4, sum5;
	wire [7:0] ext_a, ext_b;
    output [7:0] product;
	
	assign ext_a = {{4{a[3]}}, a};
	assign ext_b = {{4{b[3]}}, b};

    arrand and0(ext_a, ext_b[0], ab0);
    arrand and1(ext_a, ext_b[1], ab1);
    arrand and2(ext_a, ext_b[2], ab2);
    arrand and3(ext_a, ext_b[3], ab3);
    arrand and4(ext_a, ext_b[4], ab4);
    arrand and5(ext_a, ext_b[5], ab5);
    arrand and6(ext_a, ext_b[6], ab6);
    arrand and7(ext_a, ext_b[7], ab7);

	adder adder1(clk, ab0, {ab1[6:0], 1'b0}, sum0);
	adder adder2(clk, sum0, {ab2[5:0], 2'b0}, sum1);
	adder adder3(clk, sum1, {ab3[4:0], 3'b0}, sum2);
	adder adder4(clk, sum2, {ab4[3:0], 4'b0}, sum3);
	adder adder5(clk, sum3, {ab5[2:0], 5'b0}, sum4);
	adder adder6(clk, sum4, {ab6[1:0], 6'b0}, sum5);
	adder adder7(clk, sum5, {ab7[0], 7'b0}, product);	

endmodule

module arrand(a, b, ab);
    input [7:0] a;
    input b;
    output [7:0] ab;

    assign ab[0] = a[0] & b;
    assign ab[1] = a[1] & b;
    assign ab[2] = a[2] & b;
    assign ab[3] = a[3] & b;
    assign ab[4] = a[4] & b;
    assign ab[5] = a[5] & b;
    assign ab[6] = a[6] & b;
    assign ab[7] = a[7] & b;
endmodule

module adder(clk, a, b, sum);
    input clk;
    input [7:0] a, b;
    output [7:0] sum;
    wire [7:0]c;
    
    HA HA1(clk, a[0], b[0], sum[0], c[0]);
    FA FA1(clk, a[1], b[1], c[0], sum[1], c[1]);
    FA FA2(clk, a[2], b[2], c[1], sum[2], c[2]);
    FA FA3(clk, a[3], b[3], c[2], sum[3], c[3]);
    FA FA4(clk, a[4], b[4], c[3], sum[4], c[4]);
    FA FA5(clk, a[5], b[5], c[4], sum[5], c[5]);
    FA FA6(clk, a[6], b[6], c[5], sum[6], c[6]);
    FA FA7(clk, a[7], b[7], c[6], sum[7], c[7]);                        
endmodule
