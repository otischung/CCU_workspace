module CLA_16bit(a, b, cin, sum);

    input  [15:0] a, b;
    input cin;
    output [15:0] sum;
    
    wire [15:0] g, p;
    wire [15:1] c;
    wire [3:0] gG, gP;
    
    //Write down your design here ---//
	
        //generate g & p
        gp_generator gp00(a[3:0], b[3:0], g[3:0], p[3:0]);
        gp_generator gp04(a[7:4], b[7:4], g[7:4], p[7:4]);
        gp_generator gp08(a[11:8], b[11:8], g[11:8], p[11:8]);
        gp_generator gp12(a[15:12], b[15:12], g[15:12], p[15:12]);
		
        //generate gG & gP, generate carries
        carry_generator cg00(g[3:0], p[3:0], cin, c[3:1], gG[0], gP[0]);
        carry_generator cg04(g[7:4], p[7:4], c[4], c[7:5], gG[1], gP[1]);
        carry_generator cg08(g[11:8], p[11:8], c[8], c[11:9], gG[2], gP[2]);
        carry_generator cg12(g[15:12], p[15:12], c[12], c[15:13], gG[3], gP[3]);

        //generate carries c4, c8, c12
        assign c[4]  = gG[0] | (gP[0] & cin);
        assign c[8]  = gG[1] | (gP[1] & c[4]);
        assign c[12] = gG[2] | (gP[2] & c[8]);
		
	    //generate sum
        sum_generator sg(a, b, cin, c, sum);

    //-------------------------------//

endmodule

module gp_generator(a, b, g, p);

    input  [3:0] a, b;
    output [3:0] g, p;
   
    assign g = a & b;   // g = a x b
    assign p = a ^ b;   // p = a + b

endmodule

module carry_generator(g, p, cin, c, gG, gP);

    input [3:0] g, p;
    input cin;
    output gG, gP;
    output [3:1] c;

    //create gG and gP
    assign gG = g[3] | (p[3] & g[2]) | (p[3] & p[2] & g[1]) | (p[3] & p[2] & p[1] & g[0]);
	assign gP = p[3] & p[2] & p[1] & p[0];

    //create carries
    assign c[1] = g[0] | (p[0] & cin);
    assign c[2] = g[1] | (p[1] & g[0]) | (p[1] & p[0] & cin);
    assign c[3] = g[2] | (p[2] & g[1]) | (p[2] & p[1] & g[0]) | (p[2] & p[1] & p[0] & cin);

endmodule

module sum_generator(a, b, cin, c, sum);

    input  [15:0] a, b;
    input cin;
    input  [15:1] c;
    output [15:0] sum;

    assign sum = a ^ b ^ {c, cin};

endmodule
