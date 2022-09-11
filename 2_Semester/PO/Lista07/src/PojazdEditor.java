import javax.swing.*;
import java.io.File;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class PojazdEditor extends JFrame
{
    private Pojazd m_pojazd;
    private File plik;
    public PojazdEditor(File plik)
    {
        this.plik = plik;
        m_pojazd = new Pojazd();
    }

    private void start()
    {

           setDefaultCloseOperation(EXIT_ON_CLOSE);
           pack();
           setVisible(true);
    }
}
