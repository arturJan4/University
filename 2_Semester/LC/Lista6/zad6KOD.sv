module bit2in4MUX(// 4 to 1 MUX
  input[1:0] s,
  input[3:0] i,
  output o,
);
  assign o = (s[0]) ? ((s[1]) ? i[3] : i[1]) : (s[1] ? i[2] : i[0]);
endmodule

module dff(output q, nq, input clk, d);
logic r, s, nr, ns;
nand gq(q, nr, nq), gnq(nq, ns, q),
gr(nr, clk, r), gs(ns, nr, clk, s),
gr1(r, nr, s), gs1(s, ns, d);
endmodule

module muxNLatch(
	input i,
    input[1:0] s,     //00 - do nth, 01 <<, 10 >> , 11 parallel load
    input clkIN,      //clock input
    input right, left,//passed input from left/right mux
    output o,
);
  logic notq, temp;
  bit2in4MUX mux(s,{i,left,right,o},temp);
  dff d_latch(o,notq,clkIN,temp);
endmodule

module bit4Shift(
  input[1:0] s,
  input[3:0] i,
  input iL, iR, //input from left/right
  input clk,
  output[3:0] o
);
  muxNLatch part1(i[0],s,clk,iR  ,o[1],o[0]);
  muxNLatch part2(i[1],s,clk,o[0],o[2],o[1]);
  muxNLatch part3(i[2],s,clk,o[1],o[3],o[2]);
  muxNLatch part4(i[3],s,clk,o[2],iL,  o[3]);
endmodule