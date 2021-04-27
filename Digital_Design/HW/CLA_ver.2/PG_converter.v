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


module FAPG(a, b, cin, p, g);  // convert two inputs to generate and propagate
    input a, b, cin;
    output p, g;

    assign p = a | b;
    assign g = a & b;

endmodule


module PG2Group(p, g, P, G);  // Generate Group Propagate and Group Generate
    input [3:0] p, g;
    output P, G;

    assign P = p[3] & p[2] & p[1] & p[0];
    assign G = g[3] | (p[3] & g[2]) | (p[3] & p[2] & g[1]) | (p[3] & p[2] & p[1] & g[0]);

endmodule
