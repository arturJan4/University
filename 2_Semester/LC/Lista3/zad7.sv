module bcd_9(
  input [3:0] ai,
  output [3:0] o
);
  
  assign w = ai[0];
  assign z = ai[1];
  assign y = ai[2];
  assign x = ai[3];

  assign o[3] = (!x && !y && !z);
  assign o[2] = !x && (y ^ z);
  assign o[1] = !x && z;
  assign o[0] = !w && (!x || (x && !y && !z));
    
endmodule
          
