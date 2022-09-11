# Artur Jankowski
# PO - lista 8 zad 3
# indeks: 317928

class Jawna
    def initialize(jawna)
        @napis = jawna
    end

    def to_s
        @napis
    end

    def zaszyfruj(klucz)
        temp = @napis.split('').map{ |c| (klucz.key?(c) ? klucz.fetch(c) : c)}.join()
        return Zaszyfrowane.new(temp)
    end
end

class Zaszyfrowane
    def initialize(zaszyfrowana)
        @napis = zaszyfrowana
    end

    def to_s
        @napis
    end

    def odszyfruj(klucz) #reverse hash lookup
        temp = @napis.split('').map{ |c| (klucz.has_value?(c) ? klucz.key(c) : c)}.join()
        return Jawna.new(temp)
    end
end

#TESTY

key = {"x" => "e",
       "e" => "t",
       "t" => "x"}
a = Jawna.new("text")
b = a.zaszyfruj(key)
c = b.odszyfruj(key)

puts  b.to_s
puts  c.to_s

key2 = {'a' => 'b',
        'b' => 'r',
        'r' => 'y',
        'y' => 'u',
        'u' => 'a'}

a2 = Jawna.new("The quick brown fox jumps over the lazy dog.")
b2 = a2.zaszyfruj(key2)
c2 = b2.odszyfruj(key2)

puts b2.to_s
puts c2.to_s

