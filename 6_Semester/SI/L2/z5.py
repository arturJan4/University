# Ex.4 but with A* instead of BFS

import itertools
# ULDR - ruchy
# '#' - ściana
# G - punkt docelowy
# S - punkty startowe (wiele)
# B (startowo-docelowe)
# ' ' - pozstałe punkty
from collections import deque
import heapq as hq
import random
import math

cm_width = 0 # map size
cm_height = 0
cm_map = []
cm_goals = set()
cm_moves = ["U", "L", "D", "R"]
cm_dist = []

class State:
    def __init__(self, commando=None, steps=""):
        if commando is None:
            commando = set()
        self.commando = commando # list of commando starting points - pairs (i, j)
        self.steps = steps

    def __lt__(self, other):
        return len(self.steps) < len(other.steps)


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

def dist_ar(x, y, x2, y2):
    return math.sqrt((x-x2) * (x-x2) + (y-y2) * (y-y2))

def init_dist():
    global cm_map, cm_dist, cm_height, cm_width, cm_goals

    # find distance from position to closest goal
    def pre(pos):
        q = []
        visited = set()
        visited.add(pos)

        hq.heappush(q, (0, pos))
        while q:
            dist, curr_pos = hq.heappop(q)
            x, y = curr_pos[0], curr_pos[1]

            if (x, y) in cm_goals:
                return dist

            neighbours = [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)]

            for pos in neighbours:
                if pos not in visited and cm_map[pos[0]][pos[1]] != '#':
                    visited.add(pos)
                    hq.heappush(q, (dist + 1, pos))

    cm_dist = cm_map.copy()

    for i in range(cm_height):
        for j in range(cm_width):
            if cm_dist[i][j] == "#":
                continue

            cm_dist[i][j] = pre((i, j))



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

def A_star(state):
    def h(state):
        return len(state.steps) + max(cm_dist[x][y] for (x, y) in state.commando)

    q = []
    hq.heappush(q, (h(state), [state]))
    visited = set()
    ITER = 0

    while q:
        ITER += 1
        if ITER > 1000000:
            return None

        _, state_list = hq.heappop(q)
        curr_state = state_list[0]

        if len(curr_state.steps) > 150:
            continue

        if tuple(curr_state.commando) in visited:
            continue
        visited.add(tuple(curr_state.commando))

        if is_final_state(curr_state):
            return curr_state.steps

        for r in cm_moves:
            ns = make_move_all(curr_state, r)
            calc_h = h(ns)
            hq.heappush(q, (calc_h, [ns]))


def solve_maze():
    input_handler()
    init_state = parse_map()
    init_dist()

    return A_star(init_state)

solution = solve_maze()
#print(solution)
with open("zad_output.txt.txt", "w") as wr:
    print(solution, file=wr)