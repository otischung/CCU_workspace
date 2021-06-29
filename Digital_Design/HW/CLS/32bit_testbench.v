`timescale 1ns / 1ps
`include "32bit_CLS.v"

module testbench;

    reg [31:0] in_a, in_b;
    reg bin;

	reg clk;
	reg rst;
	
    reg [5:0] idx;
    reg [8:0] write;
    reg [5:0] correct_ct;
    reg [32:0] correct_ans;

    wire [31:0] diff;
    wire bout;
    wire gp, gg;

    CLS_32bit Import_CLS(in_a, in_b, bin, diff, gp, gg);
    PG2B T1(bin, gp, gg, bout);

	initial begin
        in_a <= 0;
        in_b <= 0;  
        bin <= 0;
        clk <= 1'b0;
        correct_ct <= 0;
        idx <= 0;
        ////////////////////////////////
        rst <= 1'b0;
        correct_ans <= 17'd0;
        write <= 9'd0;
        ////////////////////////////////

        $dumpfile("32bit_CLS.fsdb");  
        $dumpvars;
        
        #10 rst = 1;
        #10 rst = 0;

        for (idx = 1; idx < 10; idx = idx + 1) begin
            #200 rst = 1;
            #20  rst = 0;
        end

        #200 $display ("//     CORRECT COUNT = %d    //", correct_ct);
        #100 $finish;
    end

    always #10 clk = ~clk;


    always @(posedge clk or posedge rst) begin
        if (rst) begin
            in_a <= {$random};
            in_b <= {$random};        
            bin <= {$random} % 2;    

            correct_ans <= 0;
            write <= 0;            
        end 
        else begin
			correct_ans <= in_a - in_b - bin;
            write <= write + 1;

            if (write == 8) begin
                if ({bout, diff} == correct_ans) begin
                    correct_ct <= correct_ct + 1;
                    
                    $display ("////////////////////////Test %d////////////////////////", idx);
                    $display ("//  Q :%d - %d - %d = ? //",in_a, in_b, bin);
                    $display ("///////////////////////////////////////////////////////");
                    $display ("//  Your answer              //");                    
                    $display ("//  Bout = %d Diff = %d     //", bout, diff);
                    $display ("///////////////////////////////////////////////////////");
                    $display ("//  Correct answer           //");
                    $display ("//  Bout = %d Diff = %d     //", correct_ans[32], correct_ans[31:0]);           
                    $display ("///////////////////////////////////////////////////////");
                    $display ("//                   SUCCESSFUL !                  //");
                    $display ("///////////////////////////////////////////////////////\n\n");
                end 
                else begin
                    $display ("////////////////////////Test %d////////////////////////", idx);
                    $display ("//  Q :%d - %d - %d = ? //", in_a, in_b, bin);
                    $display ("///////////////////////////////////////////////////////");
                    $display ("//  Your answer                                      //");                    
                    $display ("//  Bout = %d Diff = %d     //", bout, diff);
                    $display ("///////////////////////////////////////////////////////");
                    $display ("//  Correct answer                                   //");
                    $display ("//  Bout = %d Diff = %d     //", correct_ans[32], correct_ans[31:0]);           
                    $display ("///////////////////////////////////////////////////////");
                    $display ("//                      FAIL !                     //");
                    $display ("///////////////////////////////////////////////////////\n\n");
                end 
            end            
        end
    end

endmodule