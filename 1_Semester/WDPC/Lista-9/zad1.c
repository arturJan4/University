#include <stdio.h>
#include <stdlib.h>

// resizing 2d array using malloc with stretching with already known values

typedef struct Array2D
{
    unsigned int width, height;
    int *t;

} Array2D;

void print(Array2D *array)
{
    for(unsigned int y = 0; y < array->height; y++)
    {
        for (unsigned int x = 0; x < array->width; x++)
            printf(" %i",array->t[y*array->width+x]);
        printf("\n");
    }
}

void shiftRight(int *array, int from, int howMany, int sizeArray)
{
    for(int i = sizeArray - howMany - 1; i > from; --i)
    {
        array[i+howMany] = array[i];
    }
}

void resize(Array2D *array, unsigned int width, unsigned int height)
{
    // pusty array na starcie
    if(array->width == 0 || array->height == 0 || array == NULL || array->t == NULL)
        return;

    //resize to tych samych wymiarów
    if(array->width == width && array->height == height)
        return;

    int newSize = width * height;
    int oldSize = array->height * array->width;

    if(width < array->width)
    {   //copy before realloc to save data
        int currHeight = 1;
        int currWidth = 0;
        for(int i = width; i < oldSize; ++i)
        {
            if(currWidth >= (int)width)
            {
                currWidth  = 0;
                currHeight++;
            }
            if(currHeight >= (int)(height))
                break;
            if(currHeight * (int)array->width + currWidth >= oldSize)
                break;
            array->t[i] =  array->t[currHeight * array->width + currWidth];
            currWidth++;
        }
    }

    array->t = realloc(array->t,sizeof(int) * newSize);

    if(width > array->width)
    {
        int widthDifference = width - array->width;
        for(size_t i = 0; i < array->height; ++i)
        {
            //cleans up array
            shiftRight(array->t,width*i + array->width - 1, widthDifference,newSize);
        }
        for(int i = array->width; i < newSize; ++i)
        {
            //copies last column
            int currWidth = i % width;
            if(currWidth > (int)array->width - 1)
            {
                array->t[i] = array->t[(i/width)*width + array->width - 1];
            }
        }
    }
    if(height > array->height)
    {
        //copies last row
        for(int i = array->height * width; i < newSize; ++i)
        {
            array->t[i] = array->t[(array->height - 1)* width + (i % width)];
        }
    }

    array->height = height;
    array->width = width;
}

int main()
{
    struct Array2D a = {3,3,(int*)malloc(9*sizeof(int))};
    for (int i = 0; i < 9; i++)
        a.t[i] = i+1;

    //TESTY
    print(&a);
    printf("===============\n");
// 1 2 3
// 4 5 6
// 7 8 9
    resize(&a,4,3);
    print(&a);
    printf("===============\n");
// 1 2 3 3
// 4 5 6 6
// 7 8 9 9
    resize(&a,5,2);
    print(&a);
    printf("===============\n");
// 1 2 3 3 3
// 4 5 6 6 6
    resize(&a,2,3);
    print(&a);
    printf("===============\n");
// 1 2
// 4 5
// 4 5
    resize(&a,4,5);
    print(&a);
    printf("===============\n");
// 1 2 2 2
// 4 5 5 5
// 4 5 5 5
// 4 5 5 5
// 4 5 5 5
    free(a.t);
    return 0;
}
