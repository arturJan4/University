# Artur Jankowski
# PO - lista 8 zad 1
# indeks: 317928

require "test/unit/assertions"
include Test::Unit::Assertions

class Integer
    @@hashSlowa = {"1" => "jeden"   , "2" => "dwa"   ,  
                   "3" => "trzy"    , "4" => "cztery", 
                   "5" => "piec"    , "6" => "szesc" , 
                   "7" => "siedem"  , "8" => "osiem" ,
                   "9" => "dziewiec", "0" => "zero"}

    def czynniki
        return (1..self).select{ |n| self % n == 0}
    end
    #self == n, y == m 
    def ack(y)
        if self == 0
            return y + 1
        elsif y == 0
            return (self-1).ack(1)
        else
            return (self-1).ack((self.ack(y-1)))
        end
    end

    def doskonala
        if(self <= 0)
            return false
        end
        suma = -self #usuwa ostatni dzielnik (np. 6 z dzielników 6)
        self.czynniki.each{ |n| suma += n}

        return suma == self
    end

    def slownie
        return self.to_s.split('').map{ |n| @@hashSlowa.fetch(n)}.join(" ")
    end
end

#TESTS - czynniki
assert_equal [1,2,3,6], 	6.czynniki,  "czynniki 6"
assert_equal [1], 			1.czynniki,  "czynniki 1"
assert_equal [1,2], 		2.czynniki,  "czynniki 2"
assert_equal [1,3,5,15], 	15.czynniki, "czynniki 15"
assert_equal [1,5,25], 		25.czynniki, "czynniki 25"

#TESTS - Ackermann
assert_equal 1, 0.ack(0),  "Ackerman(0,0)"
assert_equal 2, 1.ack(0),  "Ackerman(1,0)"
assert_equal 5, 3.ack(0),  "Ackerman(3,0)"
assert_equal 13, 4.ack(0), "Ackerman(4,0)"
assert_equal 9, 2.ack(3),  "Ackerman(2,3)"
assert_equal 7, 2.ack(2),  "Ackerman(2,2)"
assert_equal 5, 2.ack(1),  "Ackerman(2,1)"

#TESTS - Doskonala
assert_boolean 6.doskonala
assert_boolean 28.doskonala
assert_boolean 496.doskonala
assert_boolean !(0.doskonala)
assert_boolean !(1.doskonala)
assert_boolean !(4.doskonala)
assert_boolean !(12.doskonala)

#TESTS - Slownie
assert_equal "dwa jeden trzy", 213.slownie, "213 slownie"
assert_equal "zero",  		   0.slownie, 	"0 slownie"
assert_equal "jeden",		   1.slownie, 	"1 slownie"
assert_equal "cztery dwa", 	   42.slownie, 	"42 slownie"

