`timescale 1ns / 1ps
module test_brench;
    reg a, b, c, d;
    reg [3:0] in;
    wire [2:0] out;
    reg clk, rst;

    sum DUT(a, b, c, d, out);

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
        {a, b, c, d} = in;
        if (rst) begin
            if (in <= 15) begin
                $display("a = %d, b = %d, c = %d, d = %d, sum = %d", a, b, c, d, out);
                in = in + 1;
            end
        end
    end

    always #160 $finish;
    
endmodule
