module dec2to4(
input [1:0] i,
input en,
output [3:0] o
);
integer k;
always_comb
for (k = 0; k <= 3; k = k + 1)
	if (i == k)
		o[k] = en;
	else
		o[k] = 0;
endmodule
