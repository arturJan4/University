def is_palindrome(text):
    """
    :param text - can be UTF-8
    :returns True if given text is a palindrome.
    """
    text = text.lower()  # ignore case
    text = ''.join(char for char in text if char.isalnum())  # leave only alphanumeric chars

    return text == text[::-1]


print("Negatives:")
print(is_palindrome("Kobyła miała mały bok."))
print(is_palindrome("Eine güldne, gute Tugend: Lüge!"))

print("Positives:")
print(is_palindrome("Kobyła ma mały bok."))
print(is_palindrome("Eine güldne, gute Tugend: Lüge nie!"))
print(is_palindrome("redivider"))
