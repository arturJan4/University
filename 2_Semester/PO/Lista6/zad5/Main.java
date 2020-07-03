/*
    PO - lista 6 - zad 5
    Artur Jankowski
    Merge Sort Wielowatkowy
    indeks:317928
 */
//w jednym pliku dla wygody
package com.company;
import  java.lang.Exception;
import  java.util.Random;

class MergeSort extends Thread{
    private final int[] tablica;
    private int startIter, endIter;

    public MergeSort(int[] tablica, int startIter, int endIter)
    {
        this.tablica = tablica;
        this.startIter = startIter;
        this.endIter = endIter;
    }

    public MergeSort(int[] tablica) throws Exception//overloading na pierwsze wywolanie
    {
        this.tablica = tablica;
        this.startIter = 0;
        this.endIter = tablica.length - 1; //indeks ostatniego elementu

        Thread first = this;
        first.start();
        first.join();
    }

    public void run()
    {
        if(startIter == endIter)
            return;

        int mid = (startIter + endIter)/2;
        Thread[] threads = new Thread[2];

        threads[0] = new MergeSort(tablica,startIter,mid);
        threads[1] = new MergeSort(tablica,mid + 1, endIter);

        threads[0].start();
        threads[1].start();

        try {
            for (Thread curr : threads) {
                curr.join();//poczekaj az skoncza dzialanie
            }
            merge(tablica,startIter,mid,mid+1,endIter);
        }catch(Exception ex)
        {
            System.out.println(ex + " startIter: " + startIter + " endIter: " + endIter + " mid: " + mid);
        }
    }

    private static void merge(int[] tablica, int startIterL, int endIterL, int startIterP, int endIterP) throws Exception//lewa i prawa
    {
        if(startIterL < 0 || startIterP < 0 || startIterL >= startIterP
                          || endIterL >= endIterP || startIterL > endIterL || startIterP > endIterP)
        {
            throw new Exception("first array should be on the left of the second");
        }

        int lengthOfArray = (endIterP - startIterP + 1) + (endIterL - startIterL + 1);
        int[] tempArray = new int[lengthOfArray];

        int iterL = startIterL;
        int iterP = startIterP;

        for(int i = 0; i < lengthOfArray; ++i)
        {
            if(iterL <= endIterL && iterP <= endIterP)
            {
                if(tablica[iterL] < tablica[iterP])
                {
                    tempArray[i] = tablica[iterL];
                    iterL++;
                }
                else
                {
                    tempArray[i] = tablica[iterP];
                    iterP++;
                }
            }
            else if(iterL <= endIterL)//przepisywanie lewej podtablicy
            {
                tempArray[i] = tablica[iterL];
                iterL++;
            }
            else if(iterP <= endIterP)//przepisywanie prawej podtablicy
            {
                tempArray[i] = tablica[iterP];
                iterP++;
            }
            else
                throw new Exception("merge - error");
        }

        int ptrL = startIterL;
        for(int i = 0; i < lengthOfArray; ++i)
        {
            tablica[ptrL] = tempArray[i];
            ptrL++;
        }
    }
}

class testUtil
{
    public static boolean isSorted(int[] array)
    {
        for(int i = 0; i < array.length - 1; ++i)
        {
            if(!(array[i] <= array[i+1]))
                return false;
        }
        return true;
    }

    public static void printArray(int[] array)
    {
        for(int i : array)
        {
            System.out.print(i + " ");
        }
        System.out.println();
    }
}

public class Main {
    public static void main(String[] args) {
        int[] temp1 = {1, 2, 1, 5, 0};
        int[] temp2 = {1};
        int[] temp3 = {4, 3, 2, 1};
        try {
            MergeSort x1 = new MergeSort(temp1);
            MergeSort x2 = new MergeSort(temp2);
            MergeSort x3 = new MergeSort(temp3);

            testUtil.printArray(temp1);
            testUtil.printArray(temp2);
            testUtil.printArray(temp3);

            //losowa tablica
            Random rand = new Random();
            int[] testObciazeniowy;
            int ileEl = 1000;//jedno zero wiecej i to juz duzo watkow
            testObciazeniowy = new int[ileEl];
            for (int i = 0; i < ileEl; ++i) {
                testObciazeniowy[i] = rand.nextInt(1000000);
            }
            MergeSort x4 = new MergeSort(testObciazeniowy);
            if (testUtil.isSorted(testObciazeniowy))
                System.out.println("posortowane");

        } catch (Exception e) {
            System.out.println(e);
        }
    }
}
