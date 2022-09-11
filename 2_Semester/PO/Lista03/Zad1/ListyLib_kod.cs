/*
 * PO lista 3, zad 1 
 * Artur Jankowski
 * indeks : 317928
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ListyLib
{
    namespace Listy
    {
        public class Lista<T>
        {
            Node<T> firstElement;
            Node<T> lastElement;
            protected int size;

            public void addBack(T data)
            {
                Node<T> newNode = new Node<T>(data);
                if (size == 0)
                {
                    firstElement = newNode;
                    lastElement = newNode;
                }
                else
                {
                    newNode.setPrev(lastElement);
                    lastElement.setNext(newNode);
                    lastElement = newNode;
                }
                size++;
            }

            public void addFront(T data)
            {
                Node<T> newNode = new Node<T>(data);
                if (size == 0)
                {
                    firstElement = newNode;
                    lastElement = newNode;
                }
                else
                {
                    newNode.setNext(firstElement);
                    firstElement.setPrev(newNode);
                }
                firstElement = newNode;
                size++;
            }

            public T popBack()
            {
                if (size == 0 || lastElement == null)
                    throw new System.InvalidOperationException("lista jest pusta");

                T value = lastElement.getData();
                if (lastElement.getPrev() == null)//size == 1
                {
                    lastElement = null;
                    firstElement = null;
                }
                else
                {
                    lastElement.getPrev().setNext(null);
                    lastElement = lastElement.getPrev();
                }

                --size;
                return value;
            }

            public T popFront()
            {
                if (size == 0 || firstElement == null)
                    throw new System.InvalidOperationException("lista jest pusta");

                T value = firstElement.getData();
                if (firstElement.getNext() == null)//size == 1
                {
                    lastElement = null;
                    firstElement = null;
                }
                else
                {
                    firstElement.getNext().setPrev(null);
                    firstElement = firstElement.getNext();
                }

                --size;
                return value;
            }

            public bool isEmpty()
            {
                if (this.size == 0)
                    return true;
                return false;
            }

            public int getSize()
            {
                return this.getSize();
            }
            public void printList()
            {
                Node<T> temp = firstElement;
                if (temp == null)
                    return;

                while (temp != lastElement)
                {
                    Console.WriteLine(temp.getData());
                    temp = temp.getNext();
                }
                if (lastElement != null)
                    Console.WriteLine(lastElement.getData());
            }
        }
        internal class Node<T>//lista dwukierunkowa
        {
            protected T data;
            Node<T> prev;
            Node<T> next;

            public Node(T i)
            {
                data = i;
                next = null;
                prev = null;
            }

            public T getData()
            {
                return data;
            }
            public Node<T> getPrev()
            {
                return prev;
            }
            public Node<T> getNext()
            {
                return next;
            }
            public void setData(T newData)
            {
                this.data = newData;
            }
            public void setNext(Node<T> newNext)
            {
                this.next = newNext;
            }
            public void setPrev(Node<T> newPrev)
            {
                this.prev = newPrev;
            }

        }
    }
}
