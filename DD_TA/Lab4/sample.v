module AND2X1(A, B, Y);
    input A, B;
    output Y;

    assign Y = A & B;
endmodule 

module OR2X1(A, B, Y);
    input A, B;
    output Y;

    assign Y = A | B;
endmodule 

module NAND2X1(A, B, Y);
    input A, B;
    output Y;

    assign Y = !(A & B);
endmodule 

module XOR2X1(A, B, Y);
    input A, B;
    output Y;

    assign Y = (A & !B) | (!A & B);
endmodule 

module NOR2X1(A, B, Y);
    input A, B;
    output Y;

    assign Y = !( A | B );
endmodule 

module INVX1(A, Y);
    input A;
    output Y;

    assign Y = !A;
endmodule 
