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

module calcM(
input nrst,
  input clk,               
  input [15:0] d, 			//load
  input push,
  input [2:0] op, 			//if(push==0) 0 - greater / 1 - (- unarny) / 2 dodaj /3 pomnoz /
  							//4 swap / 5 load / 6 & 7 pop
  input en,                 //czy zmieniac stan
  output logic [15:0] out,  //top stosu
);
  logic [9:0] cnt;  	    //ile elementow na stosie
  const logic [2:0] GREATER = 3'd0, UNOPM = 3'd1, ADD = 3'd2, MULTIPLY = 3'd3, SWAP = 3'd4,
  LOAD = 3'd5, POP1 = 3'd6, POP2 = 3'd7;
  
  logic write;
  assign write = ((push || (op == SWAP)) && cnt > 0 && en);
  ram memory(clk,write,addr,out,past);
  logic [15:0] past;
  logic [9:0] addr;
  assign addr = push ? cnt-1 : ((op == LOAD) ? (cnt - 2 - out) : cnt-2);
  
  always_ff @(posedge clk, negedge nrst)
   if(!nrst) out <= 0;
   else if(!en) out <= out; 
   else if(push) out <= d;
   else unique case(op)
     GREATER:  out <= (out > 0) && !out[14]; 
     UNOPM:    out <= -out;
     ADD:      out <= out + past;
     MULTIPLY: out <= out * past;
     SWAP:     out <= past;   // to moze nie dzialac (past do memory)   
   	 LOAD:     out <= past;   
     POP1:     out <= past;
     POP2:     out <= past;
   endcase
 
  always_ff @(posedge clk, negedge nrst)
    if(!nrst) cnt <= 0;
    else if(!en) cnt <= cnt; 
    else if(push && (cnt != 1023)) cnt <= cnt + 1;
    else if((op == ADD || op == MULTIPLY || op == POP1 || op == POP2) && cnt > 0) cnt <= cnt - 1;  
endmodule

module mainModule(
  input clk, nrst,
  input [9:0] addr,
  input wr,
  input [15:0] datain,
  input start,
  output ready,
  output logic [15:0] out,
);
  const logic BUSY = 1'b0, READY = 1'b1;
  logic state;

  logic [15:0] p;      // odczyt z pamieci
  logic [9:0] pc;      // wskaznik instrukcji
  ram memCode(clk,(!start && wr),(wr ? addr : pc),datain,p);
  
  logic p15,p14,eq7;   // "sygnaly statusu"
  assign p15 = p[15];
  assign p14 = p[14];
  assign eq7 = (p[2:0] == 7);
  
  logic en;            // kontroler kalkulatora
  logic push;
  logic [2:0] op;      // 3 najmlodsze bity - kod instrukcji
  logic [15:0] d;      // p z diagramu
  assign en = (state == BUSY) && !(p15 && p14); // to zalezy od stanu
  assign op = p[2:0];                           // a to mozna przypisywac zawsze bo en == 0
  assign d = p;
  assign push = !p15;
  calcM calcModule(nrst,clk,d,push,op,en,out);

  always_ff @(posedge clk, negedge nrst)
    if(!nrst)
		state <= READY;
  else unique case(state)
    READY: if (start) state <= BUSY;
    BUSY: if(p15 && p14) state <= READY;
  endcase
    
  always_ff @(posedge clk)
    unique case(state)
    READY: if (start) pc <= 0;
    BUSY : if (!(p15 && (p14 || eq7))) pc <= pc + 1;
           else if(p15 && !p14 && eq7) pc <= out;
    endcase
  
  assign ready = state;
endmodule