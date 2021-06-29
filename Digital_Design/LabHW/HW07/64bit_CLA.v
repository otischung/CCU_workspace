`include "16bit_CLA.v"
module CLA_64bit(a, b, cin, sum);

    input [63:0] a, b;
    input cin;
    output [63:0] sum;

    wire [63:0] g, p;
    wire [63:1] c;
    wire [15:0] gG, gP;
    
    //Write down your design here ---//
	
        //generate g & p
        gp_generator gp00(a[3:0], b[3:0], g[3:0], p[3:0]);
        gp_generator gp04(a[7:4], b[7:4], g[7:4], p[7:4]);
        gp_generator gp08(a[11:8], b[11:8], g[11:8], p[11:8]);
        gp_generator gp12(a[15:12], b[15:12], g[15:12], p[15:12]);
        gp_generator gp16(a[19:16], b[19:16], g[19:16], p[19:16]);
        gp_generator gp20(a[23:20], b[23:20], g[23:20], p[23:20]);
        gp_generator gp24(a[27:24], b[27:24], g[27:24], p[27:24]);
        gp_generator gp28(a[31:28], b[31:28], g[31:28], p[31:28]);
        gp_generator gp32(a[35:32], b[35:32], g[35:32], p[35:32]);
        gp_generator gp36(a[39:36], b[39:36], g[39:36], p[39:36]);
        gp_generator gp40(a[43:40], b[43:40], g[43:40], p[43:40]);
        gp_generator gp44(a[47:44], b[47:44], g[47:44], p[47:44]);
        gp_generator gp48(a[51:48], b[51:48], g[51:48], p[51:48]);
        gp_generator gp52(a[55:52], b[55:52], g[55:52], p[55:52]);
        gp_generator gp56(a[59:56], b[59:56], g[59:56], p[59:56]);
        gp_generator gp60(a[63:60], b[63:60], g[63:60], p[63:60]);
		
	    //generate gG & gP, generate carries c0, c4, c8, c12, ... , c60
        carry_generator cg00(g[3:0], p[3:0], cin, c[3:1], gG[0], gP[0]);
        carry_generator cg04(g[7:4], p[7:4], c[4], c[7:5], gG[1], gP[1]);
        carry_generator cg08(g[11:8], p[11:8], c[8], c[11:9], gG[2], gP[2]);
        carry_generator cg12(g[15:12], p[15:12], c[12], c[15:13], gG[3], gP[3]);
        carry_generator cg16(g[19:16], p[19:16], c[16], c[19:17], gG[4], gP[4]);
        carry_generator cg20(g[23:20], p[23:20], c[20], c[23:21], gG[5], gP[5]);
        carry_generator cg24(g[27:24], p[27:24], c[24], c[27:25], gG[6], gP[6]);
        carry_generator cg28(g[31:28], p[31:28], c[28], c[31:29], gG[7], gP[7]);
        carry_generator cg32(g[35:32], p[35:32], c[32], c[35:33], gG[8], gP[8]);
        carry_generator cg36(g[39:36], p[39:36], c[36], c[39:37], gG[9], gP[9]);
        carry_generator cg40(g[43:40], p[43:40], c[40], c[43:41], gG[10], gP[10]);
        carry_generator cg44(g[47:44], p[47:44], c[44], c[47:45], gG[11], gP[11]);
        carry_generator cg48(g[51:48], p[51:48], c[48], c[51:49], gG[12], gP[12]);
        carry_generator cg52(g[55:52], p[55:52], c[52], c[55:53], gG[13], gP[13]);
        carry_generator cg56(g[59:56], p[59:56], c[56], c[59:57], gG[14], gP[14]);
        carry_generator cg60(g[63:60], p[63:60], c[60], c[63:61], gG[15], gP[15]);
	
	    //generate all carries
        assign c[4]  = gG[0] | (gP[0] & cin);
        assign c[8]  = gG[1] | (gP[1] & c[4]);
        assign c[12] = gG[2] | (gP[2] & c[8]);
        assign c[16] = gG[3] | (gP[3] & c[12]);
        assign c[20] = gG[4] | (gP[4] & c[16]);
        assign c[24] = gG[5] | (gP[5] & c[20]);
        assign c[28] = gG[6] | (gP[6] & c[24]);
        assign c[32] = gG[7] | (gP[7] & c[28]);
        assign c[36] = gG[8] | (gP[8] & c[32]);
        assign c[40] = gG[9] | (gP[9] & c[36]);
        assign c[44] = gG[10] | (gP[10] & c[40]);
        assign c[48] = gG[11] | (gP[11] & c[44]);
        assign c[52] = gG[12] | (gP[12] & c[48]);
        assign c[56] = gG[13] | (gP[13] & c[52]);
        assign c[60] = gG[14] | (gP[14] & c[56]);
	    
	    //generate sum
        sum_generator64 sg(a, b, cin, c, sum);
    
    //-------------------------------//

endmodule

module sum_generator64(a, b, cin, c, sum);

    input [63:0] a, b;
    input cin;
    input [63:1] c;
    output [63:0] sum;
	

    assign sum = a ^ b ^ {c, cin};

endmodule
