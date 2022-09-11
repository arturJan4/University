# storms solver using constraints generated here to solve by prolog

txt = open('zad_input.txt').readlines()
output = open('zad_output.txt', 'w')
# -------------------Helpers-------------------

# variable for row-i, column-j
def B(i, j):
    return 'B_%d_%d' % (i, j)


def domains(Bs):
    return [q + ' in 0..1' for q in Bs]


def get_column(j, row_len):
    return [B(i, j) for i in range(row_len)]


def get_row(i, col_len):
    return [B(i, j) for j in range(col_len)]


# values in B sum to total
def sum(B, total):
    return 'sum([' + ', '.join(B) + '], #=, ' + str(total) + ')'


# -------------------Constraints-------------------
# pretty-print for list of contraints
def print_constraints(Cs, indent, d):
    position = indent
    writeln(indent * ' ', end='')
    for c in Cs:
        writeln(c + ',', end=' ')
        position += len(c)
        if position > d:
            position = indent
            writeln('')
            writeln(indent * ' ', end='')


# number of storms in column sums to given value
def sum_vertical(columns, row_len):
    return [sum(get_column(i, row_len), val) for i, val in enumerate(columns)]


# number of storms in row sums to given value
def sum_horizontal(rows, col_len):
    return [sum(get_row(i, col_len), val) for i, val in enumerate(rows)]


# we can't have pattern (0 1 0) == (A B C)
# having a pixel implies there is at least one surrounding it in both horizontal and vertical direction
# B == 1 --> A + C > 0
def single_vertical(row_len, col_len):
    cs = []
    for j in range(col_len): # pick column
        for i in range(row_len-2):
            a = B(i, j)
            b = B(i+1, j)
            c = B(i+2, j)
            cs.append(b + ' #= 1 #==> ' + a + ' + ' + c + ' #>= 1')
    return cs


def single_horizontal(row_len, col_len):
    cs = []
    for i in range(row_len): # pick column
        for j in range(col_len-2):
            a = B(i, j)
            b = B(i, j+1)
            c = B(i, j+2)
            cs.append(b + ' #= 1 #==> ' + a + ' + ' + c + ' #>= 1')
    return cs


# for 2x2 squares, some of illegal patterns
# 0 1 | 1 0 | 1 1 | A B
# 1 0 | 0 1 | 0 1 | C D
# if we have two in one axis then we also need another axis
# A + D #= 2 <--> B + C #= 2
# this eliminates non-squares and squares with adjacent corners
def square(row_len, col_len):
    cs = []
    for i in range(row_len-1): # pick column
        for j in range(col_len-1):
            a = B(i, j)
            b = B(i, j+1)
            c = B(i+1, j)
            d = B(i+1, j+1)
            cs.append(a + ' + ' + d + ' #= 2 #<==> ' + b + ' + ' + c + ' #= 2')
    return cs


# -------------------Solver-------------------
def writeln(s, end='\n'):
    output.write(s + end)


# solve storms
def storms(rows, cols, triples):
    writeln(':- use_module(library(clpfd)).')

    R = len(rows)
    C = len(cols)

    # domain
    bs = [B(i, j) for i in range(R) for j in range(C)]

    writeln('solve([' + ', '.join(bs) + ']) :- ')

    cs = domains(bs) + sum_vertical(cols, R) + single_vertical(R, C) + sum_horizontal(rows, C) + single_horizontal(R, C) + square(R, C)
    # already filled fields
    for i, j, val in triples:
        cs.append('%s #= %d' % (B(i, j), val))

    print_constraints(cs, 4, 80)

    # print('    [%s] = [1,1,0,1,1,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0],' % (', '.join(bs),)) #only for test 1
    writeln('    labeling([ff], [' + ', '.join(bs) + ']).')
    writeln('')
    writeln(":- tell('prolog_result.txt'), solve(X), write(X), nl, told.")
    #writeln(":- tell('prolog_result.txt'), solve(X), write(X), nl, told.")


rows = list(map(int, txt[0].split()))
cols = list(map(int, txt[1].split()))
triples = []

for i in range(2, len(txt)):
    if txt[i].strip():
        triples.append(list(map(int, txt[i].split())))

storms(rows, cols, triples)

