`timescale 1ns / 1ps
module test_brench;
    reg [2:0] in;
    wire [3:0] out;
    reg clk, rst;

    A19760319 DUT(in, out);

    initial begin
        clk <= 0;
        rst <= 0;
        in <= 3'b000;
        $monitor("input = %d, output = %d", in, out);
    end

    always #5 clk = ~clk;
    always #5 rst = ~rst;

    always @(posedge clk or negedge rst) begin
        if (rst) begin
            $monitor("input = %d, output = %d", in, out);
            if (in <= 7) begin
                in = in + 1;
            end
            if (in == 7) begin
                $finish;
            end
        end
    end
    
endmodule
