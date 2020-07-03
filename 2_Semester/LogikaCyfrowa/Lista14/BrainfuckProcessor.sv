module ram(
  input clk, wr,
  input [7:0] addr, //2^8 = 256
  input [7:0] in,
  output [7:0] out
);
  logic [7:0] mem [0:255];
  assign out = mem[addr];
  always_ff @(posedge clk)
    if (wr) mem[addr] <= in;    
endmodule

module ctlPath(
  input clk, nrst, start,
  input in_valid, out_ack,			 		//sygnaly magistrali
  input [7:0] hd_s, text_s, 				//sygnaly statusu hd i text[pc]
  input c_s, mem_s,        			    	//sygnaly statusu c > 0 / mem[hd] == 0
  output pc_inc, pc_dec, pc_rst,        	//sygnaly sterujace dla pc (+1 / -1 / 0)
  output c_inc, c_dec, c_rst,		     	//sygnaly sterujace dla c  (+1 / -1 / 0)
  output hd_inc, hd_dec, hd_rst,			//sygnaly sterujace dla hd (+1 / -1 / 0)
  output mem_in, mem_inc, mem_dec, mem_rst, //sygnaly sterujace dla mem (data_in / +1 / -1 / 0)
  output text_in,							//sygnal sterujacy dla text (data_in)
  output in_ack, out_valid, 				//sygnaly magistrali
  output ready								//gotowosc ukladu do pracy
);
  const logic [2:0] READY = 3'd0, ZERO = 3'd1, WORK = 3'd2, WRITE = 3'd3,
  					READ = 3'd4, WRITE = 3'd5, LEFT = 3'd6, RIGHT = 3'd7;
  logic [2:0] state;

  always_ff @(posedge clk, negedge nrst)
    if(!nrst)
    	state <= READY;
    else unique case (state)
      READY: if(start)        state <= ZERO;
      ZERO : if(hd_s == 8'd0) state <= WORK;
      WORK :
        unique case (text_s)
          "[" : if(mem_s)  state <= RIGHT;
          "]" : if(!mem_s) state <= LEFT;
          "." : state <= WRITE;
          "," : state <= READ;
          "\0": state <= READY;
        endcase
      WRITE: if(out_ack)  state <= WORK;
      READ : if(in_valid) state <= WORK;
      RIGHT: if(text_s == "]" && !c_s) state <= WORK;
      LEFT : if(text_s == "[" && !c_s) state <= WORK;
      endcase
          
	always_comb begin
    	pc_inc = 0; pc_dec = 0; pc_rst = 0;
 		c_inc  = 0; c_dec  = 0; c_rst  = 0;
  		hd_inc = 0; hd_dec = 0; hd_rst = 0;
 		mem_in = 0; mem_inc= 0; mem_dec= 0; mem_rst = 0;
  		text_in = 0;
        in_ack = 0; out_valid = 0; ready = 0;
      unique case (state)
        READY : 
          begin
          	ready   = 1;
            text_in = (in_valid && !start);
            pc_inc  = (in_valid && !start);
            in_ack  = (in_valid && !start); 
			pc_rst  = start;
          end
        ZERO  : 
          begin
            mem_rst = 1;
            hd_inc  = 1;
          end
     	 WORK :
          unique case (text_s)
            "+" : begin mem_inc = 1; pc_inc = 1;   end
            "-" : begin mem_dec = 1; pc_inc = 1;   end
            ">" : begin hd_inc  = 1; pc_inc = 1;   end
            "<" : begin hd_dec  = 1; pc_inc = 1;   end
            "[" : begin c_rst = mem_s; pc_inc = 1; end
            "]" : 
        	  begin
                c_rst  = !mem_s;
                pc_dec = !mem_s;
                pc_inc = mem_s;
              end
            "\0": begin pc_rst = 1; hd_rst = 1;    end
      	  endcase
        WRITE : begin out_valid = 1; pc_inc = out_ack; end
        READ  : 
          begin
          	in_ack = 1;
          	mem_in = in_valid;
          	pc_inc = in_valid;
          end
        RIGHT :
          begin
            c_inc  = (text_s == "[");
            c_dec  = (c_s) && (text_s == "]");
          	pc_inc = 1;
          end
		LEFT  :
          begin
            c_inc  = (text_s == "]");
            c_dec  = (text_s == "[") && c_s;
            pc_dec = !(text_s == "[") || c_s;
            pc_inc = ((text_s == "[") && !c_s);
          end     
      endcase
    end
endmodule

module dataPath(
  input clk, nrst,
  input [7:0] in_data,						    //wejscie danych
  output [7:0] out_data,						//wyjscie danych
  output [7:0] hd_s, text_s,					//sygnaly statusu hd i text[pc]
  output c_s, mem_s,       					    //sygnaly statusu c > 0 / mem[hd] == 0
  input pc_inc, pc_dec, pc_rst,			     	//sygnaly sterujace dla pc (+1 / -1 / 0)
  input c_inc, c_dec, c_rst,					//sygnaly sterujace dla c  (+1 / -1 / 0)
  input hd_inc, hd_dec, hd_rst,				    //sygnaly sterujace dla hd (+1 / -1 / 0)
  input mem_in, mem_inc, mem_dec, mem_rst,	    //sygnaly sterujace dla mem (data_in / +1 / -1 / 0)
  input text_in 								//sygnal sterujacy dla text (data_in)
);
  logic [7:0] mem_in_data;					    //wejscie pamieci programu
  always_comb begin
  	mem_in_data = 1'bx;
    unique casez({mem_in,mem_rst, mem_inc, mem_dec})
      4'b1???: mem_in_data = in_data;
      4'b?1??: mem_in_data = 8'd0;
      4'b??1?: mem_in_data = mem + 1;
      4'b???1: mem_in_data = mem - 1;
    endcase
  end
                       
  logic code_wr;
  assign code_wr = (mem_in || mem_inc || mem_dec || mem_rst);
  logic [7:0] mem, text;
  ram memory(clk,code_wr,hd,mem_in_data,mem);
  ram code  (clk,text_in,pc,in_data,text);
  
  logic [7:0] hd, pc, c;
  always_ff @(posedge clk, negedge nrst)
    if(!nrst)
      pc <= 8'd0;
    else unique casez({pc_inc, pc_dec, pc_rst})
      3'b1??:  pc <= pc + 1;
      3'b?1?:  pc <= pc - 1;
      3'b??1:  pc <= 8'd0;
    endcase  
      
  always_ff @(posedge clk, negedge nrst)
    if(!nrst)
      hd <= 8'd0;
    else unique casez({hd_inc, hd_dec, hd_rst})
      3'b1??:  hd <= hd + 1;
      3'b?1?:  hd <= hd - 1;
      3'b??1:  hd <= 8'd0;
    endcase    
      
  always_ff @(posedge clk)
    unique casez({c_inc, c_dec, c_rst})
      3'b1??:  c <= c + 1;
      3'b?1?:  c <= c - 1;
      3'b??1:  c <= 8'd0;
    endcase
  
  //sygnaly statusu
  assign text_s = text;
  assign mem_s  = (mem == 8'd0);
  assign hd_s   = hd + 1;
  assign c_s    = (c > 0);
  assign out_data = mem;
endmodule

module toplevel(
  input clk, nrst,
  input [7:0] in_data,
  input in_valid,
  output in_ack,
  output [7:0] out_data,
  output out_valid,
  input out_ack,
  input start,
  output ready
);
   logic c_s, mem_s;                    	  //sygnaly statusu c > 0 / mem[hd] == 0
   logic [7:0] hd_s, text_s;				  //sygnaly statusu hd    / text[pc]
   logic pc_inc, pc_dec, pc_rst;			  //sygnaly sterujace dla pc (+1 / -1 / 0)
   logic c_inc, c_dec, c_rst;                 //sygnaly sterujace dla c  (+1 / -1 / 0)
   logic hd_inc, hd_dec, hd_rst;              //sygnaly sterujace dla hd (+1 / -1 / 0)
   logic mem_in, mem_inc, mem_dec, mem_rst;   //sygnaly sterujace dla mem (data_in / +1 / -1 / 0)
   logic text_in;                             //sygnal sterujacy dla text (data_in)

  ctlPath ctl(
    .clk 		(clk),
    .nrst 		(nrst),
    .start 		(start),
    .in_valid 	(in_valid),
    .out_ack 	(out_ack),
    .hd_s    	(hd_s),
    .text_s  	(text_s),
    .c_s		(c_s),
    .mem_s		(mem_s),
    .pc_inc		(pc_inc),
    .pc_dec		(pc_dec),
    .pc_rst		(pc_rst),
    .c_inc		(c_inc),
    .c_dec		(c_dec),
    .c_rst		(c_rst),
    .hd_inc 	(hd_inc),
    .hd_dec		(hd_dec),
    .hd_rst		(hd_rst),
    .mem_in		(mem_in),
    .mem_inc	(mem_inc),
    .mem_dec	(mem_dec),
    .mem_rst	(mem_rst),
    .text_in	(text_in),
    .in_ack		(in_ack),
    .out_valid	(out_valid),
    .ready      (ready),
  );
  
  dataPath data(
    .clk 		(clk),
    .nrst 		(nrst),
    .in_data    (in_data),
    .out_data   (out_data),
    .hd_s    	(hd_s),
    .text_s  	(text_s),
    .c_s		(c_s),
    .mem_s		(mem_s),
    .pc_inc		(pc_inc),
    .pc_dec		(pc_dec),
    .pc_rst		(pc_rst),
    .c_inc		(c_inc),
    .c_dec		(c_dec),
    .c_rst		(c_rst),
    .hd_inc 	(hd_inc),
    .hd_dec		(hd_dec),
    .hd_rst		(hd_rst),
    .mem_in		(mem_in),
    .mem_inc	(mem_inc),
    .mem_dec	(mem_dec),
    .mem_rst	(mem_rst),
    .text_in	(text_in),
  );
	
endmodule