`include "UAL_full_adder.sv"

module arithm_unit( {r2, r1}, add, {AU_out, AU_C, O} );

	// Define ports
	input [7:0] r2, r1;

	input add;

	output [7:0] AU_out;
	output AU_C, O;

	// Define connections
	wire sub;
	wire [7:0] c_in, c_out;

	genvar i;
	generate
		for ( i = 0; i < 8; i = i + 1 )
			full_adder FA ( r2[i], r1[i], sub, c_in[i], AU_out[i], c_out[i] );
	endgenerate

	// Link connections
	assign sub = ~add;

	genvar j;
	generate
		assign c_in[0] = sub;
		for ( j = 1; j < 8; j = j + 1 )
			assign c_in[j] = c_out[j - 1];
	endgenerate

	// Link outputs
	assign {AU_C, O} = {c_out[7], c_out[7] ^ c_out[6]};

endmodule
