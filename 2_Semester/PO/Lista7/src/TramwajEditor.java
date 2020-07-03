import javax.swing.*;
import java.io.File;

public class TramwajEditor extends JFrame
{
    private Tramwaj m_tramwaj;
    private File plik;
    public TramwajEditor(File plik)
    {
        this.plik = plik;
        m_tramwaj = new Tramwaj();
    }

}
