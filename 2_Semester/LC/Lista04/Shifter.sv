// shifts by one bit to left or right
module toplevel(
  output [3:0] o,
  input [3:0] i, 
  input l, 
  input r);
	
  function LRShift(input l, r, prev, curr, next);
    LRShift = (l && prev) || (r && next) || (!(l^r) && curr);
  endfunction
  
  assign o[0] = LRShift(l,r,0,i[0],i[1]);
  assign o[1] = LRShift(l,r,i[0],i[1],i[2]);
  assign o[2] = LRShift(l,r,i[1],i[2],i[3]);
  assign o[3] = LRShift(l,r,i[2],i[3],0);
endmodule