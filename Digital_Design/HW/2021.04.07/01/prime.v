module prime (
    input [3:0] in,
    output out
);

// SOP form
assign out = (~in[3] & ~in[2] & in[1]) | (~in[3] & in[2] & in[0]) | (in[2] & ~in[1] & in[0]) | (~in[2] & in[1] & in[0]);

// POS form
// assign out = (in[1] | in[0]) & (in[2] | in[1] | ~in[0]) & (~in[2] | ~in[1] | in[0]) & (~in[3] | ~in[1] | in[0]) & (~in[3] | ~in[2] | ~in[1]);

endmodule