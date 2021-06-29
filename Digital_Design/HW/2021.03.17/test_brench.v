`timescale 1ns / 1ps
module test_brench;
    reg [2:0] in;
    wire [3:0] out;
    reg clk, rst;

    A19760319 DUT(in, out);

    initial begin
        clk <= 0;
        rst <= 0;
        in <= 0;
        $dumpfile("test.vcd");
        $dumpvars;
    end

    always #5 clk = ~clk;
    always #5 rst = ~rst;

    always @(posedge clk or negedge rst) begin
        if (rst) begin
            if (in <= 15) begin
                $display("input = %d, output = %d", in, out);
                in = in + 1;
            end
        end
    end

    always #80 $finish;
    
endmodule
