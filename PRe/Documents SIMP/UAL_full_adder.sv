module full_adder( A, B, sub, c_in, S, c_out );
	
	// Define ports
	input A, B, sub, c_in;

	output S, c_out;

	// Define connections
	wire B_sub;

	// Link connections
	assign B_sub = B ^ sub;

	// Link outputs
	assign S = A ^ B_sub ^ c_in;
	assign c_out = ( A & B_sub ) | ( A & c_in ) | ( B_sub & c_in );

endmodule
