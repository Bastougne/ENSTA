module logic_unit( {r2, r1}, i3, {right, left, nandv, orv, xorv, right_C,
		left_C} );
	
	// Define ports
	input [7:0] r2, r1;

	input i3;

	output [7:0] right, left, nandv, orv, xorv;
	output right_C, left_C;

	// Link outputs
	assign right = {r2[0] & i3, r2[7:1]};
	assign left = {r2[6:0], r2[7] & i3};
	assign nandv = ~( r2 & r1 );
	assign orv = ( r2 | r1 );
	assign xorv = ( r2 ^ r1 );

	assign right_C = r2[0];
	assign left_C = r2[1];

endmodule
