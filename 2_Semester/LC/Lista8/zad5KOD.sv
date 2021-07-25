module nwd(
  output [15:0] out,
  output fin,
  input clk, init,
  input [15:0] in1,
  input [15:0] in2,
);
  logic cmp;
  logic [15:0] a, rejA;
  logic [15:0] b, rejB;
  logic [15:0] diff;
  
  assign fin = (a == b);
  assign cmp = (a > b);
  assign diff = ((cmp) ? a : b) - ((cmp) ? b : a); //jedna operacja odejmowania
  assign out = a;
  
  assign rejA = init ? in1 : ((cmp && !fin)  ? diff : a);
  assign rejB = init ? in2 : ((!cmp && !fin) ? diff : b);

  always_ff @(posedge clk)
	a <= rejA;   
  always_ff @(posedge clk)
    b <= rejB;   
endmodule

module test( 
  output [15:0] o,
  output fin,
  input clk, init,
  input [15:0] in1,
  input [15:0] in2,
);
  nwd test(o,fin,clk,init,in1,in2);
endmodule

