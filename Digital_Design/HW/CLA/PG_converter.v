module FA(a, b, cin, s, cout);
    
    input a, b, cin;
    output s, cout;

    assign s = a ^ b ^ cin;
    assign cout = (a & b) | (a & cin) | (b & cin);

endmodule


module PG2C (cin, p, g, cout);  // only use in produce cout
    
    input cin, p, g;
    output cout;

    assign cout = g | (p & cin);
    
endmodule


module FA4bitToPG(a, b, p, g);  // convert two inputs to generate and propagate
    
    input [3:0] a, b;
    output [3:0] p, g;

    assign p = a | b;
    assign g = a & b;

endmodule


module PG4bitToGroup(p, g, cin, P, G, c);  // Generate Group Propagate and Group Generate
    
    input [3:0] p, g;
    input cin;
    output P, G;
    output [3:1] c;

    assign P = p[3] & p[2] & p[1] & p[0];
    assign G = g[3] | (p[3] & g[2]) | (p[3] & p[2] & g[1]) | (p[3] & p[2] & p[1] & g[0]);
    assign c[1] = g[0] | (p[0] & cin);
    assign c[2] = g[1] | (p[1] & g[0]) | (p[1] & p[0] & cin);
    assign c[3] = g[2] | (p[2] & g[1]) | (p[2] & p[1] & g[0]) | (p[2] & p[1] & p[0] & cin);  

endmodule

module PG2bitToGroup(p, g, cin, P, G, c);  // Generate Group Propagate and Group Generate
    
    input [1:0] p, g;
    input cin;
    output P, G;
    output c;

    assign P = p[1] & p[0];
    assign G = g[1] | (p[1] & g[0]);
    assign c = g[0] | (p[0] & cin);

endmodule