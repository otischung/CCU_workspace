module gear (
    input [3:0] in,
    output [1:0] out
);

// SOP form
assign out[1] = (in[3] & in[2]) | (in[3] & in[1]);
assign out[0] = (~in[3] & in[2] & in[0]) | (~in[3] & in[2] & in[1]) | (in[3] & ~in[2] & ~in[1]) | (in[2] & in[1] & in[0]);

// POS form
// assign out[1] = in[3] & (in[2] | in[1]);
// assign out[0] = (in[3] | in[2]) & (in[2] | ~in[1]) & (~in[2] | in[1] | in[0]) & (~in[3] | ~in[1] | in[0]) & (~in[3] | ~in[2] | in[1]);

endmodule