module carry_MUX( {right_C, left_C, AU_C}, {i2, shift_rot}, C );

	// Define ports
	input right_C, left_C, AU_C;

	input i2, shift_rot;

	output C;

	// Define connections
	wire shift_rot_carry;

	// Link connections
	assign shift_rot_carry = i2 ? right_C : left_C;

	// Link outputs
	assign C = shift_rot ? shift_rot_carry : AU_C;

endmodule
