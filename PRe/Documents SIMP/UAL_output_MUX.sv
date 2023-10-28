module output_MUX( {right, left, nandv, orv, xorv, AU_out}, {i2, shift_rot,
		nandi, ori, xori}, o_out );

	// Define ports
	input [7:0] right, left, nandv, orv, xorv, AU_out;
	
	input i2, shift_rot, nandi, ori, xori;

	output [7:0] o_out;

	// Define connections
	wire [7:0] left_or_right, AU_or_shift_rot, else_or_nand, else_or_or;

	// Link connections
	assign left_or_right = i2 ? right : left;
	assign AU_or_shift_rot = shift_rot ? left_or_right : AU_out;
	assign else_or_nand = nandi ? nandv : AU_or_shift_rot;
	assign else_or_or = ori ? orv : else_or_nand; 

	// Link outputs
	assign o_out = xori ? xorv : else_or_or;

endmodule
