module peopleCounter(
input clk, nrst,
input wej, wyj,
output logic [7:0] cnt,
);
  const logic [1:0] START = 2'b11, ENTRCL = 2'b10, ENTROP = 2'b01, ALLOP = 2'b00;
	
  logic [1:0] inputFot;
  logic [1:0] state;
  assign inputFot = {wej,wyj};
  always_ff @(posedge clk, negedge nrst)
    if (!nrst) begin
        state <= START;
      	cnt <= 0;
    end
  	else begin case(state)
      ENTRCL:
        begin 
          if (inputFot == START || inputFot == ENTROP) cnt <= cnt - 1;
        end
      ENTROP:
        begin
          if (inputFot == START || inputFot == ENTRCL) cnt <= cnt + 1;
        end
      ALLOP:
        begin
        if (inputFot == ENTRCL) cnt <= cnt + 1;
      	else if (inputFot == ENTROP) cnt <= cnt - 1;
        end
   	  endcase
    	state <= inputFot;
    end
  
endmodule
