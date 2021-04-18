module prime (
    input [3:0] in,
    output out
);

// BCD, 10~15 don't care.
wire w1, w2;

nand nand2(w1, ~in[2], in[1]);
nand nand2(w2, in[2], in[0]);
nand nand2(out, w1, w2);

// binary code
// SOP form
// assign out = (~in[2] & in[1]) | (in[2] & in[0]);

// POS form
// assign out = (in[1] | in[0]) & (in[2] | in[1] | ~in[0]) & (~in[2] | ~in[1] | in[0]) & (~in[3] | ~in[1] | in[0]) & (~in[3] | ~in[2] | ~in[1]);

endmodule