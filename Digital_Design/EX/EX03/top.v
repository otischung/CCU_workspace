`timescale 1ns / 1ps
module top(
    input [15:0] SW,
    output [15:0] LED
    );
    
    assign LED = SW;
endmodule
