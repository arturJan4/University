module bcd_digit(
  input [3:0] ai,
  output A,B,C,D,E,F,G
);
  assign d = ai[0];
  assign c = ai[1];
  assign b = ai[2];
  assign a = ai[3];
  assign A = (a || b || c || !d) && (!b || c || d);
  assign B = (!b || c || !d) && (!b || !c || d);
  assign C = (a || b || !c || d);
  assign D = (!b || c || d) && (a || b || c || !d) && (!b || !c || !d);
  assign E = (c && !d) || (!b && !c && !d);
  assign F = (a || b || !d) && (a || b || !c) && (!c || !d);
  assign G = (a || b || c) && (!b || !c || !d);
endmodule

