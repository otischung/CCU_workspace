`include "lab5.v"
`timescale 1ms/1ms

module tb();
    reg [31:0] cnt;
    wire [7:0] seg;
    reg clk, rst;

    lab5 testfunc(clk, rst, seg);

    initial begin
        cnt <= 0;
        clk <= 1'b0;
        rst <= 1'b0;
        $dumpfile("lab5.fsdb");
        $dumpvars;
    end

    always #10 clk = ~clk;

    // always @(posedge clk or negedge rst) begin
    //     $display("%b", seg);
    // end

    always #8000 $finish;
endmodule
