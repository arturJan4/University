from decimal import *


def vat_faktura(lista):
    return sum(lista) * 0.23


def vat_paragon(lista):
    return sum([el * 0.23 for el in lista])


zakupy = [0.2, 0.5, 4.59, 6]
print(vat_faktura(zakupy) == vat_paragon(zakupy))


def convert_to_decimal(lista):
    return [Decimal(el) for el in lista]

def vat_faktura_dec(lista):
    return sum(lista) * Decimal(0.23)


def vat_paragon_dec(lista):
    return sum([el * Decimal(0.23) for el in lista])


zakupy_conv = convert_to_decimal(zakupy)
print(vat_faktura_dec(zakupy_conv) == vat_paragon_dec(zakupy_conv))
