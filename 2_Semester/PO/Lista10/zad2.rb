# Artur Jankowski
# PO - lista 10 - zad 2
# indeks: 317928

class Kolekcja
    attr_reader :first, :last, :length
    class Node
        attr_accessor :next, :prev, :val
        def initialize(val)
            @next = nil
            @prev = nil
            @val = val
        end

    end
    
    def initialize()
        @length = 0
        @first  = nil
        @last   = nil
    end

    def insert(val)
        @length += 1

        newNode = Node.new(val)
        if(@length == 1)
            @first = @last = newNode
        elsif(val <= @first.val)
            @first.prev = newNode
            newNode.next = @first
            @first = newNode
        elsif(val >= @last.val)
            @last.next = newNode
            newNode.prev = @last
            @last = newNode
        else
            prevNode = @first
            currNode = @first.next
            while(currNode != nil)
                if(val <= currNode.val)
                    prevNode.next = newNode
                    newNode.prev = prevNode
                    newNode.next = currNode
                    currNode.prev = newNode
                    return
                end
                prevNode = currNode
                currNode = currNode.next
            end
        end
    end

    def printKol
        print "["
        i = @first
        while(i != nil)
            print " #{i.val} "
            i = i.next
        end
        print "]"
        puts 
    end

    def get(i)
        if(@length/2 < i) #optimization, get to index i from last element
            index = @length - 1
            temp = @last
            while(index > i)
                temp = temp.prev
                index -= 1
            end
            return temp.val
        else
            index = 0
            temp = @first
            while(index < i)
                temp = temp.next
                index += 1
            end
            return temp.val
        end
    end
end

class Wyszukiwanie
    #return index of val, if element doesn't exist in collection returns nil
    def self.binarySearch(kolekcja, val)
        left = 0
        right = kolekcja.length - 1
        while(left <= right)
            mid = left + (right - left)/2
            if(kolekcja.get(mid) < val)
                left = mid + 1
            elsif(kolekcja.get(mid) > val)
                right = mid - 1
            else
                return mid
            end
        end
        return nil        
    end

    def self.InterpolationSearch(kolekcja,val)
        low = 0
        lowVal = kolekcja.get(low)
        mid = -1
        midVal = -1
        high = kolekcja.length - 1
        highVal = kolekcja.get(high)
        
        while(lowVal != highVal && val <= highVal && val >= lowVal)
            mid = low + ((val - lowVal) * (high - low))/(highVal - lowVal)
            midVal = kolekcja.get(mid)

            if (val == midVal)
                return mid
            elsif(val < midVal)
                high = mid - 1
                highVal = kolekcja.get(high)
            else
                low = mid + 1
                lowVal = kolekcja.get(low)
            end    
        end

        if(val == lowVal)
            return low
        else
            return nil
        end
    end
end

#binary search finds leftmost index
#interpolated binary search finds random index with given value
#test 1
a = Kolekcja.new()
a.insert(2)
a.insert(4)
a.insert(3)
puts a.length
a.printKol
puts Wyszukiwanie.binarySearch(a,5)        # returns nil
puts Wyszukiwanie.InterpolationSearch(a,5) # returns nil
puts Wyszukiwanie.binarySearch(a,2)
puts Wyszukiwanie.InterpolationSearch(a,2)

#test 2
b = Kolekcja.new()
(1..25).each{b.insert(rand(1..25))}
b.printKol
puts "4 na indeksie #{Wyszukiwanie.binarySearch(b,4)}"
puts "4 na indeksie #{Wyszukiwanie.InterpolationSearch(b,4)}"