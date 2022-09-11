# Jungle/Animal chess/Dou Shou Qi agent

import numpy as np
from enum import Enum
import random
import copy
import math

# TODO:
# implement board
# implement drawing
# implement rules (game API)
# implement agent
# 3. implement agent that beats previous
# 4. test jungle with the assigned version

class Animal(Enum):
    R = 1 # rat
    C = 2 # cat
    D = 3 # dog
    W = 4 # wolf
    J = 5 # panther?
    T = 6 # tiger
    L = 7 # lion
    E = 8 # elephant

def empty_copy(obj):
    class Empty(obj.__class__):
        def __init__(self):
            pass

    newcopy = Empty()
    newcopy.__class__ = obj.__class__
    return newcopy

class Board:
    DIRS = [(0, 1), (1, 0), (-1, 0), (0, -1)]
    HEIGHT = 9
    WIDTH = 7
    dens = [(8, 3), (0, 3)] # (0 is white-bottom, 1 is black-top)
    traps = {(0, 2), (0, 4), (1, 3), (8, 2), (8, 4), (7, 3)}
    lakes = {(y, x) for x in [1, 2, 4, 5] for y in [3, 4, 5]}
    pieces = {0: {}, 1: {}}  # (0 - white)
    no_action = 0
    turn = 0  # white starts

    def __init__(self):
        matrixl = self.init_board()
        self.matrix = np.array(matrixl, dtype=object)
        self.no_action = 0 # moves without taking
        self.turn = 0
        return

    def __copy__(self):
        # init overhead
        copied = empty_copy(self)
        copied.matrix = copy.deepcopy(self.matrix)
        copied.dens = [(8, 3), (0, 3)]  # (0 is white-bottom, 1 is black-top)
        copied.traps = {(0, 2), (0, 4), (1, 3), (8, 2), (8, 4), (7, 3)}
        copied.lakes = {(y, x) for x in [1, 2, 4, 5] for y in [3, 4, 5]}
        copied.no_action = self.no_action
        copied.turn = self.turn
        copied.pieces = copy.deepcopy(self.pieces)

        return copied

    def copy_move(self, move):
        board_n = copy.copy(self)
        board_n.make_move(move)

        return board_n

    def init_board(self):
        starting = """
        L.#*#.T
        .D.#.C.
        R.J.W.E
        .~~.~~.
        .~~.~~.
        .~~.~~.
        e.w.j.r
        .c.#.d.
        t.#*#.l
        """

        lines = [line.strip() for line in starting.split('\n') if line.strip() != '']
        player = 1
        matrixl = []
        for y, line in enumerate(lines):
            if y > 4:
                player = 0
            row = [None for _ in range(self.WIDTH)]
            for x, char in enumerate(line):
                if char == '.':
                    continue
                elif char == '#':
                    # self.traps.add((y, x))
                    continue
                elif char == '*':
                    # self.dens.append((y, x))
                    continue
                elif char == '~':
                    # self.lakes.add((y, x))
                    continue
                else:
                    val = Animal[char.upper()].value
                    self.pieces[player][val] = (y, x)
                    row[x] = (player, val)
            matrixl.append(copy.copy(row))

        return matrixl

    def print(self):
        # print(self.pieces)
        for y in range(Board.HEIGHT):
            row_str = ""
            for x in range(0, Board.WIDTH):
                if self.matrix[y][x] is not None:
                    player = self.matrix[y][x][0]
                    if player == 0:
                        row_str += Animal(self.matrix[y][x][1]).name.lower()
                    else:
                        row_str += Animal(self.matrix[y][x][1]).name
                elif (y, x) in self.dens:
                    row_str += '*'
                elif (y, x) in self.traps:
                    row_str += '#'
                elif (y, x) in self.lakes:
                    row_str += '~'
                else:
                    row_str += '.'

            print(row_str)


    # can player from pos beat a piece on to_pos
    def can_beat(self, from_pos, to_pos):
        fy, fx = from_pos
        ty, tx = to_pos

        f_player, f_val = self.matrix[fy][fx]
        t_player, t_val = self.matrix[ty][tx]

        f_name = Animal(f_val).name
        t_name = Animal(t_val).name

        if f_player == t_player:  # own piece
            return False

        if from_pos in self.lakes:  # is rat
            if to_pos in self.lakes:  # 2 rats
                return True
            else:
                return False  # taking from lake is illegal

        # piece in a trap can be taken by anything
        if to_pos in Board.traps:
            return True

        # elephants are scared of rats regardless the value
        if f_name == 'R' and t_name == 'E':
            return True
        elif f_name == 'E' and t_name == 'R':
            return False

        # just compare values
        return f_val >= t_val

    def all_possible_moves(self, player=0):
        moves = []
        # print(f"pieces {self.pieces[player]}")
        for val, pos in self.pieces[player].items():
            name = Animal(val).name
            y, x = pos

            for curr_dir in self.DIRS:
                dy, dx = curr_dir
                uy = y + dy  # updated y
                ux = x + dx

                # out of bounds
                if (ux < 0) or (ux >= self.WIDTH):
                    continue

                if (uy < 0) or (uy >= self.HEIGHT):
                    continue

                # can't enter own den
                if self.dens[player] == (uy, ux):
                    continue

                # only rat can enter lake
                # tiger and panther will jump over if rat is not blocking
                if (uy, ux) in self.lakes:
                    if Animal[name] not in ['R', 'T', 'L']:
                        continue

                    if Animal[name] == 'R':
                        # check if there is rat already there
                        if self.matrix[uy][ux] is not None:
                            if not self.can_beat((y, x), (uy, ux)):
                                continue
                    else: # T or L, check if rat blocks
                        is_blocking = False
                        while (uy, ux) in self.lakes:
                            if self.matrix[uy][ux] is not None:
                                is_blocking = True
                                break
                            uy += dy  # updated y
                            ux += dx

                        if is_blocking:
                            continue

                # check if on the other side is a piece that can be taken
                if self.matrix[uy][ux] is not None:
                    if not self.can_beat((y, x), (uy, ux)):
                        continue

                moves.append(((y, x), (uy, ux)))

        return moves

    def make_move(self, move):
        from_pos, to_pos = move

        fy, fx = from_pos
        ty, tx = to_pos
        # print(f"move {move}")

        f_player, f_val = self.matrix[fy][fx]

        if self.matrix[ty][tx] is None:
            self.no_action += 1
        else:
            self.no_action = 0
            t_player, t_val = self.matrix[ty][tx]
            del self.pieces[t_player][t_val]  # delete taken piece

        self.matrix[fy][fx] = None  # remove a piece
        # print(f"before {np.matrix(self.matrix)}")
        self.matrix[ty][tx] = (self.turn, f_val)  # add a piece
        # print(f"after {np.matrix(self.matrix)})")
        # del self.pieces[f_player][f_val]  # delete from-piece
        self.pieces[f_player][f_val] = (ty, tx)  # update dict

        self.turn = 1 - self.turn

    def random_move(self):
        moves = self.all_possible_moves(self.turn)

        if moves:
            return random.choice(moves)

        return None

    # return True if game ends and winner as second argument
    # player is the one who wants to make a move now
    def final_pos(self, player):
        for i, den in enumerate(self.dens):
            y, x = den
            # 1-i player is in the den of player i-th
            if self.matrix[y][x] is not None:
                return True, 1-i

        if self.no_action >= 30:
            # for every piece going from highest check if opponent has it
            for i in range(8, 0, -1):
                p_has = i in self.pieces[player]
                opp_has = i in self.pieces[1-player]

                if p_has and opp_has:
                    continue

                if p_has:
                    return True, player

                if opp_has:
                    return True, 1 - player

            return True, 1  # second player wins for draw

        # one of the players has no pieces
        sums = {0: 0, 1: 0}
        for y in range(self.HEIGHT):
            for x in range(self.WIDTH):
                if self.matrix[y][x] is None:
                    continue

                player, val = self.matrix[y][x]
                sums[player] += 1

        # print(sums)
        if sums[0] == 0:
            return True, 1

        if sums[1] == 0:
            return True, 0

        return False, None

    def random_agent(self):
        move = self.random_move()

        return move

    def agent_simulate(self):
        # simulate random game and check if it ends with player color winning
        def simulate(board, agent_color, n=3):
            global steps
            wins = 0

            # repeat n times
            for i in range(n):
                new_b = copy.copy(board)  # copy board
                result = None
                while result is None:
                    is_end, result = new_b.final_pos(new_b.turn)

                    #print(new_b.matrix)
                    #print("===================")

                    if is_end:
                        if result == agent_color:
                            wins += 1
                            continue
                        else:
                            wins -= 1
                            continue

                    move = new_b.random_move()
                    if move is None:
                        print("move is none")
                        return

                    new_b.make_move(move)
                    steps += 1

            return wins

        agent_color = self.turn
        all_moves = self.all_possible_moves(agent_color)
        scores = dict()

        for move in all_moves:
            board_moved = self.copy_move(move)
            scores[move] = simulate(board_moved, agent_color, 3)

        # print(scores)
        sorted_moves = [m for m, heu in sorted(scores.items(), key=lambda x: x[1], reverse=True)]

        # print(sorted_moves)
        return sorted_moves[0]

    def heu(self):
        """take into consideration sum of pieces and manhattan distance of each to opponent's nest"""
        def manhattan_dist(pos0, pos1):
            y0, x0 = pos0
            y1, x1 = pos1
            return abs(x0-x1) + abs(y0-y1)

        sums = {0: 0, 1: 0}
        dists = {0: 0, 1: 0}
        for i in [0, 1]:
            for piece in self.pieces[i].items():
                val, pos = piece
                sums[i] += val
                if val == 1:
                    dists[i] += (1/manhattan_dist(pos, self.dens[1-i])) * 5
                else:
                    dists[i] += (1 / manhattan_dist(pos, self.dens[1 - i]))

        # 0 is maximizing

        return (sums[0] - sums[1]) + (dists[0] - dists[1]) * 50

    def alpha_beta(self, depth):
        def minimax(board, depth, maximazing_player, player, alpha, beta):
            final, winner = board.final_pos(player)
            # if final:
            #     if player == 0:
            #         return 100
            #     else:
            #         return -100

            if depth == 0 or final:
                if final:
                    if winner == 0:
                        return 10000
                    else:
                        return -10000
                return board.heu()

            moves = board.all_possible_moves(player)
            if maximazing_player:  # is white (0)
                max_eval = -math.inf
                for move in moves:
                    evalt = minimax(board.copy_move(move), depth - 1, False, 1 - player, alpha, beta)
                    max_eval = max(max_eval, evalt)
                    alpha = max(alpha, evalt)
                    if beta <= alpha:
                        break
                return max_eval
            else:
                min_eval = math.inf
                for move in moves:
                    evalt = minimax(board.copy_move(move), depth - 1, True, 1 - player, alpha, beta)
                    min_eval = min(min_eval, evalt)
                    beta = min(beta, evalt)
                    if beta <= alpha:
                        break
                return min_eval

        ms = self.all_possible_moves(self.turn)
        if ms:
            if self.turn == 0:
                ms_heuristic = {m: minimax(self.copy_move(m), depth, False, 1-self.turn, -math.inf, math.inf)
                                for m in ms}
                ms = [m for m, h in sorted(ms_heuristic.items(), key=lambda x: x[1], reverse=True)]
                return ms[0]  # pick biggest
            else:
                ms_heuristic = {
                    m: minimax(self.copy_move(m), depth, True, 1-self.turn, -math.inf, math.inf) for m in
                    ms}
                ms = [m for m, h in sorted(ms_heuristic.items(), key=lambda x: x[1], reverse=False)]
                return ms[0] # pick smallest

    def alpha_beta_agent(self):
        return self.alpha_beta(2)

