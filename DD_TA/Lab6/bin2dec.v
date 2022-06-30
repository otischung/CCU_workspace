module bin2dec(A, D2, D1, D0);
    input [7:0] A;
    output [3:0] D2;
    output [3:0] D1;
    output [3:0] D0;

    assign D0 = A % 10;
    assign D1 = (A / 10) % 10;
    assign D2 = (A / 100) % 10;
endmodule
