package com.company;

public class Pulkownik extends MilitaryRank
{
    Pulkownik(String imie, String nazwisko)
    {
        super("OR-05", "Pulkownik");
        this.name = imie;
        this.surname = nazwisko;
    }
}
