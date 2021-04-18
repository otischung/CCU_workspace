`timescale 1ns / 1ps
module test_brench;
    reg [3:0] in;
    wire out;
    reg clk, rst;

    prime DUT(in, out);

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
            if (in == 10) begin
                $finish;
            end
        end
    end

    // always #160 $finish;
    
endmodule
