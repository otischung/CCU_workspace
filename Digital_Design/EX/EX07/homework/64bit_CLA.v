module CLA_64bit(a,b,cin,sum);

    input [63:0] a,b;
    input cin;
    output [63:0] sum;
    
    //Write down your design here ---//
	
	  //generate g & p

		
	  //generate gG & gP, generate carries c0, c4, c8, c12, ... , c60

	
	  //generate all carries

		
		
	    
  		
	  //generate sum

    
    //-------------------------------//

endmodule

module gp_generator(a,b,g,p);

    input [3:0] a,b;
    output [3:0] g,p;

    assign g = a & b;
    assign p = a | b;

endmodule

module carry_generator(g,p,cin,c,gG,gP);

    input [3:0] g,p;
    input cin;
    output gG,gP;
    output [3:1] c;

	assign gG = g[3] | (p[3] & g[2]) | (p[3] & p[2] & g[1]) | (p[3] & p[2] & p[1] & g[0]);
	assign gP = p[3] & p[2] & p[1] & p[0];

    assign c[1] = g[0] | (p[0] & cin);
    assign c[2] = g[1] | (p[1] & g[0]) | (p[1] & p[0] & cin);
    assign c[3] = g[2] | (p[2] & g[1]) | (p[2] & p[1] & g[0]) | (p[2] & p[1] & p[0] & cin);

endmodule

module sum_generator(a,b,cin,c,sum);

    input [63:0] a,b;
    input cin;
    input [63:1] c;
    output [63:0] sum;
	

    assign sum = a ^ b ^ {c,cin};

endmodule