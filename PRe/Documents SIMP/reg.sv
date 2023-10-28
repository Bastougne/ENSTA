module reg8( d, q, e, ck );
	
	// Define ports
	input [7:0] d;

	input e, ck;

	output reg [7:0] q;

	// Link outputs
	always @ ( posedge ck )
		if ( e ) q <= d;

	initial q <= 0;

endmodule

module reg5( d, q, e, ck );
	
	// Define ports
	input [4:0] d;

	input e, ck;

	output reg [4:0] q;

	// Link outputs
	always @ ( posedge ck )
		if ( e ) q <= d;

	initial q <= 0;

endmodule

module reg2( d, q, e, ck );
	
	// Define ports
	input [1:0] d;

	input e, ck;

	output reg [1:0] q;

	// Link outputs
	always @ ( posedge ck )
		if ( e ) q <= d;

	initial q <= 0;

endmodule
