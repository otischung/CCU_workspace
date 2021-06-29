`timescale 1ns/1ps

module RCA_16bit(a,b,cin,sum,cout);

    input [15:0] a,b;
    input cin;
    output [15:0] sum;
    output cout;
    wire [14:0] c;
	// --- Write down your design here --- //

	// ----------------------------------- //

endmodule

// FA module
module fulladder(a,b,cin,sum,cout);
	
	input a, b, cin;
	output sum,cout;

	// --- Write down your design here --- //

	// ----------------------------------- //

endmodule

// xor gate
module xorgate (a,b,out);
	
	input a,b;
	output out;

	// --- Write down your design here --- //

	// ----------------------------------- //


endmodule



// and gate
module andgate (a,b,out);
	
	input a, b;
	output reg out;

	always @ (*)  begin
		#10 out <= a & b; // #10ns 為 and gate's gate delay
	end

endmodule

// or gate
module orgate (a,b,out);
	
	input a, b;
	output reg out;

	always @ (*)  begin
		#4 out <= a | b; // #4ns 為 or gate's gate delay
	end

endmodule