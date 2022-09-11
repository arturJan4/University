package com.company;

class node<T extends Comparable<T>>//wymuszenie implemntacji Comparable<T>
{
    private T data;
    public node<T> next;

    node(T data)
    {
        this.data = data;
        next = null;
    }
    public T getData()
    {
        return data;
    }
}

public class MyCollection<T extends Comparable<T>>
{
    //sorted collection
    //lowest element at the beginning
    node<T> front;
    MyCollection()
    {
        front = null;
    }
    public void push(T element)
    {
        node<T> newNode = new node<>(element);
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
        node<T> prev = front;
        node<T> temp = front.next;
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
        node<T> temp = front;
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
        node<T> temp = front;
        System.out.println("Printing a list: ");
        while(temp != null)
        {
            System.out.println("["+ temp.getData() + "] ");
            temp = temp.next;
        }
        System.out.println();
    }
}
