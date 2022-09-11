import java.io.Serializable;

public class Pojazd implements Serializable
{
   protected String nazwa;
   protected boolean czyMaKola;
   protected int ilePasazerow;

    public Pojazd(String nazwa, boolean czyMaKola, int ilePasazerow) {
        this.nazwa = nazwa;
        this.czyMaKola = czyMaKola;
        this.ilePasazerow = ilePasazerow;
    }

    public Pojazd()
    {
    }

    @Override
    public String toString() {
        return "Pojazd{" +
                "nazwa='" + nazwa + '\'' +
                ", czyMaKola=" + czyMaKola +
                ", ilePasazerow=" + ilePasazerow +
                '}';
    }

    public String getNazwa() {
        return nazwa;
    }

    public void setNazwa(String nazwa) {
        this.nazwa = nazwa;
    }

    public int getIlePasazerow() {
        return ilePasazerow;
    }

}
