module MPY(clk, a, b, p);
    input clk;
    input [3:0] a, b;
    output [7:0] p;
    wire [3:0] ab0, ab1, ab2, ab3;
    wire [3:0] carry0, carry1, carry2;
    wire [3:0] s0, s1, s2;

    arrand and0(a, b[0], ab0);
    arrand and1(a, b[1], ab1);
    arrand and2(a, b[2], ab2);
    arrand and3(a, b[3], ab3);
	
	HA HA1_1(clk, ab1[0], ab0[1], s0[0], carry0[0]);
	FA FA1_1(clk, ab2[0], ab1[1], ab0[2], s0[1], carry0[1]);
	FA FA1_2(clk, ab2[1], ab1[2], ab0[3], s0[2], carry0[2]);	
	HA HA1_2(clk, ab2[2], ab1[3], s0[3], carry0[3]);
	
	HA HA2_1(clk, s0[1], carry0[0], s1[0], carry1[0]); 
	FA FA2_1(clk, ab3[0], s0[2], carry0[1], s1[1], carry1[1]);
	FA FA2_2(clk, ab3[1], s0[3], carry0[2], s1[2], carry1[2]);
	FA FA2_3(clk, ab3[2], ab2[3], carry0[3], s1[3], carry1[3]);
	
	HA HA3_1(clk, s1[1], carry1[0], s2[0], carry2[0]);
	FA FA3_1(clk, s1[2], carry1[1], carry2[0], s2[1], carry2[1]);
	FA FA3_2(clk, s1[3], carry1[2], carry2[1], s2[2], carry2[2]);
	FA FA3_3(clk, ab3[3], carry1[3], carry2[2], s2[3], carry2[3]);
	
	assign p[0] = ab0[0];
	assign p[1] = s0[0];
	assign p[2] = s1[0];
	assign p[6:3] = s2[3:0];
	assign p[7] = carry2[3];
		
endmodule

module arrand(a, b, ab);
    input [3:0] a;
    input b;
    output [3:0] ab;

    assign ab[0] = a[0] & b;
    assign ab[1] = a[1] & b;
    assign ab[2] = a[2] & b;
    assign ab[3] = a[3] & b;
endmodule

module FA(clk, a, b, cin, s, c);
    input clk;
    input a, b, cin;
    output  reg s, c;
    always @(posedge clk) begin
        s <= (a ^ b ^ cin);
        c <= ( a & b ) + ( b & cin ) + ( cin & a );
    end
endmodule

module HA(clk, a, b, s, c);
    input clk;
    input a, b;
    output  reg s, c;
    always @(posedge clk) begin
        s <=  a ^ b ;
        c <=  a & b ;
    end
endmodule
