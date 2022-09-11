module decoder_2_to_4(
output [3:0] o,
input [1:0] i
);
assign o = 4'b1 << i;
endmodule

module decoder_3_to_8(
  output [7:0] o,
  input [2:0] i
);
  logic [3:0] dec1, dec2;
  logic notMSB;
  assign notMSB = !i[2];
  //zalozylem zgodnie z poleceniem ze nie uzywamy dekodera z wejsciem aktywujacym, tylko zwyczajny

  //zerujemy wejscia w zaleznosci od przypadku
  //mozna zerowac na wyjsciu(jest czytelniej, ale wychodzi wiecej bramek)
  decoder_2_to_4 dec2x4f(dec1,{i[1] && notMSB, i[0] && notMSB});
  decoder_2_to_4 dec2x4s(dec2,{i[1] && i[2]  , i[0] && i[2]  });
    
  integer k;  
  //"czyscimy" 1 w one-hot zdekodowane z zer w systemie binarnym
  assign o[0] = notMSB && dec1[0];
  assign o[4] =   i[2] && dec2[0];
  //reszte przepisujemy
  always_comb begin
    for(k = 1; k < 4; k = k + 1)begin
      o[k] = dec1[k];
      o[k+4] = dec2[k];
    end
  end
endmodule