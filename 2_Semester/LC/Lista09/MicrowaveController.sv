// uses FSM
module microwaveController(
input clk, nrst, door, start, finish,
output heat, light, bell,
);
  //stany
  const logic [2:0] CLOSED = 3'd0, COOK = 3'd1, BELL = 3'd2,
  					OPEN = 3'd3, PAUSE = 3'd4;
  logic [2:0] state;
  
  //funkcja wyjscia
  always_comb begin
    heat = 0; light = 0; bell = 0;
    unique case (state)
      COOK: begin light = 1; heat = 1; end
      PAUSE, OPEN: light = 1;
      BELL: bell = 1;
    endcase
  end
  
  //funkcja przejscia
  always_ff @(posedge clk or negedge nrst)
    if(!nrst) state <= CLOSED;
  else unique case(state)
    CLOSED: state <= door ? OPEN  : (start ? COOK : CLOSED);
    COOK:   state <= door ? PAUSE : (finish ? BELL : COOK);
    BELL:   state <= door ? OPEN : BELL;
    OPEN:   state <= door ? OPEN : CLOSED;
    PAUSE:  state <= door ? PAUSE : COOK;
  endcase
endmodule
