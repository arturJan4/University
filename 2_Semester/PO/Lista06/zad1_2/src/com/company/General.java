package com.company;

public class General extends MilitaryRank
{
    General(String imie, String nazwisko)
    {
        super("OF-09", "General");
        this.name = imie;
        this.surname = nazwisko;
    }
}
