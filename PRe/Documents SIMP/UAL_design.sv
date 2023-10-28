`include "UAL_instr_decoder.sv"
`include "UAL_r_MUX.sv"
`include "UAL_logic_unit.sv"
`include "UAL_arithm_unit.sv"
`include "UAL_carry_MUX.sv"
`include "UAL_output_MUX.sv"
`include "UAL_flag_unit.sv"
`include "UAL_reg_unit.sv"

module UAL( instr, r1, r2, flags, mem, IN, OUT, ck );
	
	// Define ports
	input [7:0] instr, mem, IN;
	input ck;

	output [7:0] r1, r2, OUT;
	output [4:0] flags;

	// Define UAL blocs and connections
	wire shift_rot, nandi, ori, xori, leq, add, les_leq, iget, set_A, set_B,
		set_V, set_X, hi_lo_V, i7, i4, i3, i2, i1, i0;
	wire [3:0] V_nibble;
	instr_decoder ID( instr, {shift_rot, nandi, ori, xori, leq, add, les_leq,
		iget, set_A, set_B, set_V, set_X, hi_lo_V, i7, i4, i3, i2, i1, i0,
		V_nibble} );

	wire [7:0] A, B, V, X;
	r_MUX r1_MUX( {A, B, V, X}, {i0, i1}, r1 );
	r_MUX r2_MUX( {A, B, V, X}, {i2, i3}, r2 );

	wire [7:0] right, left, nandv, orv, xorv;
	wire right_C, left_C;
	logic_unit LU( {r2, r1}, i3, {right, left, nandv, orv, xorv, right_C,
		left_C} );

	wire [7:0] AU_out;
	wire AU_C, O;
	arithm_unit AU( {r2, r1}, add, {AU_out, AU_C, O} );

	wire C;
	carry_MUX c_MUX( {right_C, left_C, AU_C}, {i2, shift_rot}, C );

	wire [7:0] o_out;
	output_MUX o_MUX( {right, left, nandv, orv, xorv, AU_out}, {i2, shift_rot,
		nandi, ori, xori}, o_out );

	wire [4:0] FU_out;
	wire N;
	flag_unit FU( {AU_out, C, O, ck}, {i7, leq}, {FU_out, N} );

	reg_unit RU( {mem, o_out, IN, V_nibble, N, ck}, {les_leq, iget, set_A,
		set_B, set_V, set_X, hi_lo_V, i4, i7}, {A, B, V, X, OUT} );

	// Display registers
	always @ ( instr ) #6
		$display( "#%0t) A : %d B : %d V : %d X : %d", $time, A, B, V, X );

	always @ ( instr ) #6 $display( "#%0t) COPNZ : %5b", $time, FU_out );

endmodule
