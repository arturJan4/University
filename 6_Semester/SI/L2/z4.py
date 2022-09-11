# BFS Labyrinth (with extra rules) solver

import itertools
# ULDR - ruchy
# '#' - ściana
# G - punkt docelowy
# S - punkty startowe (wiele)
# B (startowo-docelowe)
# ' ' - pozstałe punkty
from collections import deque
import random

cm_width = 0 # map size
cm_height = 0
cm_map = []
cm_goals = set()
cm_moves = ["U", "L", "D", "R"]

class State:
    def __init__(self, commando=None, steps=""):
        if commando is None:
            commando = set()
        self.commando = commando # list of commando starting points - pairs (i, j)
        self.steps = steps


def input_handler():
    global cm_width, cm_height, cm_map
    """reads into global variables"""
    with open("zad_input.txt", "r") as rd:
        for line in rd:
            cm_map.append(list(line.strip()))

        cm_height = len(cm_map)
        cm_width = len(cm_map[0])


def parse_map():
    initial_state = State()

    for i in range(cm_height):
        for j in range(cm_width):
            if cm_map[i][j] == "S":
                initial_state.commando.add((i, j))
                cm_map[i][j] = ' '
            elif cm_map[i][j] == "B":
                initial_state.commando.add((i, j))
                cm_goals.add((i, j))
                cm_map[i][j] = ' '
            elif cm_map[i][j] == "G":
                cm_goals.add((i, j))
                cm_map[i][j] = ' '

    return initial_state


def make_move(pos, direction):
    """move with one"""
    change_pos = (0, 0)

    if direction == "U":
        change_pos = (-1, 0)
    elif direction == "D":
        change_pos = (1, 0)
    elif direction == "L":
        change_pos = (0, -1)
    elif direction == "R":
        change_pos = (0, 1)

    updated_pos = (pos[0] + change_pos[0], pos[1] + change_pos[1])

    # found wall
    if cm_map[updated_pos[0]][updated_pos[1]] == "#":
        return pos

    return updated_pos


def make_move_all(state, direction):
    nextS = State()
    for com in state.commando:
        nextS.commando.add(make_move(com, direction))

    nextS.steps = state.steps + direction
    return nextS


def is_final_state(state):
    for com in state.commando:
        if com not in cm_goals:
            return False

    return True


MAX_UNCERTAINITY = 4

def reduce_uncertainity(state):
    """reduce possible starting positions"""
    global cm_width, cm_height

    endpts = state.commando
    best_state = state
    ITER = 0

    while len(endpts) > MAX_UNCERTAINITY:
        if ITER > 100:
            endpts = state.commando
            best_state = state
            ITER = 0

        direction = random.choice(cm_moves)
        best_state = make_move_all(best_state, direction)
        endpts = best_state.commando
        ITER += 1

    return best_state

def bfs(state):
    q = deque()
    visited = set()

    q.append(state)

    commando_num = len(state.commando)

    while q:
        curr_state = q.popleft()

        # warunki zadania
        if len(curr_state.steps) > 150:
            continue

        state_var = tuple(curr_state.commando)
        if state_var in visited:
            continue

        if is_final_state(curr_state):
            return curr_state

        visited.add(state_var)

        states = []
        for direction in ["U", "D", "L", "R"]:
            new_state = make_move_all(curr_state, direction)

            states.append(new_state)

            # two commando at same spot (merges)
            if len(new_state.commando) < commando_num:
                commando_num = len(new_state.commando)
                q.clear()
                visited.clear()

        for s in states:
            if len(s.commando) <= commando_num:
                q.append(s)


def solve_maze():
    input_handler()
    init_state = parse_map()

    solution = None
    while True:
        reduced_state = reduce_uncertainity(init_state)
        solution = bfs(reduced_state)
        if solution and len(solution.steps) < 150:
            break

    #print(solution.steps)

    return solution.steps

solution = solve_maze()
#print(solution)
with open("zad_output.txt.txt", "w") as wr:
    print(solution, file=wr)