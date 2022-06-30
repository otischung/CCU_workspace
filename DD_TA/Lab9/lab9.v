/**
 *
 * @author : 409412345, 409412346
 * @latest changed : 2022/5/8 12:34
 */

module lab9(input clk,
            input reset,
            input give_valid,
            input [13:0] Intake,
            output reg [13:0] UpPrime,
            output reg [13:0] LowPrime,
            output out_valid
);

    initial begin
        $dumpfile("Lab.vcd");
        $dumpvars(0, lab9tb);
    end

    wire [7:0] root;
    sqrt sqrt(.in(Intake), .out(root));

    reg updone;
    reg lowdone;

    assign out_valid = lowdone & updone;

    // 1. initial 
    // 2. N+1 or N-1
    // 3. check 0 ~ N root
    // 4. back to 2. or done

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            updone <= 0;
        end else begin
        
        end
    end

endmodule

/*==================================*/

module sqrt(input [13:0]in,
            output reg [7:0]out
);

    always @(*) begin
        if ( in > 9801 ) out <=  99 ;
        else if ( in > 9604 ) out <=  98 ;
        else if ( in > 9409 ) out <=  97 ;
        else if ( in > 9216 ) out <=  96 ;
        else if ( in > 9025 ) out <=  95 ;
        else if ( in > 8836 ) out <=  94 ;
        else if ( in > 8649 ) out <=  93 ;
        else if ( in > 8464 ) out <=  92 ;
        else if ( in > 8281 ) out <=  91 ;
        else if ( in > 8100 ) out <=  90 ;
        else if ( in > 7921 ) out <=  89 ;
        else if ( in > 7744 ) out <=  88 ;
        else if ( in > 7569 ) out <=  87 ;
        else if ( in > 7396 ) out <=  86 ;
        else if ( in > 7225 ) out <=  85 ;
        else if ( in > 7056 ) out <=  84 ;
        else if ( in > 6889 ) out <=  83 ;
        else if ( in > 6724 ) out <=  82 ;
        else if ( in > 6561 ) out <=  81 ;
        else if ( in > 6400 ) out <=  80 ;
        else if ( in > 6241 ) out <=  79 ;
        else if ( in > 6084 ) out <=  78 ;
        else if ( in > 5929 ) out <=  77 ;
        else if ( in > 5776 ) out <=  76 ;
        else if ( in > 5625 ) out <=  75 ;
        else if ( in > 5476 ) out <=  74 ;
        else if ( in > 5329 ) out <=  73 ;
        else if ( in > 5184 ) out <=  72 ;
        else if ( in > 5041 ) out <=  71 ;
        else if ( in > 4900 ) out <=  70 ;
        else if ( in > 4761 ) out <=  69 ;
        else if ( in > 4624 ) out <=  68 ;
        else if ( in > 4489 ) out <=  67 ;
        else if ( in > 4356 ) out <=  66 ;
        else if ( in > 4225 ) out <=  65 ;
        else if ( in > 4096 ) out <=  64 ;
        else if ( in > 3969 ) out <=  63 ;
        else if ( in > 3844 ) out <=  62 ;
        else if ( in > 3721 ) out <=  61 ;
        else if ( in > 3600 ) out <=  60 ;
        else if ( in > 3481 ) out <=  59 ;
        else if ( in > 3364 ) out <=  58 ;
        else if ( in > 3249 ) out <=  57 ;
        else if ( in > 3136 ) out <=  56 ;
        else if ( in > 3025 ) out <=  55 ;
        else if ( in > 2916 ) out <=  54 ;
        else if ( in > 2809 ) out <=  53 ;
        else if ( in > 2704 ) out <=  52 ;
        else if ( in > 2601 ) out <=  51 ;
        else if ( in > 2500 ) out <=  50 ;
        else if ( in > 2401 ) out <=  49 ;
        else if ( in > 2304 ) out <=  48 ;
        else if ( in > 2209 ) out <=  47 ;
        else if ( in > 2116 ) out <=  46 ;
        else if ( in > 2025 ) out <=  45 ;
        else if ( in > 1936 ) out <=  44 ;
        else if ( in > 1849 ) out <=  43 ;
        else if ( in > 1764 ) out <=  42 ;
        else if ( in > 1681 ) out <=  41 ;
        else if ( in > 1600 ) out <=  40 ;
        else if ( in > 1521 ) out <=  39 ;
        else if ( in > 1444 ) out <=  38 ;
        else if ( in > 1369 ) out <=  37 ;
        else if ( in > 1296 ) out <=  36 ;
        else if ( in > 1225 ) out <=  35 ;
        else if ( in > 1156 ) out <=  34 ;
        else if ( in > 1089 ) out <=  33 ;
        else if ( in > 1024 ) out <=  32 ;
        else if ( in > 961 ) out <=  31 ;
        else if ( in > 900 ) out <=  30 ;
        else if ( in > 841 ) out <=  29 ;
        else if ( in > 784 ) out <=  28 ;
        else if ( in > 729 ) out <=  27 ;
        else if ( in > 676 ) out <=  26 ;
        else if ( in > 625 ) out <=  25 ;
        else if ( in > 576 ) out <=  24 ;
        else if ( in > 529 ) out <=  23 ;
        else if ( in > 484 ) out <=  22 ;
        else if ( in > 441 ) out <=  21 ;
        else if ( in > 400 ) out <=  20 ;
        else if ( in > 361 ) out <=  19 ;
        else if ( in > 324 ) out <=  18 ;
        else if ( in > 289 ) out <=  17 ;
        else if ( in > 256 ) out <=  16 ;
        else if ( in > 225 ) out <=  15 ;
        else if ( in > 196 ) out <=  14 ;
        else if ( in > 169 ) out <=  13 ;
        else if ( in > 144 ) out <=  12 ;
        else if ( in > 121 ) out <=  11 ;
        else if ( in > 100 ) out <=  10 ;
        else if ( in > 81 ) out <=  9 ;
        else if ( in > 64 ) out <=  8 ;
        else if ( in > 49 ) out <=  7 ;
        else if ( in > 36 ) out <=  6 ;
        else if ( in > 25 ) out <=  5 ;
        else if ( in > 16 ) out <=  4 ;
        else if ( in > 9 ) out <=  3 ;
        else if ( in > 4 ) out <=  2 ;
    end
endmodule
