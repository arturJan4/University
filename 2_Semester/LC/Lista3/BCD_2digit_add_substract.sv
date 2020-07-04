// BCD 2 digit adder
// addding '1 could have been implemented using carry

// Full adder
module FA(output s,c_o,
          input a,b,c_i);
  
	assign s = a ^ b ^ c_i;
	assign c_o = (a && b) || (a ^ b && c_i);
endmodule

//uklad z wykladu sumator szeregowy
module add_4bit(output [3:0] s,output c_o,
               input [3:0] a, input [3:0] b, input c_i);

  logic c1,c2,c3;
  FA fa1(s[0],c1,a[0],b[0],c_i);
  FA fa2(s[1],c2,a[1],b[1],c1);
  FA fa3(s[2],c3,a[2],b[2],c2);
  FA fa4(s[3],c_o,a[3],b[3],c3);
endmodule

//dopelnienie do 9 (9 - ai)
module bcd_9(output [3:0] o,input [3:0] ai
            ); 
  
  assign w = ai[0];
  assign z = ai[1];
  assign y = ai[2];
  assign x = ai[3];
  //z mapy Karnough
  assign o[3] = (!x && !y && !z);
  assign o[2] = !x && (y ^ z);
  assign o[1] = !x && z;
  assign o[0] = !w && (!x || (x && !y && !z));
endmodule

//dodaje 1 cyfre w BCD
module bcd_add_1digit(output [3:0] s,output c_o,
                      input [3:0] a, input [3:0] b, input c_i, input sub);  
  //dopelnienie do 9 dla sub=1
  logic [3:0] compl9;
  logic [3:0] b_in;
  bcd_9 complement(compl9,b);
  assign b_in[0] = (sub && compl9[0]) || (!sub && b[0]);
  assign b_in[1] = (sub && compl9[1]) || (!sub && b[1]);
  assign b_in[2] = (sub && compl9[2]) || (!sub && b[2]);
  assign b_in[3] = (sub && compl9[3]) || (!sub && b[3]);
  
  logic [3:0] resultFA;
  logic c_out1;
  add_4bit first_add(resultFA,c_out1,a,b_in,c_i);//sub = 1 (a + dopelnienie), sub = 0 (a + b)
  logic carry;
  assign carry = (resultFA[3] && resultFA[2]) || (resultFA[3] && resultFA[1]) || c_out1;

  logic [3:0] checksum;//0xx0 gdzie x = carry
  logic [3:0] result;
  logic temp;
  assign checksum[0] = 0;
  assign checksum[3] = 0;
  assign checksum[1] = carry;
  assign checksum[2] = carry;
  add_4bit second_add(result,temp,resultFA,checksum,0);  //suma kontrolna(do modulo) + 0xx0
  //carry-out
  assign c_o = c_out1 || temp;
  assign s = result;
endmodule

module bcd_add_2digit(output [7:0] s,
                      input [7:0] a, input [7:0] b, input sub);
  
  logic c_o;
  bcd_add_1digit bcd1(s[3:0],c_o,a[3:0],b[3:0],0,sub);
  bcd_add_1digit bcd2(s[7:4],c_oo,a[7:4],b[7:4],c_o,sub);
endmodule

module bcd_addSub(output [7:0] s,
                  input [7:0] a, input [7:0] b, input sub);
 
  logic [7:0] negative;
  logic [7:0] positive;
  
  bcd_add_2digit adderPos(positive,a,b,sub);//dla sub=1 liczy a + dopelnienie(b)
  bcd_add_2digit adderNeg(negative,positive,1,0);//dopelnienie(b) + 1

  assign s[0] = (!sub && positive[0]) || (sub && negative[0]);
  assign s[1] = (!sub && positive[1]) || (sub && negative[1]);
  assign s[2] = (!sub && positive[2]) || (sub && negative[2]);
  assign s[3] = (!sub && positive[3]) || (sub && negative[3]);
  assign s[4] = (!sub && positive[4]) || (sub && negative[4]);
  assign s[5] = (!sub && positive[5]) || (sub && negative[5]);
  assign s[6] = (!sub && positive[6]) || (sub && negative[6]);
  assign s[7] = (!sub && positive[7]) || (sub && negative[7]);
endmodule

module toplevel(
  input [7:0] a,
  input [7:0] b,
  input sub,
  output [7:0] o
    );
  
  bcd_addSub final(o,a,b,sub);
endmodule
