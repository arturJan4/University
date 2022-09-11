module ram(
  input clk, wr,
  input [9:0] addr, //2^10 = 1024
  input [15:0] in,
  output logic [15:0] out
);
  logic [15:0] mem [0:1023];
  assign out = mem[addr];
  always_ff @(posedge clk)
    if (wr) mem[addr] <= in;    
endmodule

module onp(
input nrst,
  input step,
  input [15:0] d, 			//load
  input push,
  input [1:0] op, 			//if(push==0) 0 - brak / 1 - (- unarny) / 2 dodaj, 3 pomnoz
  output logic [15:0] out,  //top stosu
  output logic [9:0] cnt,  	//ile elementow na stosie
);
  const logic [1:0] NTH = 2'b00, UNOPM = 2'b01, ADD = 2'b10, MULTIPLY = 2'b11;
  ram memory(step,(push && cnt > 0),addr,out,past);
  logic [15:0] past;
  logic [9:0] addr;
  assign addr = push ? cnt-1 : cnt-2;
  
  always_ff @(posedge step, negedge nrst)
   if(!nrst) out <= 0;
   else if(push) out <= d;
   else unique case(op)
         UNOPM:    out <= -out;
         ADD:      out <= out + past;
         MULTIPLY: out <= out * past;
   endcase
 
  always_ff @(posedge step, negedge nrst)
    if(!nrst) cnt <= 0;
    else if(push && (cnt != 1023)) cnt <= cnt + 1;
    else if((op == ADD || op == MULTIPLY) && cnt > 0) cnt <= cnt - 1;  
endmodule

module toplevel(
  input nrst,
  input step,
  input [15:0] d, 			//load
  input push,
  input [1:0] op, 			//if(push==0) 0 - brak / 1 - (- unarny) / 2 dodaj, 3 pomnoz
  output logic [15:0] out,  //top stosu
  output logic [9:0] cnt,  	//ile elementow na stosie
);
  onp test(nrst,step,d,push,op,out,cnt);
endmodule