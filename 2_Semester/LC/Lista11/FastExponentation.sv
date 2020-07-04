module multiplier(
  input [15:0] a, x,
  input remainder2,
  output [15:0] o
);
  assign o = (remainder2 ? a : x) * x; 
endmodule

module fastExp(
  input clk, nrst, start,
  input [15:0] inx,
  input [7:0] inn,
  output logic ready,
  output logic [15:0] out,
);
  const logic BUSY  = 1'b0;
  const logic READY = 1'b1;
  
  logic [15:0] a, x, n, mult;
  multiplier mult1(a,x,n[0],mult);
  
  always_ff @(posedge clk, negedge nrst)
    if(!nrst) begin
      ready <= READY;
      out <= 16'd0;
    end
  	else case (ready)
        BUSY:
          if(!n) begin
         	out <= a; ready <= READY;
          end
          else if(n[0]) begin //n % 2 == 1
            a <= mult;
            n <= n - 1;
          end
      	  else begin          //n % 2 == 0
            x <= mult;
            n <= n >> 1;
          end
      	READY: 
          if(start) begin
  			a <= 16'd1; x <= inx; n <= inn;
            ready <= BUSY;
     	  end
    endcase
endmodule

module test(
  input clk, nrst, start,
  input [15:0] inx,
  input [7:0] inn,
  output logic ready,
  output logic [15:0] out
);
  fastExp test(clk,nrst,start,inx,inn,ready,out);
endmodule