/*
 * PO lista 3, zad 2 
 * Artur Jankowski
 * indeks : 317928
 */
using System;

namespace MyDictionary
{
    internal class Node<K, V>//lista dwukierunkowa par
    {
        protected K key;
        protected V value;
        Node<K, V> prev;
        Node<K, V> next;

        public Node(K key, V value)
        {
            this.key = key;
            this.value = value;
            next = null;
            prev = null;
        }
        public K getKey()
        {
            return key;
        }
        public V getValue()
        {
            return value;
        }
        public Node<K, V> getPrev()
        {
            return prev;
        }
        public Node<K, V> getNext()
        {
            return next;
        }
        public void setKey(K newKey)
        {
            this.key = newKey;
        }
        public void setValue(V newValue)
        {
            this.value = newValue;
        }
        public void setNext(Node<K, V> newNext)
        {
            this.next = newNext;
        }
        public void setPrev(Node<K, V> newPrev)
        {
            this.prev = newPrev;
        }

    }
    public class Slownik<K, V>
    {
        private int size;
        Node<K, V> pairs;//points to first element, key is unique

        public Slownik()
        {
            this.size = 0;
            pairs = null;
        }
        public void insert(K key, V value)
        {
            if (keyExists(key))
            {
                throw new System.InvalidOperationException("key must be unique!");
            }
            Node<K, V> newElement = new Node<K, V>(key, value);
            if (pairs == null)
            {
                pairs = newElement;
            }
            else
            {
                pairs.setPrev(newElement);
                newElement.setNext(pairs);
                pairs = newElement;
            }
            ++size;
        }
        public V searchValue(K key)
        {
            Node<K, V> temp = getNodeByKey(key);
            if (temp != null)
            {
                return temp.getValue();
            }

            throw new System.IndexOutOfRangeException("such key doesn't exsist");
        }
        public void delete(K key)
        {
            Node<K, V> temp = getNodeByKey(key);
            if (temp == null)
            {
                throw new IndexOutOfRangeException("dictionary is empty or such key does not exist");
            }
            else if (size == 1)
            {
                pairs = null;
            }
            else if (temp.getPrev() == null)//first element
            {
                temp.getNext().setPrev(null);
                pairs = temp.getNext();
            }
            else if (temp.getNext() == null)//last element
            {
                temp.getPrev().setNext(null);
            }
            else//middle element
            {
                temp.getPrev().setNext(temp.getNext());
                temp.getNext().setPrev(temp.getPrev());
            }

            --size;
        }
        public void print()
        {
            Node<K, V> temp = pairs;
            while (temp != null)
            {
                Console.Write("<{0},{1}> ", temp.getKey(), temp.getValue());
                temp = temp.getNext();
            }
            Console.WriteLine();
        }
        public V this[K key]//[] overload
        {
            get { return searchValue(key); }
            set { this.insert(key, value); }
        }
        private Node<K, V> getNodeByKey(K key)
        {
            Node<K, V> temp = pairs;
            while (temp != null)
            {
                if (temp.getKey().Equals(key))
                {
                    return temp;
                }
                temp = temp.getNext();
            }
            return null;
        }
        private bool keyExists(K key)
        {
            if (getNodeByKey(key) != null)
                return true;
            return false;
        }
    }
}
