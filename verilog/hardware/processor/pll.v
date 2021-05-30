module pll(
        input  clock_in,
        output clock_out,
        );

SB_PLL40_CORE #(
                .FEEDBACK_PATH("SIMPLE"),
                .DIVR(4'b0000),         // DIVR =  0
                .DIVF(7'b1001010),      // DIVF = 74
                .DIVQ(3'b101),          // DIVQ =  5
                .FILTER_RANGE(3'b001)   // FILTER_RANGE = 1
        ) uut (
                .LOCK(),
                .RESETB(1'b1),
                .BYPASS(1'b0),
                .REFERENCECLK(clock_in),
                .PLLOUTCORE(clock_out)
                );

endmodule

module pll_clock(input clock_in, output reg clock_out);
	wire clock_div;
	pll hardware_pll(clock_in, clock_div);
	
	always @(posedge clock_div) begin
		clock_out <= ~clock_out;
	end
endmodule
