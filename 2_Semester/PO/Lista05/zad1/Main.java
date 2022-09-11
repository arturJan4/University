/*
    PO
    zad 1 lista 5
    Artur Jankowski
    indeks: 317928
 */
package com.company;

class internalTests
{
    public static void testListInteger()
    {
        MyCollection<Integer> test = new MyCollection<>();
        test.push(3);
        test.push(2);
        test.push(1);
        test.push(4);
        test.push(2);
        test.print();
        System.out.println(test.pop());
        test.print();
        test.pop();
        test.pop();
        test.pop();
        test.pop();
        test.print();
        //test.pop(); //exception
    }

    public static void testListString()
    {
        MyCollection<String> test = new MyCollection<>();
        test.push("42");
        test.push("the");
        test.push("answer");
        test.print();

    }

    public static void testPrintMilitary()
    {
        Szeregowy Dawid = new Szeregowy("Dawid", "Iksinski");
        System.out.println(Dawid);
        Kapitan Wzorcowy = new Kapitan("Andrzej", "Wzorcowy");
        System.out.println(Wzorcowy);
    }

    public static void testListMilitary()
    {
        MyCollection<MilitaryRank> test = new MyCollection<>();
        test.push(new Szeregowy("Marek", "Aureliusz"));
        test.push(new General("Oktawian", "August"));
        test.push(new Kapitan("Lucjusz", "Werus"));
        test.push(new Kapral("Kaligula", "Kaligula"));
        test.push(new General("Juliusz", "Cezar"));
        test.push(new Pulkownik("Divus","Claudius"));
        test.printLn();
    }
}

public class Main {

    public static void main(String[] args) {
       // internalTests.testListInteger();
       // internalTests.testListString();
        // internalTests.testPrintMilitary();
        internalTests.testListMilitary();
    }
}
