package com.company;

//OR1 OR2 ... -> OF1 OF2 ...
public abstract class MilitaryRank implements Comparable<MilitaryRank>
{
    protected String codeNATO; //key
    protected String rank;
    protected String name;
    protected String surname;

    MilitaryRank(String codeNATO, String rank)
    {
        this.codeNATO = codeNATO;
        this.rank = rank;
        if(codeNATO.length() != 5 || codeNATO.charAt(2) != '-')
            throw new IllegalArgumentException("Zly format kodu NATO");
    }
    @Override
    public int compareTo(MilitaryRank militaryRank) {
        String letterPart = codeNATO.substring(0,2);
        String numberPart = codeNATO.substring(3,5);

        String cmLetterPart = militaryRank.codeNATO.substring(0,2);
        String cmNumberPart = militaryRank.codeNATO.substring(3,5);

        if(letterPart.compareTo(cmLetterPart) == 0)//equal
        {
            if(numberPart.compareTo(cmNumberPart) == 0)//equal
                return 0;
            else if(numberPart.compareTo(cmNumberPart) < 0)
                return -1;
            else
                return 1;
        }
        else if(letterPart.compareTo(cmLetterPart) > 0)
            return -1;
        else
            return 1;
    }

    @Override
    public String toString() {
        return "Dane: " + this.name + " " + this.surname + " stopien: " + this.rank;
    }
}

