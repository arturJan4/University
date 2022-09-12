def common_prefix(lista_slow):
    """
    Find longest common prefix for 3 or more strings.

    Idea: Sort lexicographically and compare next three strings' prefixes.

    :param lista_slow: lista_slow of strings
    :return: prefix string
    """
    if len(lista_slow) < 3:
        return None

    lista_slow = [x.lower() for x in lista_slow]  # lowercase
    lista_slow.sort()

    longest = ""
    for i in range(3, len(lista_slow) + 1):
        first, second, third = lista_slow[i-3:i]

        j = 0
        while j < max(len(first), len(second), len(third)):
            if first[j] == second[j] == third[j]:  # three characters match
                j += 1
            else:
                break

        if j > len(longest):  # update longest common prefix
            longest = first[0:j]

    return longest


print(common_prefix(["Cyprian", "cyberotoman", "cynik", "ceniąc", "czule"]))
print(common_prefix(["Cyprian", "cyberotoman", "cynik", "ceniąc", "czule", "cypel", "Cypru"]))
print(common_prefix(["dawka", "dawid", "dawkować", "Cyprian", "cyberotoman", "cynik", "ceniąc", "czule", "cypel", "Cypru"]))
print(common_prefix(["dawka", "Dawid", "Cyprian", "cyberotoman", "dawki", "cynik", "ceniąc", "czule", "dawkować", "cypel", "Cypru"]))
print(common_prefix(["ssss", "ssss", "ssss"]))