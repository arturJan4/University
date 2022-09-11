# text reconstruction

words = set()  # set of words
world_len_sq = dict()
world_len_max = 0

def splitter(text):
    DP_len = [0 for i in range(len(text) + 1)]
    DP_txt = ['' for i in range(len(text) + 1)]

    for i in range(1, len(text) + 1):
        if text[:i] in words:  # i-letter prefix
            DP_len[i] = i**2
            DP_txt[i] = text[:i]
        else:
            cond = max(i - world_len_max, -1)

            for j in range(i-1, cond, -1):
                if text[j:i] in words and DP_len[i] < DP_len[j] + (i-j+1)**2:
                    DP_len[i] = DP_len[j] + (i-j+1)**2
                    DP_txt[i] = DP_txt[j] + ' ' + text[j:i]

    return DP_txt[len(text)]


# Take string input and pass to opt_bits"
def input_handler():
    global world_len_sq, words, world_len_max

    with open("words_for_ai1.txt", "r") as file:
        for word in file:
            word = word.strip()
            words.add(word)
    world_len_sq = {word: len(word) ** 2 for word in words}
    world_len_max = max(len(word) for word in words)

    with open("zad2_input.txt", "r") as rd:
        with open("zad2_output.txt", "w") as wr:
            for line in rd:
                solution = splitter(line.strip())
                print(solution, file=wr)

input_handler()

# tests
# print(splitter("księgapierwsza"))
# print(splitter("tamatematykapustkinieznosi"))
