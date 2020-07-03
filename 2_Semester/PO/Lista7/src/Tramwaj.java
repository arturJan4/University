public class Tramwaj extends Pojazd
{
    protected int numerLinii;
    protected String miasto;
    protected long liczbaWykolejenNaMiesiac;
    public Tramwaj(){};
    public Tramwaj(String nazwa, int ilePasazerow,
                   int numerLinii, String miasto, int liczbaWykolejenNaMiesiac) {
        this.nazwa = nazwa;
        this.czyMaKola = true;
        this.ilePasazerow = ilePasazerow;
        this.numerLinii = numerLinii;
        this.miasto = miasto;
        this.liczbaWykolejenNaMiesiac = liczbaWykolejenNaMiesiac;
        //if(liczbaWykolejenNaMiesiac < 1)throw new IllegalStateException();
    }

    @Override
    public String toString() {
        return "Tramwaj{" +
                "numerLinii=" + numerLinii +
                ", miasto='" + miasto + '\'' +
                ", liczbaWykolejenNaMiesiac=" + liczbaWykolejenNaMiesiac +
                ", nazwa='" + nazwa + '\'' +
                ", czyMaKola=" + czyMaKola +
                ", ilePasazerow=" + ilePasazerow +
                '}';
    }

    public int getNumerLinii() {
        return numerLinii;
    }

    public void setNumerLinii(int numerLinii) {
        this.numerLinii = numerLinii;
    }

    public String getMiasto() {
        return miasto;
    }

    public void setMiasto(String miasto) {
        this.miasto = miasto;
    }

    public long getLiczbaWykolejenNaMiesiac() {
        return liczbaWykolejenNaMiesiac;
    }

    public void setLiczbaWykolejenNaMiesiac(long liczbaWykolejenNaMiesiac) {
        this.liczbaWykolejenNaMiesiac = liczbaWykolejenNaMiesiac;
    }
}
