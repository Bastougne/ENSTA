`ifdef REG_SV `else
`define REG_SV
`include "reg.sv"
`endif

module reg_unit( {mem, o_out, IN, V_nibble, N, ck}, {les_leq, iget, set_A,
		set_B, set_V, set_X, hi_lo_V, i4, i7}, {A, B, V, X, OUT} );

	// Define ports
	input [7:0] mem, o_out, IN;
	input [3:0] V_nibble;
	input N;
	input ck;

	input les_leq, iget, set_A, set_B, set_V, set_X, hi_lo_V, i4, i7;

	output [7:0] A, B, V, X, OUT;

	// Define connections
	wire [7:0] A_in, hi_lo_Vv, V_in, math_res, X_in;
	wire A_en, V_en, X_en;

	reg8 reg_A( A_in, A, A_en, ck );
	reg8 reg_B( mem, B, set_B, ck );
	reg8 reg_V( V_in, V, V_en, ck );
	reg8 reg_X( X_in, X, X_en, ck );

	// Link connections
	assign A_in = iget ? IN : mem;
	assign A_en = iget | set_A;

	assign hi_lo_Vv = i4 ? {V[7:4], V_nibble} : {V_nibble, V[3:0]};
	assign V_in = hi_lo_V ? hi_lo_Vv : mem;
	assign V_en = hi_lo_V | set_V;

	assign math_res = les_leq ? {8{N}}: o_out;
	assign X_in = i7 ? math_res : mem;
	assign X_en = i7 | set_X;

endmodule
