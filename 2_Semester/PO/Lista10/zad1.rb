# Artur Jankowski
# PO - lista 10 - zad 1
# indeks: 317928

class Kolekcja
    def initialize
    end
    def initWithArray(arr)
        @array = arr
    end
    def swap(i, j)
        temp = @array[i]
        @array[i] =  @array[j]
        @array[j] = temp
    end
    def length()
        @array.length
    end
    def get(i)
        @array[i]
    end
    def set(i, val)
        @array[i] = val
    end
    def copy(i,j)
        temp = Kolekcja.new()
        temp.initWithArray(@array[i..j])
        return temp
    end
    def compare(i,j)
        if(@array[i] == @array[j])
            0            
        elsif(@array[i] > @array[j])
            1
        else
            -1
        end
    end
    def print
        puts @array.to_s
    end
    def sort
        if(self.length <= 42) #because merge sort creates overhead, strategy pattern
            Sortowanie.sort1(self)
        else
            Sortowanie.sort2(self)
        end
    end
    def isSorted #in ascending order
        for i in 0...(length-1)
            if(compare(i,i+1) == 1)
                return false
            end
        end
        return true
    end
end
class Sortowanie
    #bubble sort
    def self.sort1(kolekcja)
        if(!(kolekcja.respond_to?("swap") &&
           kolekcja.respond_to?("compare")&&
           kolekcja.respond_to?("length")))
           begin
           raise RuntimeError.new("Collection doesn't respond to swap and compare so it cannot be sorted")
           end
        end
        for i in 0...kolekcja.length do
            for j in 0...(kolekcja.length-i-1) do
                if(kolekcja.compare(j,j + 1) == 1)# >
                    kolekcja.swap(j, j + 1)
                end
            end
        end
    end
    #merge sort
    def self.sort2(kolekcja)
        if(!(kolekcja.respond_to?("length") &&
            kolekcja.respond_to?("get")     &&
            kolekcja.respond_to?("set")     &&
            kolekcja.respond_to?("copy")    && 
            kolekcja.respond_to?("compare")))
            begin
            raise RuntimeError.new("Collection doesn't respond to certain methods so it cannot be sorted")
            end
         end
        mergeSort(kolekcja,0,kolekcja.length-1)
    end
    #insertion sort
    def self.sort3(kolekcja)
        if(!(kolekcja.respond_to?("length") &&
            kolekcja.respond_to?("get")     &&
            kolekcja.respond_to?("set")))
            begin
            raise RuntimeError.new("Collection doesn't respond to certain methods so it cannot be sorted")
            end
         end
        for i in 1...kolekcja.length do
             j = i - 1
             key = kolekcja.get(i)
             while (j >= 0 && kolekcja.get(j) > key)
                 kolekcja.set(j+1, kolekcja.get(j))
                 j -= 1
             end
            kolekcja.set(j+1,key)
         end
    end

    private
    def self.mergeSort(kolekcja, lPtr, rPtr)
        if(lPtr < rPtr)
            midPtr = lPtr + (rPtr - lPtr)/2
            mergeSort(kolekcja, lPtr, midPtr)
            mergeSort(kolekcja, midPtr + 1, rPtr)
            merge(kolekcja, lPtr, rPtr)
        end
    end

    def self.merge(kolekcja, lPtr, rPtr)
        midPtr = lPtr + (rPtr - lPtr)/2
        temp = kolekcja.copy(lPtr,rPtr)
        curr = 0
        i = lPtr
        j = midPtr + 1
        #merging into temp collection
        while ((i <= midPtr) && j <= rPtr)
            if(kolekcja.compare(i,j) != 1) # i <= j
                temp.set(curr,kolekcja.get(i))
                i += 1
            else
                temp.set(curr,kolekcja.get(j))
                j += 1
            end
            curr += 1
        end

        #if some element are left
        while (i <= midPtr)
            temp.set(curr,kolekcja.get(i))
            i += 1
            curr += 1
        end
        while (j <= rPtr)
            temp.set(curr,kolekcja.get(j))
            j += 1
            curr += 1
        end
        #copying from temp collection to the one passed in function call
        i = 0
        while(i <= rPtr - lPtr)
            kolekcja.set(i+lPtr,temp.get(i))
            i += 1
        end
    end
end
test = Kolekcja.new()

#test 1
test.initWithArray(Array.new(5){|i| i})
test.swap(0,1)
test.print
puts test.length
puts "test1 is Sorted: #{test.isSorted} "
test.sort
test.print
puts "test1 is Sorted (after insertion sort): #{test.isSorted} "

#test 2
test.initWithArray(Array.new(200){|i| i})
test.set(3,0)
test.set(99,0)
test.swap(0,83)
test.swap(1,22)
#test.print
puts "test2 is Sorted: #{test.isSorted} "
test.sort
puts "test2 is Sorted (after merge sort): #{test.isSorted} "
#test.print