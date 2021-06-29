module sum (
    input a, b, c, d,
    output [2:0] out
);

// SOP form
assign out[2] = a & b & c & d;
assign out[1] = (~a & c & d) | (b & ~c & d) | (b & c & ~d) | (a & b & ~c) | (a & ~b & d) | (a & ~b & c);
assign out[0] = (~a & ~b & ~c & d) | (~a & ~b & c & ~d) | (~a & b & ~c & ~d) | (~a & b & c & d) | (a & ~b & ~c & ~d) | (a & ~b & c & d) | (a & b & ~c & d) | (a & b & c & ~d);

// POS form
// assign out[2] = a & b & c & d;
// assign out[1] = (a | c | d) & (b | c | d) & (a | b | c) & (a | b | d) & (~a | ~b | ~c | ~d);
// assign out[0] = (a | b | c | d) & (a | b | ~c | ~d) & (a | ~b | c | ~d) & (a | ~b | ~c | d) & (~a | b | c | ~d) & (~a | b | ~c | d) & (~a | ~b | c | d) & (~a | ~b | ~c | ~d);

endmodule