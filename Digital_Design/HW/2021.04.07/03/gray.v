module gray (
    input [3:0] in,
    output [3:0] out
);

// SOP form
assign out[3] = in[3];
assign out[2] = (in[3] & ~in[2]) | (~in[3] & in[2]);
assign out[1] = (in[2] & ~in[1]) | (~in[2] & in[1]);
assign out[0] = (in[1] & ~in[0]) | (~in[1] & in[0]);

// POS form
// assign out[3] = in[3];
// assign out[2] = (in[3] | in[2]) & (~in[3] | ~in[2]);
// assign out[1] = (in[2] | in[1]) & (~in[2] | ~in[1]);
// assign out[0] = (in[1] | in[0]) & (~in[1] | ~in[0]);

endmodule