`ifdef REG_SV `else
`define REG_SV
`include "reg.sv"
`endif

module flag_unit( {AU_out, C, O, ck}, {i7, leq}, {FU_out, N} );

	// Define ports
	input [7:0] AU_out;
	input C, O;
	input ck;

	input i7, leq;

	output [4:0] FU_out;
	output N;

	// Define connections
	wire P, N, Z;
	reg5 COPNZ( {C, O, P, N, Z}, FU_out, i7, ck );

	// Link connections
	assign P = ~AU_out[0];
	assign Z = ( AU_out == 8'b0 );

	// Link outputs
	assign N = AU_out[7] | ( Z & leq );

endmodule
