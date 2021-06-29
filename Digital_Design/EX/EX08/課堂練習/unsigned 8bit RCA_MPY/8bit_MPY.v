module MPY(clk, a, b, p);
    input clk;
    input [7:0] a, b;
    output [15:0] p;
    wire [7:0] ab0, ab1, ab2, ab3, ab4, ab5, ab6, ab7;
    wire [6:0] carry;
    wire [7:0] s0, s1, s2, s3, s4, s5, s6;

    arrand and0(a, b[0], ab0);
    arrand and1(a, b[1], ab1);
    arrand and2(a, b[2], ab2);
    arrand and3(a, b[3], ab3);
    arrand and4(a, b[4], ab4);
    arrand and5(a, b[5], ab5);
    arrand and6(a, b[6], ab6);
    arrand and7(a, b[7], ab7);


	//****************************************************//
	
	
			// write down your design here 
			
			
	//****************************************************//
	
endmodule

module arrand(a, b, ab);
    input [7:0] a;
    input b;
    output [7:0] ab;

    assign ab[0] = a[0] & b;
    assign ab[1] = a[1] & b;
    assign ab[2] = a[2] & b;
    assign ab[3] = a[3] & b;
    assign ab[4] = a[4] & b;
    assign ab[5] = a[5] & b;
    assign ab[6] = a[6] & b;
    assign ab[7] = a[7] & b;
endmodule

module FA(clk, a, b, cin, s, c);
    input clk;
    input a, b, cin;
    output reg s, c;
    always @(posedge clk) begin
        s <= (a ^ b ^ cin);
        c <= ( a & b ) + ( b & cin ) + ( cin & a );
    end
endmodule

module HA(clk, a, b, s, c);
    input clk;
    input a, b;
    output reg s, c;
    always @(posedge clk) begin
        s <=  a ^ b ;
        c <=  a & b ;
    end
endmodule

module HA1FA7(clk, a, b, c, s);
    input clk;
    input [7:0] a, b;
    output c;
    output [7:0] s;
    wire [7:0] carry;

    HA HA1(clk, a[0], b[0], s[0], carry[0]);
    FA FA1(clk, a[1], b[1], carry[0], s[1], carry[1]);
    FA FA2(clk, a[2], b[2], carry[1], s[2], carry[2]);
    FA FA3(clk, a[3], b[3], carry[2], s[3], carry[3]);
    FA FA4(clk, a[4], b[4], carry[3], s[4], carry[4]);
    FA FA5(clk, a[5], b[5], carry[4], s[5], carry[5]);
    FA FA6(clk, a[6], b[6], carry[5], s[6], carry[6]);
    FA FA7(clk, a[7], b[7], carry[6], s[7], carry[7]);

    assign c = carry[7];
endmodule

module HA2FA6(clk, a, b, c, s);
    input clk;
    input [7:0] a;
    input [6:0] b;
    output c;
    output [7:0] s;

    wire [7:0] carry;

    HA HA1(clk, a[0], b[0], s[0], carry[0]);
    FA FA1(clk, a[1], b[1], carry[0], s[1], carry[1]);
    FA FA2(clk, a[2], b[2], carry[1], s[2], carry[2]);
    FA FA3(clk, a[3], b[3], carry[2], s[3], carry[3]);
    FA FA4(clk, a[4], b[4], carry[3], s[4], carry[4]);
    FA FA5(clk, a[5], b[5], carry[4], s[5], carry[5]);
    FA FA6(clk, a[6], b[6], carry[5], s[6], carry[6]);
    HA HA2(clk, a[7], carry[6], s[7], carry[7]);

    assign c = carry[7];
endmodule