def random_game_print():
    board = Board()
    result = None
    moven = 0

    while result is None:
        # if moven > 20:
        #     break

        print("===============================")
        print(f"move {moven}")
        print(f"no-action {board.no_action}")
        board.print()
        print(board.matrix)

        is_end, result = board.final_pos(board.turn)

        if is_end:
            if result == 0:
                print("white has won")
            else:
                print("black has won")
            continue

        move = board.random_move()
        # print(f"next move is: {move}")
        if move is None:
            print("move is none")
            return

        board.make_move(move)
        moven += 1

# agent A is white
def play(agentA, agentB):
    board = Board()

    result = None
    moven = 0

    while result is None:
        white = (moven % 2 == 0)
        is_end, result = board.final_pos(board.turn)

        if is_end:
            # print(f"action: {board.no_action}")
            # board.print()
            if result == 0:
                # print("white has won")
                return 0
            else:
                # print("black has won")
                return 1

        if white:
            # print(f"============ {board.turn} move ================")
            # board.print()
            move = agentA(board)
        else:
            # print(f"============ {board.turn} move ================")
            # board.print()
            move = agentB(board)

        # print(f"next move is: {move}")
        if move is None:
            print("move is none")
            return

        board.make_move(move)
        moven += 1


steps = 0
def play_experiment(agentA, agentB, n=10):
    global steps
    agentA_wins = 0
    agentB_wins = 0

    for i in range(n):
        steps = 0
        A_is_white = (i % 2 == 0)

        if A_is_white:
            result = play(agentA, agentB)
            if result == 0:  # A is white and white won
                agentA_wins += 1
            else:
                agentB_wins += 1
        else:
            result = play(agentB, agentA)
            if result == 0:  # A is black and white won
                agentB_wins += 1
            else:
                agentA_wins += 1

        print(f"steps {steps}, A-wins {agentA_wins}, B-wins {agentB_wins}")

    print(f"agent A won {agentA_wins}, and agent B won {agentB_wins}")

temp = Board()
# play_experiment(Board.random_agent, Board.random_agent, 1000) # ~ 500 500
play_experiment(Board.agent_simulate, Board.random_agent, n=10)  # 67 33
play_experiment(Board.alpha_beta_agent, Board.random_agent, n=10) # 84 16
play_experiment(Board.alpha_beta_agent, Board.agent_simulate, n=10)  # 95 5
