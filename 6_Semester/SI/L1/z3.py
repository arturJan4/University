# extra-rules poker game win-chance using python features

import random
# porównujemy układy, jeśli obaj mają ten sam układ -> Figurant zawsze wygra

kolory = ['S', 'H', 'D', 'C']  # spades, hearts, diamonds, clubs
figury = ['A', 'K', 'Q', 'J']
blotki = [str(val) for val in range(2, 11)]

# dla porządkowania przy sortowaniu
blotki_dict = {i: int(i) for i in blotki}
wartosc_dict = {'A': 14, 'K': 13, 'Q': 12, 'J': 11}
wartosc_dict.update(blotki_dict)

karty_figuranta = [(kolor, figura) for kolor in kolory for figura in figury]
karty_blotkarza = [(kolor, blotka) for kolor in kolory for blotka in blotki]

def matching_cards(hand, n):
    """check if there are exactly n cards of same value in hand, return how many such matches there are"""
    suma = [0 for i in range(0, 15)]
    for card in hand:
        suma[wartosc_dict[card[1]]] += 1

    return suma.count(n)

def in_order(hand):
    """returns how many cards are in order"""
    #print(hand)
    sorted_hand = sorted(hand, key=lambda x: wartosc_dict[x[1]])

    ord = 1
    max_ord = 1
    for i in range(1, len(hand)):
        if sorted_hand[i][1] == sorted_hand[i - 1][1]:
            continue
        elif wartosc_dict[sorted_hand[i][1]] == wartosc_dict[sorted_hand[i - 1][1]] + 1:
            ord += 1
        else:
           max_ord = max(ord, max_ord)
           ord = 1

    return max(ord, max_ord)

# poker królewski nie jest tu możliwy
def poker(hand):
    return kolor(hand) and strit(hand)

def kareta(hand):
    return matching_cards(hand, 4) == 1

def ful(hand):
    return trojka(hand) and para(hand)

def kolor(hand):
    kolory = [card[0] for card in hand]

    return kolory.count(kolory[0]) == len(kolory)

def strit(hand):
    """can't be A-2-3-4-5 because of task constraints"""
    return in_order(hand) == 5

def trojka(hand):
    return matching_cards(hand, 3) == 1

def dwie_pary(hand):
    return matching_cards(hand, 2) == 2

def para(hand):
    return matching_cards(hand, 2) == 1

# wysoka karta -> nie trzeba (bo figurant zawsze ma większą)

def prawdopodobienstwo_Blotkarza(talia_blotkarza, GRY):
    """jak czesto wygrywa Blotkarz?"""
    wygrane = 0
    uklady = [poker, kareta, ful, kolor, strit, trojka, dwie_pary, para]

    for i in range(0, GRY):
        blotkarz_hand = random.sample(talia_blotkarza, 5)
        figurant_hand = random.sample(karty_figuranta, 5)

        for uklad in uklady:
            # figurant ma mocniejszy lub taki sam uklad
            if uklad(figurant_hand):
                break

            # blotkarz ma lepszy uklad
            if uklad(blotkarz_hand):
                wygrane += 1
                break

    return wygrane / GRY


# print(karty_figuranta)

assert in_order([('S', val) for val in ['A', 'K', 'Q', 'J', '7']]) == 4
assert in_order([('S', val) for val in ['A', 'Q', 'Q', 'K', '7']]) == 3
assert in_order([('S', val) for val in ['2', '3', '4', '5', '6']]) == 5
assert in_order([('S', val) for val in ['2', '4', '6', '8', '10']]) == 1
assert para([('S', val) for val in ['2', '2', '6', '8', '10']]) is True
assert trojka([('S', val) for val in ['2', '2', '6', '2', '10']]) is True
assert kolor([('S', val) for val in ['2', '2', '6', '2', '10']]) is True
assert poker([('S', val) for val in ['2', '3', '4', '5', '6']]) is True


def znajdz_talie(GRY, per_rozmiar, repeat):
    najlepsza_talia = karty_blotkarza
    najlepsze_pdp_list = [prawdopodobienstwo_Blotkarza(najlepsza_talia, GRY) for i in range(repeat)]
    najlepsze_pdp = sum(najlepsze_pdp_list) / float(len(najlepsze_pdp_list))

    for rozmiar in (5, 36):
        for i in range(per_rozmiar):
            talia = random.sample(karty_blotkarza, rozmiar)

            nowe_pdp_list = [prawdopodobienstwo_Blotkarza(talia, GRY) for i in range(repeat)]
            nowe_pdp = sum(nowe_pdp_list) / float(len(nowe_pdp_list))

            if nowe_pdp > najlepsze_pdp:
                najlepsze_pdp = nowe_pdp
                najlepsza_talia = talia

    return najlepsze_pdp * 100, najlepsza_talia


def znajdz_talie_50(GRY, per_rozmiar, repeat):
    najlepsza_talia = karty_blotkarza
    najlepsze_pdp_list = [prawdopodobienstwo_Blotkarza(najlepsza_talia, GRY) for i in range(repeat)]
    najlepsze_pdp = sum(najlepsze_pdp_list) / float(len(najlepsze_pdp_list))

    for rozmiar in (5, 36):
        for i in range(per_rozmiar):
            talia = random.sample(karty_blotkarza, rozmiar)

            nowe_pdp_list = [prawdopodobienstwo_Blotkarza(talia, GRY) for i in range(repeat)]
            nowe_pdp = sum(nowe_pdp_list) / float(len(nowe_pdp_list))

            if nowe_pdp > 0.50:
                najlepsze_pdp = nowe_pdp
                najlepsza_talia = talia

    return najlepsze_pdp * 100, najlepsza_talia

# print(znajdz_talie(100, 1000, 10))
# print(znajdz_talie_50(100, 1000, 10))
# pdp, talia50 = znajdz_talie_50(100, 10000, 1)
# print(prawdopodobienstwo_Blotkarza(talia50, 100000))
# print(talia50)

# ~8.5% dla całej talii błotkarza
print("pdp. wygranej Błotkarza:", prawdopodobienstwo_Blotkarza(karty_blotkarza, 100000) * 100, "%")

# kareta zawsze
# talia_1 = [(kolor, '10') for kolor in kolory] + [('S', '9')]
# print(prawdopodobienstwo_Blotkarza(talia_1, 100000))

# poker -> 1.0
# talia_poker = [('S', str(val)) for val in range(2, 7)]
# print(prawdopodobienstwo_Blotkarza(talia_poker, 100000))

# ok. ~92.5% dla jednego koloru -> 9 kart
talia_kolor = [('S', str(val)) for val in range(2, 11)] # kolor
print(prawdopodobienstwo_Blotkarza(talia_kolor, 100000))

# ok. 93% dla 2 i 3, jak dodaję 4 to spada do 56% -> 8/12 kart
talia_mix = [(kolor, str(val)) for kolor in kolory for val in range(2, 4)]
print(prawdopodobienstwo_Blotkarza(talia_mix, 100000))

talia_mix = [(kolor, str(val)) for kolor in kolory for val in range(2, 5)]  # + [('S', '5')]
print(prawdopodobienstwo_Blotkarza(talia_mix, 100000))
# 20% -> 10 kart
# talia_strit = [('S', str(val)) for val in range(2, 7)] + [('D', str(val)) for val in range(2, 7)]
# print(prawdopodobienstwo_Blotkarza(talia_strit, 100000))

# czyli ten mix daje powyżej 50% a ma 12 kart