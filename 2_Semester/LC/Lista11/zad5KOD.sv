module ctlPath(
input clk, nrst,
input wej, wyj,
output add, sub, 		//sygnaly sterujace
);
  const logic [1:0] START = 2'b11, ENTRCL = 2'b10, ENTROP = 2'b01, ALLOP = 2'b00; //start, entry close, entry opened, all open
	
  logic [1:0] inputFot;
  logic [1:0] state;
  assign inputFot = {wej,wyj};
  always_ff @(posedge clk, negedge nrst)
    if (!nrst)
        state <= START;
  	else 
    	state <= inputFot;
  	
  always_comb begin
    add = 0; sub = 0;
    case (state)
      ENTRCL: sub = (inputFot == START || inputFot == ENTROP);
      ENTROP: add = (inputFot == START || inputFot == ENTRCL);
      ALLOP: if(inputFot == ENTRCL) add = 1;
      	 	 else if (inputFot == ENTROP) sub = 1;
    endcase
  end
endmodule

module dataPath(
input clk, nrst,
input add, sub, 		//sygnaly sterujace
output logic [7:0] cnt,
);
  always_ff @(posedge clk, negedge nrst)
    if (!nrst)
    	cnt <= 0;
  	else if (add)
    	cnt <= cnt + 1;
  	else if (sub)
    	cnt <= cnt - 1;
endmodule

module peopleCounter(
input clk, nrst,
input wej, wyj,
output logic [7:0] cnt,
);
  logic add, sub;
  ctlPath ctrl(clk,nrst,wej,wyj,add,sub);
  dataPath data(clk,nrst,add,sub,cnt);
endmodule