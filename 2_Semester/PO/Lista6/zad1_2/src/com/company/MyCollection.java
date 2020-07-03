package com.company;

import java.io.*;
class node<T extends Comparable<T>> implements Serializable
{
    private T data;
    public com.company.node<T> next;

    node(T data)
    {
        this.data = data;
        next = null;
    }
    public T getData()
    {
        return data;
    }
    private void readObject(java.io.ObjectInputStream stream) throws IOException, ClassNotFoundException
    {
        stream.defaultReadObject();
    }
    private void writeObject(java.io.ObjectOutputStream stream) throws IOException
    {
        stream.defaultWriteObject();
    }
}

public class MyCollection<T extends Comparable<T>> implements Serializable
{
    //sorted collection
    //lowest element at the beginning
    com.company.node<T> front;
    MyCollection()
    {
        front = null;
    }
    public void push(T element)
    {
        com.company.node<T> newNode = new com.company.node<>(element);
        if(front == null)//empty list(initialize)
        {
            front = newNode;
            return;
        }

        if(front.getData().compareTo(element) > 0)//push at the beginning
        {
            newNode.next = front;
            front = newNode;
            return;
        }

        //push at middle or back
        com.company.node<T> prev = front;
        com.company.node<T> temp = front.next;
        while(!(temp == null) && temp.getData().compareTo(element) < 0)
        {
            prev = temp;
            temp = temp.next;
        }
        prev.next = newNode;
        newNode.next = temp; //could be null for back of the list
    }

    public T pop()
    {
        if(front == null)
        {
            throw new IllegalStateException("list is empty - cannot pop");
        }
        T temp = front.getData();
        front = front.next;

        return temp;
    }

    public void print()
    {
        com.company.node<T> temp = front;
        System.out.print("Printing a list: ");
        while(temp != null)
        {
            System.out.print("["+ temp.getData() + "] ");
            temp = temp.next;
        }
        System.out.println();
    }

    public void printLn()
    {
        com.company.node<T> temp = front;
        System.out.println("Printing a list: ");
        while(temp != null)
        {
            System.out.println("["+ temp.getData() + "] ");
            temp = temp.next;
        }
        System.out.println();
    }

    private void readObject(java.io.ObjectInputStream stream) throws IOException, ClassNotFoundException
    {
        stream.defaultReadObject();
    }
    private void writeObject(java.io.ObjectOutputStream stream) throws IOException
    {
        stream.defaultWriteObject();
    }
}
