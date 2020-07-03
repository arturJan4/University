/*
    PO
    zad 1 lista 6
    Artur Jankowski
    indeks: 317928
 */
package com.company;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

class internalTests {
    public static void serializationWriteTest_1()
    {
        MyCollection<Integer> test = new MyCollection<>();
        test.push(4);
        test.push(2);
        test.push(4);
        test.push(2);
        test.push(0);

        try (ObjectOutputStream outputStream = new ObjectOutputStream(new FileOutputStream("kolekcje.bin"))) {
            outputStream.writeObject(test);
        } catch (Exception ex) {
            System.out.println(ex);
        }
    }

    public static void serializationWriteTest_2()
    {
        MyCollection<MilitaryRank> test = new MyCollection<>();
        test.push(new Szeregowy("Marek", "Aureliusz"));
        test.push(new General("Oktawian", "August"));
        test.push(new Kapitan("Lucjusz", "Werus"));
        test.push(new Kapral("Kaligula", "Kaligula"));
        test.push(new General("Juliusz", "Cezar"));
        test.push(new Pulkownik("Divus", "Claudius"));

        try (ObjectOutputStream outputStream = new ObjectOutputStream(new FileOutputStream("stopnie.bin"))) {
            outputStream.writeObject(test);
        } catch (Exception ex) {
            System.out.println(ex);
        }
    }

    public static void serializationReadTest_1()
    {
        try (ObjectInputStream inputStream = new ObjectInputStream(new FileInputStream("kolekcje.bin"))) {
            MyCollection<Integer> test = (MyCollection<Integer>) inputStream.readObject();
            test.print();
        } catch (Exception ex) {
            System.out.println(ex);
        }
    }

    public static void serializationReadTest_2()
    {
        try (ObjectInputStream inputStream = new ObjectInputStream(new FileInputStream("stopnie.bin"))) {
            MyCollection<MilitaryRank> test = (MyCollection<MilitaryRank>) inputStream.readObject();
            test.printLn();
        } catch (Exception ex) {
            System.out.println(ex);
        }
    }
}

public class Main {

    public static void main(String[] args)
    {
        internalTests.serializationWriteTest_1();
        internalTests.serializationWriteTest_2();
        internalTests.serializationReadTest_1();
        internalTests.serializationReadTest_2();
    }
}
