import javax.swing.*;
import java.io.File;

public class Main {
    public static void main(String[] args) {
        /*
        if(args.length != 2)
        {
            System.out.println("Podaj jako arugemnty wywolania programu nazwe pliku + nazwe klasy");
            return;
        }*/
        String path = args[0];
        String nazwaKlasy = "Pojazd";
        JFrame newFrame = new JFrame("Edytor pojazdu");

        if (nazwaKlasy.equals("Pojazd"))
            newFrame = new PojazdEditor(new File(path));
        if (nazwaKlasy.equals("Samochod"))
            newFrame = new SamochodEditor(new File(path));
        else if (nazwaKlasy.equals("Tramwaj"))
            newFrame = new TramwajEditor(new File(path));
        else
        {
            System.out.println("Mozliwe klasy: to 'Pojazd' 'Samochod' i 'Tramwaj'");
            return;
        }

    }
}
