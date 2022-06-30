//以前者(1ns)為單位，以後者(1ns)的時間，查看一次電路的行為
`timescale 1ns/1ns
`include "multiplier.v"

module tb();
    reg [3:0] a, b;
    wire [7:0] p;
    reg clk;
    reg rst;

    initial begin
        clk <= 1'b0;
        rst <= 1'b1;
        a <= 4'd15;
        b <= 4'd7;
        $dumpfile("mul.fsdb");
		$dumpvars;
    end

    always #10 clk <= ~clk;
    always #500 rst <= ~rst;
    multiplier m1(clk, rst, a, b, p);
    always @(posedge clk) begin
        #150 $display("%d * %d = %d", a, b, p);
        #1170 $display("%d * %d = %d", a, b, p);
    end
    always #1500 $finish;
endmodule
