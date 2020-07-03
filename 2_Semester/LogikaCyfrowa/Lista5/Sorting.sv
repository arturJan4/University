// not efficient solution, generates a really large circuit
module sort(
  output [15:0] o,
  input [15:0] i
);
  integer k, j, m;
  logic [15:0] temp;

  //bubble sort
  always_comb begin
    temp = i;
    for(k = 0; k < 3; k = k + 1)begin
      for(j = 0; j < 3; j = j + 1)begin
        m = j * 4;
        if(temp[(m+3):m] > temp[(m+7):(m+4)])//swap
          temp[m+7:m] = {temp[(m+3):m],temp[(m+7):(m+4)]};
        else
          temp[m+7:m] = {temp[(m+7):(m+4)],temp[(m+3):m]};
      end
    end  
  end
  assign o = temp;
endmodule

module testModule(
  output [15:0] o,
  input [15:0] i
);
  //for easier testing
  sort sorter(o,i);
endmodule