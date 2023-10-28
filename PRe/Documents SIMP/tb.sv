`include "UAL_design.sv"

module tb;

	reg [7:0] instr, mem, IN;
	reg ck;
	wire [4:0] flags;
	wire [7:0] r1, r2, OUT;
	UAL UAL0( instr, r1, r2, flags, mem, IN, OUT, ck );

	initial begin
		instr <= 0;
		mem <= 0;
		IN <=0;
		ck <= 0;
	end

	always #5 ck <= ~ck;

	initial begin
		instr <= 8'b01101111; // 1) hiV 1111 ok
		#10 instr <= 8'b01110111; // 11) loV 0111 ok
		#10 instr <= 8'b10001011; // 21) add V X ok
		#10 instr <= 8'b10011011; // 31) sub V X ok
		#10 instr <= 8'b10001011; // 41) add V X ok
		#10 instr <= 8'b10100010; // 51) rol V 
		#10 instr <= 8'b10100011; // 61) ror V
		#10 instr <= 8'b10100000; // 71) shl V
		#10 instr <= 8'b10100001; // 81) shr V
		#10 instr <= 8'b11001010; // 91) or V X
		#10 instr <= 8'b11011011; // 101) xor V X
		#10 instr <= 8'b11101011; // 111) nand V X
		
		#15 $finish;

	end

endmodule
