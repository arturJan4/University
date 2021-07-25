module decoder_3_to_8(
  output [3:0] o,
  input [3:0] i
);
  assign {w,x,y,z} = {i[3],i[2],i[1],i[0]};
  assign o[3] = w && (x || (!y && !z));
  assign o[2] = (x && !y && !z) || (!x && (z || y));
  assign o[1] = y ^ z;
  assign o[0] = z;
endmodule