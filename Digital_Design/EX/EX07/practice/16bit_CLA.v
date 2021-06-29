module CLA_16bit(a,b,cin,sum);

    input  [15:0] a,b;
    input cin;
    output [15:0] sum;
    
    wire [15:0] g,p;
    wire [15:1] c;
    wire [3:0] gG,gP;
    
    //Write down your design here ---//
	
	  //generate g & p

		
	  //generate gG & gP, generate carries

	  //generate carries c4, c8, c12

		
	  //generate sum

    //-------------------------------//

endmodule

module gp_generator(a,b,g,p);

    input  [3:0] a,b;
    output [3:0] g,p;
   
    assign g = a & b;   // g = a x b
    assign p = a ^ b;   // p = a + b

endmodule

module carry_generator(g,p,cin,c,gG,gP);

    input [3:0] g,p;
    input cin;
    output gG,gP;
    output [3:1] c;

    //create gG and gP
    assign gG = g[3] | (p[3] & g[2]) | (p[3] & p[2] & g[1]) | (p[3] & p[2] & p[1] & g[0]);
	assign gP = p[3] & p[2] & p[1] & p[0];

    //create carries
    assign c[1] = g[0] | (p[0] & cin);
    assign c[2] = g[1] | (p[1] & g[0]) | (p[1] & p[0] & cin);
    assign c[3] = g[2] | (p[2] & g[1]) | (p[2] & p[1] & g[0]) | (p[2] & p[1] & p[0] & cin);

endmodule

module sum_generator(a,b,cin,c,sum);

    input  [15:0] a,b;
    input cin;
    input  [15:1] c;
    output [15:0] sum;

    //sum = a ^ b ^ c;
    assign sum = a ^ b ^ {c,cin};

endmodule