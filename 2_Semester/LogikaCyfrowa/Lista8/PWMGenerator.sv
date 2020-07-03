// Pulse Width Modulation
module PWMgen(
  input clk,
  input [15:0] d,   		//load
  input [1:0] sel,	    	//0-nth 1-cmp 2-top 3-cnt
  output logic [15:0] cnt,	//counter
  output logic [15:0] cmp,	//compare
  output logic [15:0] top,
  output out 				//generator output
);  
  always_ff @(posedge clk)//counter
    if(sel == 2'b11) cnt <= d;
    else if(cnt < top) cnt <= cnt + 16'd1;
  	else cnt <= 16'd0;
  
  always_ff @(posedge clk)//comparator
    if(sel == 2'b01) cmp <= d;	
  
  always_ff @(posedge clk)//top value
    if(sel == 2'b10) top <= d;	

  assign out = (cmp > cnt);
endmodule