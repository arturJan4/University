# Artur Jankowski
# PO - lista 9 - zad 1 i 3
# indeks: 317928

require "test/unit/assertions"
include Test::Unit::Assertions

# Zakomentowalem testy wykresow - w funkcji rysuj mozna zmienic ich szerokosc i wysokosc gdyby nie pasowaly do terminala

class Funkcja
    def initialize(proc)
        @proc = proc
    end

    def value(x)
        @proc.call(x)
    end

    def zerowe(a,b,e)
        def sign(num)
            if(num < 0)
                return 'neg'
            else
                return 'pos'
            end
        end
        #miejsce zerowe [a,b] z dokladnoscia e
        valA = value(a)
        valB = value(b)

        if(valA == 0)
            return a
        elsif(valB == 0)
            return b
        end

        if((a-b).abs < e)
            return nil
        end
        half = (a + b).to_f/2

        if(value(half).abs < e)
            return half
        elsif(sign(value(half)) == sign(valA))
            return zerowe(half,b,e) 
        else
            return zerowe(a,half,e)
        end
    end
    
    def pole(a,b)
        @@epsilon = 0.0001 #delta x
        iterA = a
        sum = 0
        while(iterA < b)
            sum += @@epsilon * value((iterA - @@epsilon/2)) #metoda trapezoidalna
            iterA += @@epsilon
        end
        
        return sum
    end

    def poch(x)
        @@h = 0.0001
        return (value(x+@@h) - value(x))/@@h
    end

    #rysuje na przedziale [a,b]
    #skala y dopasowuje sie automatycznie do wartosci minimalnych i maksymalnych funkcji na przedziale (mozna zmienic dy by ustalic stala wysokosc)
    def rysuj(a,b)
        
        #szerokosc osi OY
        @@yAxisThickness = 2

        #wyglad wykresu
        @@backgroundSymbol = ' '
        @@lineSymbol = '*'

        #ilosc jednostek dx dy
        @@szerokosc = 128
        @@wysokosc = 32

        #znajduje minimum i maximum funkcji w [a,b], aby potem dobrze dopasowac dy, by zmiescic wartosci
        def maxMin(a,b)
            @@epsilon = 0.01
            i = a
            min = value(a).to_f
            max = value(a).to_f
            while(i <= b)
                if(value(i) < min)
                    min = value(i)
                elsif(value(i) > max)
                    max = value(i)
                end
                i += @@epsilon
            end
            return max,min
        end
        
        #porownanie floatow
        def closeEnough(val,expV,changeOfVal)
            if((val - expV).abs < changeOfVal)
                return true
            else
                return false
            end
        end

        max,min = maxMin(a,b)
        heightWykres = (max - min).to_f.abs

        widthRatio = (b - a).to_f.abs/@@szerokosc
        heightRatio = heightWykres/@@wysokosc

        #akceptowalny blad (od srodka kratki do brzegu kratki, w jednostkach)
        @@dx = widthRatio/2
        @@dy = heightRatio/2

        for i in 0..@@wysokosc do
            realHeight = (@@wysokosc - i) * heightRatio + min #wysokosc w skali rzeczywistej
            midPointY = realHeight
            midPointY = (midPointY > 0) ? midPointY - @@dy : midPointY + @@dy

            for j in 0...@@szerokosc do
                realWidth = (a + (j * widthRatio))

                if(j==0)
                    print realHeight.round(2).to_s.center(heightWykres.to_s.length + 4, "||")
                end

                if(closeEnough(realHeight,0,@@dy) and (closeEnough(realWidth,0,@@dx)))
                    @@yAxisThickness.times do print 'X' end
                elsif(closeEnough(realWidth,0,@@dx))
                    @@yAxisThickness.times do print '|' end
                elsif(closeEnough(realHeight,0,@@dy))
                    print '='
                else 
                    midPointX = realWidth
                    midPointX = (midPointX > 0) ? midPointX - @@dx : midPointX + @@dx
                    
                    if(closeEnough(value(midPointX),midPointY,@@dy))
                        print @@lineSymbol
                    else
                        print @@backgroundSymbol
                    
                    end
                end
            end
            puts
        end
    end
end

def assertFloat(x,expX,eps,mes)
    assert((x-expX).abs < eps , mes)
end

#testy z Wolfram Alpha
test = Funkcja.new(Proc.new{|x| x**2 - 4})
puts "x^2 - 4:"
assert_equal(21,test.value(5), "test(5) != 21")   
assertFloat(test.zerowe(-4,-1,0.01),-2,0.01,"test zerowe(-4,1)")
assertFloat(test.pole(0,2),-5.3,0.1,"calka z test od 0 do 2")
assertFloat(test.poch(3),6,0.01,"pochodna w test(3)")

#test.rysuj(-6,6)

puts "x^2 * sin(x):"
testSin = Funkcja.new(Proc.new{ |x| (x**2) * Math.sin(x)})
assertFloat(testSin.value(5),-23.97, 0.1, "testSin(5) != -23.97..")   
assertFloat(testSin.zerowe(-4,1,0.1),-3.14,0.1,"testSin zerowe(-4,1)")
assertFloat(testSin.pole(-15,2),-187.9,4,"calka z testSin od -15 do 2")
assertFloat(testSin.poch(2),1.97,0.01,"pochodna w test(3)")

#testSin.rysuj(-15,3)

testX = Funkcja.new(Proc.new{ |x| x})
#testX.rysuj(-3,7)





















