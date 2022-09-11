public class Samochod extends Pojazd
{
    protected String numerRejestracyjny;
    protected String wlasciciel;
    protected int cena;
    public Samochod(){};
    public Samochod(String nazwa, boolean czyMaKola, int ilePasazerow, int KM,String numerRejestracyjny, String wlasciciel) {
        this.nazwa = nazwa;
        this.czyMaKola = czyMaKola;
        this.ilePasazerow = ilePasazerow;
        this.numerRejestracyjny = numerRejestracyjny;
        this.wlasciciel = wlasciciel;
    }

    @Override
    public String toString() {
        return "Samochod{" +
                "numerRejestracyjny='" + numerRejestracyjny + '\'' +
                ", wlasciciel='" + wlasciciel + '\'' +
                ", cena=" + cena +
                ", nazwa='" + nazwa + '\'' +
                ", czyMaKola=" + czyMaKola +
                ", ilePasazerow=" + ilePasazerow +
                '}';
    }

    public String getNumerRejestracyjny() {
        return numerRejestracyjny;
    }

    public void setNumerRejestracyjny(String numerRejestracyjny) {
        this.numerRejestracyjny = numerRejestracyjny;
    }

    public String getWlasciciel() {
        return wlasciciel;
    }

    public void setWlasciciel(String wlasciciel) {
        this.wlasciciel = wlasciciel;
    }

    public int getCena() {
        return cena;
    }

    public void setCena(int cena) {
        this.cena = cena;
    }
}
