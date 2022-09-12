import itertools

def kompresja(tekst):
    """
    Compresses string by replacing letters with pairs (frequency, letter)
    :param tekst: string to compress
    :return: compressed string
    """
    out = []
    for key, group in itertools.groupby(tekst):
        out.append((len(list(group)), key))
    return out


def dekompresja(test_skompresowany):
    """
    Decompress string compressed with (kompresja) method
    """
    return ''.join([letter * times for (times, letter) in test_skompresowany])


# znaki przestankowe: \n'`!?.,[](){}-":;

# testy

text = """Suuuuper..!!!! ;"""

# http://shakespeare.mit.edu/Poetry/sonnet.XIX.html
text2 = """Devouring Time, blunt thou the lion's paws,
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

skompresowany_1 = kompresja(text)
skompresowany_2 = kompresja(text2)

print(skompresowany_1)
print(skompresowany_2)

print(dekompresja(skompresowany_1))
print(dekompresja(skompresowany_2))