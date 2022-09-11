module memory(
input rd, wr, clk,
input [2:0] rdaddr, wraddr,
input [7:0] in,
output logic [7:0] out
);
logic [7:0] mem [7:0];
always_ff @(posedge clk)
	if (rd) out <= mem[rdaddr];
always_ff @(posedge clk)
	if (wr) mem[wraddr] <= in;
endmodule

module ctlPath(
input clk, nrst, start, wr,
input ieq, jeq, cltm, ijmeq, 					 	 //sygnaly statusu
output init, mvin, mvout, mjmset, iter, readyOut,	 //sygnaly sterujace
output wrout, wrin, cld, djms, dis,					 //sygnaly sterujace
);
  const logic [1:0] OUTER = 2'b00, INNER = 2'b01, END = 2'b10, SWAP = 2'b11;
  const logic BUSY = 1'b0, READYS = 1'b1;
  logic [1:0] state;
  logic ready;
  always_ff @(posedge clk, negedge nrst)
    if(!nrst) begin
  	  state <= OUTER;
	  ready <= READYS;
    end
    else if (readyOut)
      begin if (start) begin state <= OUTER; ready <= BUSY; end end
    else case (state)
      OUTER:
        if(!ieq) state <= INNER;
        else ready <= READYS;
      INNER:
        if(jeq) state <= END;
      END:
        if(ijmeq) state <= OUTER;
        else state <= SWAP;
      SWAP:
        state <= OUTER;
    endcase
	
  assign readyOut = ready;
  always_comb begin
      init = 0; mvin = 0; mvout = 0; mjmset = 0; iter = 0; wrout = 0; wrin = 0; cld = 0; djms = 0; dis = 0;	
      if (readyOut) begin
     	 init = start;
      	 wrin = !start && wr;
         wrout= !start && !wr;
      end
      else unique case (state)
        OUTER: mvin = !ieq;
        INNER: begin mjmset = cltm; iter = !jeq; cld = jeq; end
        END:   begin mvout = ijmeq; djms = !ijmeq; end
        SWAP:  begin mvout = 1; dis = 1; end
	  endcase
  end
  
endmodule

module dataPath(
input clk, nrst,
input [2:0] addr,
input [7:0] datain,
input init, mvin, mvout, mjmset, iter, readyOut,	 //sygnaly sterujace
input wrout, wrin, cld, djms, dis,					 //sygnaly sterujace
output ieq, jeq, cltm, ijmeq,				 	     //sygnaly statusu
output logic [7:0] dataout,
output ready,
);    
  logic rdf, wrf;
  logic [2:0] rdaddrf, wraddrf;
  logic [7:0] inf;
  memory ram(rdf, wrf, clk, rdaddrf, wraddrf,inf, dataout);
    
  always_comb begin									 //zarzadanie pamiecia
	rdf = 0; wrf = 0; rdaddrf = 0; wraddrf = 0; inf = 0;
    if(readyOut) begin
        inf = datain;
        wraddrf = addr;
        wrf = wrin;
        rdf = wrout || init;
        rdaddrf = wrout ? addr : 0;
      end
    else begin
    	wrf = dis || djms;
      	rdf = mvin || iter || cld || mvout || dis;
      	inf = dis ? m : dataout;
        rdaddrf = (mvin || mvout) ? i + 1 : (iter ? j + 1 : i);
        wraddrf =  djms ? jm : i;
    end
  end
  
  logic [2:0] i, j, jm;
  logic [7:0] m;							// korzystam z dataout jako c
  
  always_ff @(posedge clk)
    if(init)
  		i <= 0;
    else if(mvout)
  		i <= i + 1;
  
    always_ff @(posedge clk)
    if(mvin)
  		j <= i + 1;
    else if(iter)
  		j <= j + 1;
  
    always_ff @(posedge clk)
    if(mvin)
    	jm <= i;
    else if(mjmset) begin
    	jm <= j;
  	end
        
  always_ff @(posedge clk)
    if(mvin || mjmset)
    	m <= dataout;
  
  assign ready = readyOut;
  
  assign ieq   = (i == 7);
  assign jeq   = (j == 7);
  assign cltm  = (dataout < m);
  assign ijmeq = (i == jm);
endmodule

module toplevel(
input clk, nrst, start,
input [2:0] addr,
input wr,
input [7:0] datain,
output logic [7:0] dataout,
output logic ready,
);
  logic init, mvin, mvout, mjmset, iter, readyOut;		 //sygnaly sterujace
  logic wrout, wrin, cld, djms, dis;					 //sygnaly sterujace (pojedyncze instrukcje)
  logic ieq, jeq, cltm, ijmeq; 					 		 //sygnaly statusu
  
  ctlPath ctl(clk,nrst,start,wr,
              ieq,jeq,cltm,ijmeq,
              init, mvin, mvout, mjmset, iter, readyOut,
              wrout, wrin, cld, djms, dis);
  dataPath data(clk,nrst,addr,datain,
                init, mvin, mvout, mjmset, iter, readyOut, 
                wrout, wrin, cld, djms, dis, 
                ieq, jeq, cltm, ijmeq ,dataout, ready);
endmodule