// based on paper by A. Arvind, C. Pandu Rangan 
// doi=10.1.1.472.6213
// Symmetric Min-Max heap: A simpler data structure for double-ended priority queue 

#include <iostream>
#include <algorithm>
#include <vector>

// min-max heap using array (vector here!) to store the heap
// can be used for double-ended priority queue

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
        return position * 2 + position % 2; // compiler does position << 1 so it's fast
    }

    static size_t rightChild(size_t position)
    {
        return position * 2 + 2 + position % 2; 
    }
    
    static size_t parent(size_t position)
    {
        const size_t& i = position;
        return ((i/2 % 2) == (i % 2)) ? i/2 : i/2 - 1; 
    }    

    // O(1) !
    int getMax()
    {
        return heapTable[1];
    }

    int getMin()
    {
        return heapTable[2];
    }

    void changeElement(size_t position, int value)
    {
        /*
        int temp = heapTable[position];
        heapTable[position] = value;
        if(value < temp)
            moveDown(position);
        else
            moveUp(position);
        */
    }

    void moveUp(size_t position)
    {
        // swap up until it's not possible      
        size_t i = position; 
        int x = i % 2;
        size_t parent = this->parent(i);
        if(x)
        {
            while(i > 2 && heapTable[i] > heapTable[parent])
            {   
                std::swap(heapTable[i], heapTable[parent]);
                i = parent;
                parent = this->parent(i);
            }          
        }
        else
        {
            while(i > 2 && heapTable[i] < heapTable[parent])
            {   
                std::swap(heapTable[i], heapTable[parent]);
                i = parent;
                parent = this->parent(i);
            }    
        }
    }

    void moveDown(size_t position)
    {
        // swap up until it's not possible      
        size_t left = leftChild(position);
        size_t right = rightChild(position);  

        int x = position % 2;
        if (x)
        {
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
        else
        {
            if(left < heapSize && heapTable[position] > heapTable[left])  
            {
                std::swap(heapTable[position], heapTable[left]);
                moveDown(left); 
            } 
    
            if(right < heapSize && heapTable[position] > heapTable[right])  
            {
                std::swap(heapTable[position], heapTable[right]);
                moveDown(right); 
            }
        }
    }
    
    // n log n time needed
    // up to down build
    void buildHeap()
    {
        for(size_t i = 1; i < heapSize; ++i)
        {
           int x = heapTable[i];
           if(i % 2) // add to maxHeap
           {
               if(i != 1)
               {
                   int j;
                   
                   if(i % 4 == 3)
                   {
                       j = (i+1)/2;
                   }
                   else
                   {
                       j = i/2;
                   }
                   
                   int y = heapTable[j];
                   if(x < y)
                   {
                       std::swap(heapTable[i], heapTable[j]);
                       moveUp(j); // move up in L
                   }
                   else
                   {
                       moveUp(i); // move up in H
                   }
               }
               else
               {
                   moveUp(i); // move up in H
               }
           }
           else
           {
                if(i != 1 && x > heapTable[i-1])
                {
                       std::swap(heapTable[i], heapTable[i-1]);
                       moveUp(i-1); // move up in H 
                }
                else
                {
                       moveUp(i); // move up in L
                }
           }
        }
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    // some basic heap usage

    int elements[8] = {1,2,3,4,5,6,7,8};
    
    Heap myHeap(elements, 8);
    myHeap.buildHeap();
    myHeap.printTable();
    
    int elements2[8] = {8,3,4,2,10,9,6,7};
    
    Heap myHeap2(elements2, 8);
    myHeap2.buildHeap();
    myHeap2.printTable();

    int elements3[8] = {2,3,4,10,8,6,7,9};
    
    Heap myHeap3(elements3, 8);
    myHeap3.buildHeap();
    myHeap3.printTable();
    return 0;
}