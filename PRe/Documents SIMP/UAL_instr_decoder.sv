module instr_decoder( instr, {shift_rot, nandi, ori, xori, leq, add, les_leq,
		iget, set_A, set_B, set_V, set_X, hi_lo_V, i7, i4, i3, i2, i1, i0, V_nibble} );
	
	// Define ports
	input [7:0] instr;

	output shift_rot, nandi, ori, xori, leq, add, les_leq, iget, set_A, set_B,
		set_V, set_X, hi_lo_V, i7, i4, i3, i2, i1, i0;
	output [3:0] V_nibble;

	// Define connections
	wire mget, pop_r, set;

	// Link connections
	assign mget = ( instr[7:4] == 4'b0010 );
	assign pop_r = ( instr[7:4] == 4'b0001 ) & ( instr[3:2] == 2'b10 );
	assign set = mget | pop_r;

	// Link outputs
	assign shift_rot = ( instr[7:4] == 4'b1010 );
	assign nandi = ( instr[7:4] == 4'b1011 );
	assign ori = ( instr[7:4] == 4'b1100 ) ;
	assign xori = ( instr[7:4] == 4'b1101 );
	assign leq = ( instr[7:4] == 4'b1111 );
	assign add = ( instr[7:4] == 4'b1000 );
	assign les_leq = ( instr[7:5] == 3'b111 );
	assign iget = ( instr[7:4] == 4'b0100 );
	assign set_A = ( instr[1:0] == 2'b00 ) & set;
	assign set_B = ( instr[1:0] == 2'b01 ) & set;
	assign set_V = ( instr[1:0] == 2'b10 ) & set;
	assign set_X = ( instr[1:0] == 2'b11 ) & set;
	assign hi_lo_V = ( instr[7:5] == 3'b011 );
	assign i7 = instr[7];
	assign i4 = instr[4];
	assign i3 = instr[3];
	assign i2 = instr[2];
	assign i1 = instr[1];
	assign i0 = instr[0];
	assign V_nibble = instr[3:0];

	// Display
	always @ ( instr ) #1 $display( "\n#%0t) ", $time, "shift_rot %d ", shift_rot,
		"nandi %d ", nandi, "ori %d ", ori, "xori %d ", xori, "leq %d ", leq,
		"add %d ", add, "les_leq %d ", les_leq, "iget %d ", iget, "set_A %d ",
		set_A, "set_B %d ", set_B, "set_V %d ", set_V, "set_X %d ", set_X,
		"hi_lo_V %d ", hi_lo_V, "i7 %d ", i7, "i4 %d ", i4, "i3 %d ", i3,
		"i2 %d ", i2, "i1 %d ", i1, "i0 %d ", i0, "V_nibble %d ", V_nibble );

endmodule
