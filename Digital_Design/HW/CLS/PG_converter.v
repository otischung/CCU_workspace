module FS(x, y, bin, d, bout);
    
    input x, y, bin;
    output d, bout;

    assign d = x ^ y ^ bin;
    assign bout = (~x & y) | (~x & bin) | (y & bin);

endmodule


module PG2B (bin, p, g, bout);  // only use in produce cout
    
    input bin, p, g;
    output bout;

    assign bout = g | (p & bin);
    
endmodule


module FS4bitToPG(a, b, p, g);  // convert two inputs to generate and propagate
    
    input [3:0] a, b;
    output [3:0] p, g;

    assign p = ~a | b;
    assign g = ~a & b;

endmodule


module PG4bitToGroup(p, g, bin, P, G, b);  // Generate Group Propagate and Group Generate
    
    input [3:0] p, g;
    input bin;
    output P, G;
    output [3:1] b;

    assign P = p[3] & p[2] & p[1] & p[0];
    assign G = g[3] | (p[3] & g[2]) | (p[3] & p[2] & g[1]) | (p[3] & p[2] & p[1] & g[0]);
    assign b[1] = g[0] | (p[0] & bin);
    assign b[2] = g[1] | (p[1] & g[0]) | (p[1] & p[0] & bin);
    assign b[3] = g[2] | (p[2] & g[1]) | (p[2] & p[1] & g[0]) | (p[2] & p[1] & p[0] & bin);  

endmodule

module PG2bitToGroup(p, g, bin, P, G, b);  // Generate Group Propagate and Group Generate
    
    input [1:0] p, g;
    input bin;
    output P, G;
    output b;

    assign P = p[1] & p[0];
    assign G = g[1] | (p[1] & g[0]);
    assign b = g[0] | (p[0] & bin);

endmodule