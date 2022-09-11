# Sokoban BFS with dead-state detection

from collections import deque

sk_map = []
sk_width = 0
sk_height = 0
sk_pos = (0, 0)  # starting position (x, y), x - height, y - width
sk_boxes = set()
sk_goals = set()
sk_dead = [[]]


class State:
    # need player's position, boxes and current moves list
    def __init__(self, player=(0, 0), boxes=None, steps=""):
        if boxes is None:
            boxes = set()

        self.player = player
        self.boxes = boxes
        self.steps = steps


def input_handler():
    global sk_width, sk_height, sk_dead
    """reads into global variables"""
    with open("zad_input.txt", "r") as rd:
        for line in rd:
            sk_map.append(line.strip())

        sk_width = len(sk_map[0])
        sk_height = len(sk_map)
        sk_dead = [[0]*sk_width for i in range(sk_height)]

def parse_map():
    global sk_height, sk_width, sk_pos, sk_boxes, sk_map, sk_goals

    for i in range(sk_height):
        for j in range(sk_width):
            # goal
            if sk_map[i][j] == "K":
                sk_pos = (i, j)
            elif sk_map[i][j] == "G":
                sk_goals.add((i, j))
            elif sk_map[i][j] == "B":
                sk_boxes.add((i, j))
            elif sk_map[i][j] == "*":
                sk_boxes.add((i, j))
                sk_goals.add((i, j))
            elif sk_map[i][j] == "+":
                sk_pos = (i, j)
                sk_goals.add((i, j))


def mark_dead():
    for i in range(0, sk_height):
        for j in range(0, sk_width):
            if sk_map[i][j] == "W":
                sk_dead[i][j] = 1
                continue

            if sk_dead[i][j] == 1:
                continue

            if (i, j) not in sk_goals:
                borders = [(i + dy, j + dx) for (dy, dx) in [(-1, 0), (0, 1), (1, 0), (0, -1)]]
                # corner
                for k in range(0, 3):
                    dy, dx = borders[k][0], borders[k][1]
                    dy2, dx2 = borders[(k + 1) % 4][0], borders[(k + 1) % 4][1]

                    first = sk_map[dy][dx]
                    second = sk_map[dy2][dx2]

                    # 1. two adjacent field are walls
                    if first == "W" and second == "W":
                        sk_dead[i][j] = 1

                    # 2. three adjacent are walls -> another one is also a wall
                    dy3, dx3 = borders[(k + 2) % 4][0], borders[(k + 2) % 4][1]
                    third = sk_map[dy3][dx3]
                    dy4, dx4 = borders[(k + 3) % 4][0], borders[(k + 3) % 4][1]
                    fourth = sk_map[dy4][dx4]

                    is_dead1 = sk_dead[dy][dx]
                    is_dead2 = sk_dead[dy2][dx2]
                    is_dead3 = sk_dead[dy3][dx3]
                    is_dead4 = sk_dead[dy4][dx4]

                    if (first == "W") and (second == "W") and (third == "W"):
                        sk_dead[dy4][dx4] = 1
                        if j > 1:
                            j -= 1
                        if i > 1:
                            i -= 1

                    # 3. one dead and two opposite walls
                    if (first == "W") and is_dead2 and (third == "W"):
                        sk_dead[i][j] = 1
                        if j > 1:
                            j -= 1
                        if i > 1:
                            i -= 1

                    # 4. two dead and a wall
                    if is_dead1 and is_dead2 and (third == "W") or \
                            is_dead1 and (second == "W") and is_dead3:
                        sk_dead[i][j] = 1
                        if j > 1:
                            j -= 1
                        if i > 1:
                            i -= 1

def make_move(state, direction):
    global sk_dead
    change_pos = (0, 0)

    if direction == "U":
        change_pos = (-1, 0)
    elif direction == "D":
        change_pos = (1, 0)
    elif direction == "L":
        change_pos = (0, -1)
    elif direction == "R":
        change_pos = (0, 1)

    # get position from state
    player_pos = state.player

    updated_pos = (player_pos[0] + change_pos[0], player_pos[1] + change_pos[1])

    # found wall
    if sk_map[updated_pos[0]][updated_pos[1]] == "W":
        return None

    # new position is a box -> push box
    if updated_pos in state.boxes:
        box_pos = (player_pos[0] + 2 * change_pos[0], player_pos[1] + 2 * change_pos[1])

        # pushed box hits a wall
        if sk_map[box_pos[0]][box_pos[1]] == "W":
            return None

        # pushed box into another box
        if box_pos in state.boxes:
            return None

        #if sk_map[box_pos[0]][box_pos[1]] == "W":
        #    return None

        if sk_dead[box_pos[0]][box_pos[1]] == 1:
            return None

        # update box position in boxes list for new state
        new_boxes = state.boxes.copy()
        new_boxes.remove(updated_pos)
        new_boxes.add(box_pos)
        new_str = state.steps + direction

        return State(updated_pos, new_boxes, new_str)

    new_boxes = state.boxes.copy()
    new_str = state.steps + direction
    return State(updated_pos, new_boxes, new_str)


def is_final_state(state):
    # all boxes are in goals positions
    for box in state.boxes:
        if box not in sk_goals:
            return False

    return True


def bfs(state):
    q = deque()
    visited = set()

    q.append(state)
    while q:
        curr_state = q.popleft()
        state_var = (curr_state.player, tuple(curr_state.boxes))
        if state_var in visited:
            continue

        if is_final_state(curr_state):
            return curr_state.steps

        visited.add(state_var)

        for direction in ["U", "D", "L", "R"]:
            #print(curr_state.steps, direction,  end=", ")
            new_state = make_move(curr_state, direction)

            if new_state is not None:
                #print(curr_state.steps, new_state.steps)
                q.append(new_state)


def solve_sokoban():
    input_handler()
    parse_map()
    mark_dead()

    # print('\n'.join(['\t'.join([str(cell) for cell in row]) for row in sk_dead]))

    # print(sk_pos, sk_goals, sk_boxes)
    starter_state = State(sk_pos, sk_boxes, "")

    return bfs(starter_state)


solution = solve_sokoban()
#print(solution)
with open("zad_output.txt.txt", "w") as wr:
    print(solution, file=wr)
