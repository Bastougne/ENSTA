module r_MUX( {A, B, V, X}, {i_n1, i_n2}, r );
	
	// Define ports
	input [7:0] A, B, V, X;

	input i_n1, i_n2;

	output [7:0] r;

	// Define connections
	wire [7:0] A_or_B, V_or_X;

	// Link connections
	assign A_or_B = i_n1 ? B : A;
	assign V_or_X = i_n1 ? X : V;

	// Link outputs
	assign r = i_n2 ? V_or_X : A_or_B;

endmodule
