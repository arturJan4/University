import javax.swing.*;
import java.io.File;

public class SamochodEditor extends JFrame
{
    private Samochod m_samochod;
    private File plik;
    public SamochodEditor(File plik)
    {
        this.plik = plik;
        m_samochod = new Samochod();
    }
}
