module CLA_4bit(a,b,cin,sum);

    input  [3:0] a,b;
    input cin;
    output [3:0] sum;
    
    wire [3:0] g,p;
	wire [3:1] c;

    //generate g & p
    gp_generator gp_geneator1(a[3:0],b[3:0],g[3:0],p[3:0]); 
    
    //generate all carrys 
    carry_generator carry_geneator_c0(g[3:0],p[3:0],cin,c[3:1]);

    //generate sum
    sum_geneator geneate_sum(a[3:0],b[3:0],cin,c[3:1],sum[3:0]);    

endmodule

module gp_generator(a,b,g,p);

    input  [3:0] a,b;
    output [3:0] g,p;
    
    assign g = a & b;   // g = a x b
    assign p = a | b;   // p = a + b


endmodule

module carry_generator(g,p,cin,c);

    input [3:0] g,p;
    input cin;
    output [3:1] c;

    //create carries
    assign c[1] = g[0] | (p[0] & cin);
    assign c[2] = g[1] | (p[1] & g[0]) | (p[1] & p[0] & cin);
    assign c[3] = g[2] | (p[2] & g[1]) | (p[2] & p[1] & g[0]) | (p[2] & p[1] & p[0] & cin);
	
endmodule

module sum_geneator(a,b,cin,c,sum);

    input  [3:0] a,b;
    input cin;
	input  [3:1] c;
    output [3:0] sum;

    assign sum = a ^ b ^ {c,cin};

endmodule
