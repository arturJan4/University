package com.company;

public class Kapitan extends MilitaryRank
{
    Kapitan(String imie, String nazwisko)
    {
        super("OF-01", "Kapitan");
        this.name = imie;
        this.surname = nazwisko;
    }
}
