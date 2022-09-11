// blok na czerwono z wykladu i xor
module calcPGX(output g, output p, output s,
               input a, input b, input c);
	assign s = a ^ b ^ c;
   	assign g = a && b;
        assign p = a || b;
  
endmodule
 
module four_bit_block(
  output G,
  output P,
  output [3:0] s,
  input [3:0] a,
  input [3:0] b,
  input c_in);//c0
  
  calcPGX calc1(g0,p0,s[0],a[0],b[0],c_in);
  logic c1;
  assign c1 = g0 || (p0 && c_in);
  
  calcPGX calc2(g1,p1,s[1],a[1],b[1],c1);
  logic c2;
  assign c2 = g1 || (p1 && g0) || (p1 && p0 && c_in);
  
  calcPGX calc3(g2,p2,s[2],a[2],b[2],c2);
  logic c3;
  assign c3 = g2 || (p2 && g1) || (p2 && p1 && g0) || (p2 && p1 && p0 && c_in);
  
  calcPGX calc4(g3,p3,s[3],a[3],b[3],c3);
  
  assign P = p0 && p1 && p2 && p3;
  assign G = g3 || (g2 && p3) || (g1 && p2 && p3) || (g0 && p1 && p2 && p3);
  
endmodule

module bit_16_adder(input [15:0] a, input [15:0] b, output [15:0] o);
  logic c4, c8, c12;
  logic g0,p0,g1,p1,g2,p2,g3,p3;
  logic [3:0] s3,s2,s1,s0;
  logic [3:0] a3,a2,a1,a0;
  logic [3:0] b3,b2,b1,b0;
  
  assign {a3,a2,a1,a0} = a;
  assign {b3,b2,b1,b0} = b;
  
  four_bit_block blok1(g0,p0,s0,a0,b0,0);
  assign c4 = g0;
  
  four_bit_block blok2(g1,p1,s1,a1,b1,c4);
  assign c8 = (g0 && p1) || g1;
  
  four_bit_block blok3(g2,p2,s2,a2,b2,c8);
  assign c12 = (g0 && p1 && p2) || (g1 && p2) || g2;
  
  four_bit_block blok4(g3,p3,s3,a3,b3,c12);
  
  assign o = {s3,s2,s1,s0};
endmodule

module toplevel(input [15:0] a, input [15:0] b, output [15:0] o);
  bit_16_adder top(a,b,o);
endmodule
