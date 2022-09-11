// more complicated function implementation
module toplevel(output o, input [3:0] i);
  assign x = i[0];
  assign y = i[1];
  assign z = i[2];
  assign w = i[3];
  assign o = (x || y || w ) && ( y || z || w) && ( x || z || w) && ( x || y || z) && (!x || !y || !z || !w);
endmodule
