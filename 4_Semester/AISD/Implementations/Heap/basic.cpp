#include <iostream>
#include <algorithm>
#include <vector>

// basic max-heap implementation

// using std::vector as a raw array (it's just easier for my sanity) 
// changes are left to be made as an exercise to the reader :)

struct Heap
{
    private:
    size_t heapSize; // indexed from 1 to n inclusive
    std::vector<int> heapTable;

    public:
    Heap(int array[], size_t size)
    {
        //std::cout << "ctor called \n";
        heapSize = size + 1;
        heapTable.reserve(size);
        heapTable.push_back(-1);
        for(size_t i = 1; i <= size; ++i)
        {
            heapTable.push_back(array[i-1]);
        }
    }
    std::vector<int> getTable()
    {
        return heapTable;
    }

    void printTable()
    {
        for(size_t i = 1; i < heapSize; ++i)
        {
            std::cout << heapTable[i] << " ";
        }
        std::cout << "\n";
    }

    static size_t leftChild(size_t position)
    {
        return position * 2; // compiler does position << 1 so it's fast
    }

    static size_t rightChild(size_t position)
    {
        return position * 2 + 1; 
    }
    
    static size_t parent(size_t position)
    {
        return position / 2; 
    }    

    // O(1) !
    int getMax()
    {
        return heapTable[1];
    }

    void changeElement(size_t position, int value)
    {
        int temp = heapTable[position];
        heapTable[position] = value;
        if(value < temp)
            moveDown(position);
        else
            moveUp(position);
    }

    void moveUp(size_t position)
    {
        // swap up until it's not possible      
        size_t i = position; 
        size_t parent = this->parent(position);
        while(i != 1 && heapTable[i] > heapTable[parent])
        {
            std::swap(heapTable[i], heapTable[parent]);
            i /= 2;
            parent = this->parent(i);
        }
    }

    void moveDown(size_t position)
    {
        // swap up until it's not possible      
        size_t left = leftChild(position);
        size_t right = rightChild(position);  

        if(left < heapSize && heapTable[position] < heapTable[left])  
        {
            std::swap(heapTable[position], heapTable[left]);
            moveDown(left); 
        } 
    
        if(right < heapSize && heapTable[position] < heapTable[right])  
        {
            std::swap(heapTable[position], heapTable[right]);
            moveDown(right); 
        }
    }
    
    // n log n time needed
    // up to down build
    void buildHeap_slow()
    {
        for(size_t i = 1; i < heapSize; ++i)
        {
           moveUp(i);
        }
    }
    // O(n) time
    // down to up (bottom-up) build (use left sub-heap and right sub-heap to make a bigger heap adding a root)
    void buildHeap_faster()
    { 
        size_t nonLeaf= (heapSize-1)/2; // last non-leaf node

        for(int i = nonLeaf; i >= 1; --i) 
        {
            moveDown(i);
        }
    }

    std::vector<int> heapSort()
    {
        //it would be better if moveDown and moveUp accepted a range parameter
        //but this is a workaround if they don't have it
        //this->buildHeap_faster();
        std::vector<int> temp = heapTable;
        size_t tempSize = heapSize;

        std::vector<int> result;
        result.reserve(heapSize-1);

        for(int i = heapSize-1; i >= 2; --i)
        {
           result.push_back(getMax());
           std::swap(heapTable[1], heapTable[i]); // swap with first element (local max), push current to last 
           
           heapSize -= 1;         // delete last element
           heapTable.pop_back();
           
           moveDown(1); // heapify in log(n) time
        }

        heapTable = std::move(temp);
        heapSize = tempSize;

        return result;
    }
    // can be optimized further for number of comparisions by moving 'empty' spot
    // downwards instead of moving the heapTable[i] (which is possibly small and would end up at the bottom)
    // 1. move the 'hole' down
    // 2. swap elements heapTable[current] & heapTable[i]
    // 3. move heapTable[i] up (on average only two moves up)
    
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    // some basic heap usage

    int elements[8] = {1,2,3,4,9,7,5,4};
    
    Heap myHeap(elements, 8);
    myHeap.buildHeap_faster();
    
    myHeap.printTable();
    std::cout << "parent of 7th element is: " << (myHeap.getTable())[myHeap.parent(7)] << "\n";

    std::cout << "sorted: ";
    for(auto i : myHeap.heapSort())
    {
        std::cout << i << " ";
    }
    std::cout << "\n";
    return 0;
}