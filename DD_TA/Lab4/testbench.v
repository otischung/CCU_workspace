`include "Lab4.v"
`timescale 1ps / 1ps

module tb();
    reg [3:0] a, b;
    wire [7:0] p;
    reg clk;
    reg [8:0] cnt;

    Lab4 testfunc(a, b, p);

    initial begin
        a <= 0;
        b <= 0;
        cnt <= 0;
        clk <= 1'b0;
        $dumpfile("Lab4.fsdb");
        $dumpvars;
    end

    always #5 clk = ~clk;
    // always #2560 $finish;

    always @(posedge clk) begin
        $display("%d * %d = %d", a, b, p);
        if (p == a * b) begin
            cnt = cnt + 1;
        end
        if (a == 15 && b == 15) begin
            $display("\nCorrect count: %d", cnt);
            $finish;
        end
        else if (b == 15) begin
            a = a + 1;
        end
        b = b + 1;
    end
endmodule
