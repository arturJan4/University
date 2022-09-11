import random

# pomysł:
# split po ' '
# funkcja licząca długość słowa (po usunięciu znaków ,.'" itp.)
# usuń zbyt długie słowa według powyższej funkjcji
# policz liczbę słów po usnięciu i zapisz ile trzeba jeszcze usunąć
# wybierz losowe indeksy -> usuń slowa pod tymi indeksami
# zwróć tekst po transformacjach


def dlugosc_slowa(slowo):
    znaki_del = ";:,.!?-+-=<>[](){}\\//@#$%^&*`~"
    znaki_del += '"'

    slowo = slowo.strip(znaki_del)  # delete special chars from left and right side

    return len(slowo)


def uprosc_zdanie(tekst, dl_slowa, liczba_slow):
    # remove words of length > dl_slowa
    tekst = [s for s in tekst.split(" ") if dlugosc_slowa(s) <= dl_slowa]

    # length of text after removing longer words
    pozostalo = len(tekst)

    # delete random sample of excess words
    if pozostalo > liczba_slow:
        do_usuniecia = pozostalo - liczba_slow

        indeksy_del = random.sample(range(0, pozostalo), do_usuniecia)

        tekst = [s for i, s in enumerate(tekst) if (i not in indeksy_del)]

    # return a string
    return ' '.join(s for s in tekst)


# testy

# http://shakespeare.mit.edu/Poetry/sonnet.XIX.html
text = """Devouring Time, blunt thou the lion's paws,
And make the earth devour her own sweet brood;
Pluck the keen teeth from the fierce tiger's jaws,
And burn the long-lived phoenix in her blood;
Make glad and sorry seasons as thou fleets,
And do whate'er thou wilt, swift-footed Time,
To the wide world and all her fading sweets;
But I forbid thee one most heinous crime:
O, carve not with thy hours my love's fair brow,
Nor draw no lines there with thine antique pen;
Him in thy course untainted do allow
For beauty's pattern to succeeding men.
Yet, do thy worst, old Time: despite thy wrong,
My love shall in my verse ever live young.
"""

text2 = "Podział peryklinalny inicjałów wrzecionowatych \
kambium charakteryzuje się ścianą podziałową inicjowaną \
w płaszczyźnie maksymalnej."

print(uprosc_zdanie(text2, 10, 5))

print(dlugosc_slowa("gżegżółka"))
print(dlugosc_slowa("żaba"))
print(dlugosc_slowa("żaba;"))
print(dlugosc_slowa("żaba()"))
print(dlugosc_slowa(",żaba():"))
print(dlugosc_slowa("utf-8:ąężść"))

print(uprosc_zdanie(text, 10, 100))
