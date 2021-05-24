module MPY(clk, a, b, p);
    
    input clk;
    input [7:0] a, b;
    output [15:0] p;

    wire [15:0] ext_a, ext_b;
    wire [15:0] sum00, sum01, sum02, sum03, sum04, sum05, sum06;
    wire [15:0] sum07, sum08, sum09, sum10, sum11, sum12, sum13;
    wire [15:0] ab00, ab01, ab02, ab03, ab04, ab05, ab06, ab07;  // ab00 = a * b[0]
    wire [15:0] ab08, ab09, ab10, ab11, ab12, ab13, ab14, ab15;

    assign ext_a = { {8{a[7]}}, a };
    assign ext_b = { {8{b[7]}}, b };

    arrand x00(ext_a, ext_b[0], ab00);
    arrand x01(ext_a, ext_b[1], ab01);
    arrand x02(ext_a, ext_b[2], ab02);
    arrand x03(ext_a, ext_b[3], ab03);
    arrand x04(ext_a, ext_b[4], ab04);
    arrand x05(ext_a, ext_b[5], ab05);
    arrand x06(ext_a, ext_b[6], ab06);
    arrand x07(ext_a, ext_b[7], ab07);
    arrand x08(ext_a, ext_b[8], ab08);
    arrand x09(ext_a, ext_b[9], ab09);
    arrand x10(ext_a, ext_b[10], ab10);
    arrand x11(ext_a, ext_b[11], ab11);
    arrand x12(ext_a, ext_b[12], ab12);
    arrand x13(ext_a, ext_b[13], ab13);
    arrand x14(ext_a, ext_b[14], ab14);
    arrand x15(ext_a, ext_b[15], ab15);

    RCA RCA00(clk, ab00, { ab01[14:0], 1'b0 }, sum00);
    RCA RCA01(clk, sum00, { ab02[13:0], 2'b0 }, sum01);
    RCA RCA02(clk, sum01, { ab03[12:0], 3'b0 }, sum02);
    RCA RCA03(clk, sum02, { ab04[11:0], 4'b0 }, sum03);
    RCA RCA04(clk, sum03, { ab05[10:0], 5'b0 }, sum04);
    RCA RCA05(clk, sum04, { ab06[9:0], 6'b0 }, sum05);
    RCA RCA06(clk, sum05, { ab07[8:0], 7'b0 }, sum06);
    RCA RCA07(clk, sum06, { ab08[7:0], 8'b0 }, sum07);
    RCA RCA08(clk, sum07, { ab09[6:0], 9'b0 }, sum08);
    RCA RCA09(clk, sum08, { ab10[5:0], 10'b0 }, sum09);
    RCA RCA10(clk, sum09, { ab11[4:0], 11'b0 }, sum10);
    RCA RCA11(clk, sum10, { ab12[3:0], 12'b0 }, sum11);
    RCA RCA12(clk, sum11, { ab13[2:0], 13'b0 }, sum12);
    RCA RCA13(clk, sum12, { ab14[1:0], 14'b0 }, sum13);
    RCA RCA14(clk, sum13, { ab15[0], 15'b0 }, p);

endmodule


module arrand(a, b, ab);
    
    input [15:0] a;
    input b;
    output [15:0] ab;

    assign ab[0] = a[0] & b;
    assign ab[1] = a[1] & b;
    assign ab[2] = a[2] & b;
    assign ab[3] = a[3] & b;
    assign ab[4] = a[4] & b;
    assign ab[5] = a[5] & b;
    assign ab[6] = a[6] & b;
    assign ab[7] = a[7] & b;
    assign ab[8] = a[8] & b;
    assign ab[9] = a[9] & b;
    assign ab[10] = a[10] & b;
    assign ab[11] = a[11] & b;
    assign ab[12] = a[12] & b;
    assign ab[13] = a[13] & b;
    assign ab[14] = a[14] & b;
    assign ab[15] = a[15] & b;

endmodule

module RCA(clk, a, b, sum);
    
    input clk;
    input [15:0] a, b;
    output [15:0] sum;
    wire [15:0]c;
    
    HA HA01(clk, a[0], b[0], sum[0], c[0]);
    FA FA01(clk, a[1], b[1], c[0], sum[1], c[1]);
    FA FA02(clk, a[2], b[2], c[1], sum[2], c[2]);
    FA FA03(clk, a[3], b[3], c[2], sum[3], c[3]);
    FA FA04(clk, a[4], b[4], c[3], sum[4], c[4]);
    FA FA05(clk, a[5], b[5], c[4], sum[5], c[5]);
    FA FA06(clk, a[6], b[6], c[5], sum[6], c[6]);
    FA FA07(clk, a[7], b[7], c[6], sum[7], c[7]);
    FA FA08(clk, a[8], b[8], c[7], sum[8], c[8]);
    FA FA09(clk, a[9], b[9], c[8], sum[9], c[9]);
    FA FA10(clk, a[10], b[10], c[9], sum[10], c[10]);
    FA FA11(clk, a[11], b[11], c[10], sum[11], c[11]);
    FA FA12(clk, a[12], b[12], c[11], sum[12], c[12]);
    FA FA13(clk, a[13], b[13], c[12], sum[13], c[13]);
    FA FA14(clk, a[14], b[14], c[13], sum[14], c[14]);
    FA FA15(clk, a[15], b[15], c[14], sum[15], c[15]);

endmodule

module FA(clk, a, b, cin, s, c);
    
    input clk;
    input a, b, cin;
    output reg s, c;

    always @(posedge clk) begin
        s <= a ^ b ^ cin;
        c <= ( a & b ) | ( b & cin ) | ( a & cin );
    end

endmodule

module HA(clk, a, b, s, c);
    
    input clk;
    input a, b;
    output reg s, c;

    always @(posedge clk) begin
        s <= a ^ b;
        c <= a & b;
    end
    
endmodule

/* Sign Extension ver.2

ext_a   |   a7      a7      a7      a7      a7      a7      a7      a7      a7   |  a6      a5      a4      a3      a2      a1      a0
ext_b   |   b7      b7      b7      b7      b7      b7      b7      b7      b7   |  b6      b5      b4      b3      b2      b1      b0
--------|-------------------------------------------------------------------------------------------------------------------------------
ab00    |   a7b0    a7b0    a7b0    a7b0    a7b0    a7b0    a7b0    a7b0    a7b0 /  a6b0    a5b0    a4b0    a3b0    a2b0    a1b0    a0b0
ab01    |   a7b1    a7b1    a7b1    a7b1    a7b1    a7b1    a7b1    a7b1 /  a6b1    a5b1    a4b1    a3b1    a2b1    a1b1    a0b1
ab02    |   a7b2    a7b2    a7b2    a7b2    a7b2    a7b2    a7b2 /  a6b2    a5b2    a4b2    a3b2    a2b2    a1b2    a0b2
ab03    |   a7b3    a7b3    a7b3    a7b3    a7b3    a7b3 /  a6b3    a5b3    a4b3    a3b3    a2b3    a1b3    a0b3
ab04    |   a7b4    a7b4    a7b4    a7b4    a7b4 /  a6b4    a5b4    a4b4    a3b4    a2b4    a1b4    a0b4
ab05    |   a7b5    a7b5    a7b5    a7b5 /  a6b5    a5b5    a4b5    a3b5    a2b5    a1b5    a0b5
ab06    |   a7b6    a7b6    a7b6 /  a6b6    a5b6    a4b6    a3b6    a2b6    a1b6    a0b6
ab07    |   a7b7____a7b7 /  a6b7    a5b7    a4b7    a3b7    a2b7    a1b7    a0b7
--------|-------------------------------------------------------------------------------------------------------------------------------
ab08    |   a7b7    a6b7    a5b7    a4b7    a3b7    a2b7    a1b7    a0b7
ab09    |   a6b7    a5b7    a4b7    a3b7    a2b7    a1b7    a0b7
ab10    |   a5b7    a4b7    a3b7    a2b7    a1b7    a0b7
ab11    |   a4b7    a3b7    a2b7    a1b7    a0b7
ab12    |   a3b7    a2b7    a1b7    a0b7
ab13    |   a2b7    a1b7    a0b7
ab14    |   a1b7    a0b7
ab15    |   a0b7

*/
