`timescale 1ns/1ps
`include "16bit_RCA.v"
module testbench;

    reg [15:0] in_a, in_b;
    reg cin;

    reg clk;
    reg rst;
    reg [5:0] idx;

    wire [15:0] sum;
    wire cout;

    RCA_16bit Import_RCA(in_a,in_b,cin,sum,cout);

    initial begin
        
        in_a <= 0;
        in_b <= 0;  
        cin  <= 1;
        clk  <= 0;
        idx  <= 0;

        $dumpfile("16bit_RCA.fsdb");  
        $dumpvars;
        
        #10 rst = 1;
        #10 rst = 0;

        for (idx = 1;idx < 3;idx=idx+1) begin
            #500 rst = 1;
            #20  rst = 0;
        end

        #500    $finish;

    end

    always #10 clk = ~clk;


    always @(posedge clk or posedge rst) begin

        if (rst) begin
            /* 
            數值表示方法
            MSB 表示位數大小
            二進位 :
                16'b0000000000000000 = 0
                16'b0000000000000001 = 1 
                16'b0000000000000010 = 2, etc.
            十進位 :    
                16'd0 = 0
                16'd10 = 10 
                16'd100 = 100, etc.
            十六進位 :
                16'h0 = 0
                16'hf = 15
                16'h10 = 16, etc.
            */

            //--- Write your design here---//

            // Bestcase test
            if (idx == 1) begin
                in_a <= 
                in_b <=       
                cin  <= 
            end 
            // Worstcase test
            else if (idx == 2) begin
                in_a <= 
                in_b <= 
                cin  <= 
            end 
            //--- Write your design here---//
            
            // 為了讓波形圖有分界的值    
            else begin
                in_a <= 0;
                in_b <= 0;        
                cin  <= 0;
            end
        end
    end

endmodule







