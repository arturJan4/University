module helper(
  input [7:0] a,
  input [7:0] b,
  input [3:0] n,
  output [7:0] o);
 	
  logic [15:0] x;
  assign x = {a,b};
  assign o[7:0] = x[(n+7):n];
endmodule

module funnelShifter(
  input [7:0] i,
  input [3:0] n,
  input ar,  //arithmethic1/logical0
  input lr,  //left1/right0
  input rot, //rotation/shift
  output[7:0] o);
  
  logic MSB;
  logic [7:0] fill;//fill with MSB for right arithmetical shift
  assign MSB = (ar && !lr) ? i[7] : 0;
  assign fill = {MSB,MSB,MSB,MSB,MSB,MSB,MSB};
  
  logic [3:0] n1;
  logic [7:0] a;//left array
  logic [7:0] b;//right array
  //rotation takes precedence
  assign a = (lr || rot)? i : fill;
  assign b = (lr && !rot) ? fill : i;
  assign n1 = lr ? (8-n) : n;
  
  helper help(a,b,n1,o);
endmodule