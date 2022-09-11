// 4 to 1 MUX
module bit2in4MUX(
  input[1:0] s,
  input[3:0] i,
  output o,
);
  assign o = (s[0]) ? ((s[1]) ? i[3] : i[1]) : ((s[1]) ? i[2] : i[0]);
endmodule

module dff(output q, nq, input clk, d);//z wykladu
logic r, s, nr, ns;
nand gq(q, nr, nq), gnq(nq, ns, q),
gr(nr, clk, r), gs(ns, nr, clk, s),
gr1(r, nr, s), gs1(s, ns, d);
endmodule

//D-Latch 4-1 MUX pair
module muxNLatch(
	input i,           //input for parallel loading
    input l,r,         //00 - do nth, 01 <<, 10 >> , 11 parallel load - controls
    input clkIN,       //clock input
    input right, left, //passed input from left/right mux
    output o,
);
  logic notq, temp;
  bit2in4MUX mux({l,r},{i,left,right,o},temp);
  dff d_latch(o,notq,clkIN,temp);
endmodule

// 4 bit universal shifter
module bit4Shift(
  input l, r,
  input[3:0] i,
  input iL, iR, //input from left/right for linking shifters 
  input clkIN,
  output[3:0] o
);
  muxNLatch part1(i[0],l,r,clkIN,iR  ,o[1],o[0]);//rightmost
  muxNLatch part2(i[1],l,r,clkIN,o[0],o[2],o[1]);
  muxNLatch part3(i[2],l,r,clkIN,o[1],o[3],o[2]);
  muxNLatch part4(i[3],l,r,clkIN,o[2],iL,  o[3]);//leftmost
endmodule

//8 bit universal shifter
module bit8Shift(
  input[7:0] d, //rownolegle
  input i, 		//szeregowe
  input c,
  input l, r,
  output[7:0] q, 
);
  bit4Shift right(l,r,d[3:0],q[4],i,c,q[3:0]);
  bit4Shift left(l,r,d[7:4],i,q[3],c,q[7:4]);
endmodule