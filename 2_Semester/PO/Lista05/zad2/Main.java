/*
    PO lista 5
    Artur Jankowski
    indeks: 317928
    //Nie dzielilem na osobne pliki .java bo tak maly program chyba
     lepiej jest sprawdzac gdy jest w jednym pliku
 */
package com.company;
import java.util.*;//Hashtable

abstract class Wyrazenie
{
    protected Wyrazenie leftChild;
    protected Wyrazenie rightChild;
    public abstract int oblicz();
    public abstract String toString();
}

class Dodaj extends Wyrazenie
{
    Dodaj(Wyrazenie leftChild, Wyrazenie rightChild)
    {
        this.leftChild = leftChild;
        this.rightChild = rightChild;
    }
    public int oblicz()
    {
        return leftChild.oblicz() + rightChild.oblicz();
    }
    @Override
    public String toString() {
        return "(" + leftChild.toString() + " + " + rightChild.toString() + ")";
    }
}

class Odejmij extends Wyrazenie
{
    Odejmij(Wyrazenie leftChild, Wyrazenie rightChild)
    {
        this.leftChild = leftChild;
        this.rightChild = rightChild;
    }
    public int oblicz()
    {
        return leftChild.oblicz() - rightChild.oblicz();
    }
    @Override
    public String toString() {
        return "(" + leftChild.toString() + " - " + rightChild.toString() + ")";
    }
}

class Pomnoz extends Wyrazenie
{
    Pomnoz(Wyrazenie leftChild, Wyrazenie rightChild)
    {
        this.leftChild = leftChild;
        this.rightChild = rightChild;
    }
    public int oblicz()
    {
        return leftChild.oblicz() * rightChild.oblicz();
    }
    @Override
    public String toString() {
        return "(" + leftChild.toString() + " * " + rightChild.toString() + ")";
    }
}

//uwaga: w zadaniu podano by oblicz() zwracalo int, przez co dzielenie działa slabo
class Podziel extends Wyrazenie
{
    Podziel(Wyrazenie leftChild, Wyrazenie rightChild)
    {
        this.leftChild = leftChild;
        this.rightChild = rightChild;
    }
    public int oblicz() throws ArithmeticException
    {
        if(rightChild.oblicz() == 0)
            throw new ArithmeticException("division by zero");
        return leftChild.oblicz() / rightChild.oblicz();
    }
    @Override
    public String toString() {
        return "(" + leftChild.toString() + " / " + rightChild.toString() + ")";
    }
}

class Stala extends Wyrazenie
{
    final private int value;//const
    Stala(int value)
    {
        this.value = value;
    }
    @Override
    public int oblicz() {
        return value;
    }
    @Override
    public String toString()
    {
        return String.valueOf(this.value);
    }
}

class Zmienna extends Wyrazenie
{
    String symbol;//key
    public  static Hashtable<String, Integer> hash = new Hashtable<>();

    Zmienna(String symbol) throws IllegalArgumentException// to allow new Zmienna(x)
    {
        this.symbol = symbol;
        if (hash.containsKey(symbol))
            throw new IllegalArgumentException("duplicate key");
    }
    Zmienna(String symbol,int value) throws IllegalArgumentException
    {
        this.symbol = symbol;
        if (hash.containsKey(symbol))
            throw new IllegalArgumentException("duplicate key");
        else {
            this.symbol = symbol;
            hash.put(this.symbol, value);
        }
    }
    public void setValue(int value)
    {
        hash.put(this.symbol,value);
    }
    @Override
    public int oblicz() throws NoSuchElementException
    {
        if(hash.containsKey(this.symbol))
            return hash.get(this.symbol);
        else
            throw new NoSuchElementException("there is no element of this symbol in the hashtable - set value first");
    }
    @Override
    public String toString()
    {
        return symbol;
    }
}

public class Main {

    public static void main(String[] args) {
        Stala pi = new Stala(3);//engineering approximation
        Zmienna p1 = new Zmienna("p1", 25);
        Zmienna p2 = new Zmienna("p2", 8);

        Wyrazenie wyrazenie = new Podziel(new Stala(4), new Zmienna("x",1));
        Wyrazenie wyrazenie2 = new Dodaj(new Stala(4), new Zmienna("y", 3));
        Wyrazenie wyrazenie3 = new Podziel(p1,p2);
        Wyrazenie wyrazenie4 = new Dodaj(wyrazenie, wyrazenie2);
        Wyrazenie wyrazenie5 = new Dodaj(wyrazenie3, wyrazenie4);

        System.out.println(pi.oblicz());
        System.out.println(wyrazenie3.oblicz());
        System.out.println(wyrazenie5);
        System.out.println(wyrazenie5.oblicz());
	// write your code here
    }
}
