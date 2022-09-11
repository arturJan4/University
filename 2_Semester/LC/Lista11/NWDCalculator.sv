module ctlpath(
input clk, nrst, start, 					//wejscia
input eq, lt,								//sygnaly statusu
output swap_sub, finish, load, readyLight,  //sygnaly sterujace
);
  const logic BUSY = 1'b0, READY = 1'b1;
  
  logic ready;
  always_ff @(posedge clk, negedge nrst)
    if(!nrst) begin
    	ready <= READY;
    end
    else case (ready)
      BUSY: if (eq) ready <= READY;
      READY: if (start) ready <= BUSY;
    endcase
  
	always_comb begin
 	  finish = 0; load = 0;
      case (ready)
        BUSY:  begin finish = eq;
               		 swap_sub = lt;
       		   end
        READY: begin load = start;
        			 finish = !start;
        	   end
      endcase
    end
  
  assign readyLight = ready;
endmodule

module datapath(
  input clk, nrst,
  input [7:0] ina, inb,						 // wejscia
  input swap_sub, finish, load, readyLight,  // sygnaly sterujace
  output eq, lt,							 // sygnaly statusu
  output ready,								 // wyjscia
  output logic [7:0] out,
);
  
  logic [7:0] a, b;
  always_ff @(posedge clk, negedge nrst)  	 //operacje
    if(!nrst) begin
      a <= 8'd0;
      b <= 8'd0;
    end
  else if (load) begin
  	a <= ina;
    b <= inb;
  end
  else begin
    a <= (swap_sub) ? b : a - b;
    b <= (swap_sub) ? a : b;
  end    
  
  always_ff @(posedge clk, negedge nrst)  	 //wyjscie
   if(!nrst) out <= 0;
   else if(finish) out <= a;
  assign ready = readyLight;
  		
  assign eq = (a == b);						 //sygnaly statusu
  assign lt = (a < b);
endmodule

module nwd(
  input clk, nrst, start,
  input [7:0] ina, inb,
  output ready,
  output [7:0] out,
);
  
  logic swap_sub, finish, load, readyLight;		//sygnaly sterujace
  logic eq,lt; 		 						    //sygnaly statusu   equal(a,b) | a less than b
  
  ctlpath ctl(clk,nrst,start,eq,lt,swap_sub,finish,load,readyLight);
  datapath data(clk,nrst,ina,inb,swap_sub,finish,load,readyLight,eq,lt,ready,out);
endmodule