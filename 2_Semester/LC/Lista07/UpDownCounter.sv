module bit2in4MUX(
  input[1:0] s,
  input[3:0] i,
  output o,
);
  assign o = (s[0]) ? ((s[1]) ? i[3] : i[1]) : ((s[1]) ? i[2] : i[0]);
endmodule

module tff(output q, nq, input t, clk, nrst);
logic ns, nr, ns1, nr1, j, k;
nand n1(ns, clk, j), n2(nr, clk, k),
	n3(q, ns, nq), n4(nq, nr, q, nrst),
	n5(ns1, !clk, t, nq), n6(nr1, !clk, t, q),
	n7(j, ns1, k), n8(k, nr1, j, nrst);
endmodule

module syncnt(output [3:0] out, input clk, nrst, step, down);
genvar n;
  logic [3:0] t;
  logic [3:0] nq;
 
  logic [1:0] s;  
  assign s = {down,step};// <11 down by 2>, <10 down by 1>, <01 up by 2>, <00 up by 1>  
    
  genvar n;
  for (n = 0; n < 4; n = n + 1)
    tff tf(.q(out[n]),.nq(nq[n]),.t(t[n]), .clk(clk), .nrst(nrst));

  assign t[0] = !step;
  bit2in4MUX mux1(s,
                  {	 1'b1,  //11
                     nq[0], //10
                     1'b1,  //01
                  	 out[0] //00
				  },
                  t[1]);
  
  bit2in4MUX mux2(s,
                  {	  nq[1],
                  	 (nq[1]  && t[1]),
                      out[1],
                     (out[1] && t[1])
				  },
                  t[2]);
  
  bit2in4MUX mux3(s,
                  {   (nq[1]  && nq[2]),
                 	  (nq[2]  && t[2]),
                 	  (out[1] && out[2]),
                 	  (out[2] && t[2])
				  },
                   t[3]);
endmodule