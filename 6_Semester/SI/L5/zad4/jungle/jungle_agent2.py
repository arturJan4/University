#!/usr/bin/env python

# Jungle/Animal chess/Dou Shou Qi
# simple low-depth (non-optimized python code) alpha-beta
# using tables that promote certain fields (this creates "defenders" for own base)
# one table promotes rat to rush to enemey base (this wins games against random and simple defenders)

import numpy as np
from enum import Enum
import random
import copy
import math
import sys

class Animal(Enum):
    R = 1 # rat
    C = 2 # cat
    D = 3 # dog
    W = 4 # wolf
    J = 5 # panther?
    T = 6 # tiger
    L = 7 # lion
    E = 8 # elephant


pieces_values = [0, 15, 20, 30, 45, 65, 90, 120, 155, 190]

rat_table = [
    1, 1, 1, 5, 2, 3, 2,
    -1, -1, 2, 2, 4, 3, 3,
    -1, -1, 1, 1, 2, 3, 3,
    -2, 1, 1, -1, 1, 1, 3,
    -2, 0, 0, -1, 0, 0, 3,
    -2, 0, 0, -1, 0, 0, 2,
    -3, -1, 0, 1, 0, 1, 1,
    -5, -3, 1, -1, 1, 0, -4,
    -5, 1, -1, -20, -1, 1, -5
]

default_table = [
    1, 2, 3, 5, 3, 2, 1,
    2, 2, 2, 3, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 1,
    1, 0, 0, 1, 0, 0, 0,
    1, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0.5, 0.5, 0.5, 1, 0.5, 0.5, 0.5,
    0, 0, 1.5, 1, 1.5, 0, 0,
    0, 0, 1, -20, 1, 0, 0
]

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

    def position_singular(self, pos, white):
        """
        if white -> start at bottom
        pos is (y, x) pair
        """
        y, x = pos
        result = y * self.WIDTH
        result += x

        if not white:
            return self.WIDTH * self.HEIGHT - 1 - result
        else:
            return result

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
        if move is None:
            self.turn = 1 - self.turn
            self.no_action += 1
            return

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

    def heu(self):
        """take into consideration sum of pieces and manhattan distance of each to opponent's nest"""
        def manhattan_dist(pos0, pos1):
            y0, x0 = pos0
            y1, x1 = pos1
            return abs(x0-x1) + abs(y0-y1)

        sums = {0: 0, 1: 0}
        position = {0: 0, 1: 0}
        dists = {0: 0, 1: 0}
        closests = {0: -100, 1: -100}
        for i in [0, 1]:
            for piece in self.pieces[i].items():
                val, pos = piece
                sums[i] += pieces_values[val] / 10
                dist = (1/manhattan_dist(pos, self.dens[1-i]))
                if closests[i] < dist:
                    closests[i] = dist * 4

                if val == 1:  # rats move rapidly
                    position[i] += rat_table[self.position_singular(pos, i == 0)] / 12
                    dists[i] += dist * 5
                else:
                    position[i] += default_table[self.position_singular(pos, i == 0)] / 12
                    dists[i] += dist

        # 0 is maximizing
        # if random.randint(0, 1000) == 0:
        #    print("heuristic:")
        #    self.print()
        #    print(f"sum {sums}, pos: {position}, dists: {dists}, closests: {closests}")

        return (sums[0] - sums[1]) + (dists[0] - dists[1]) + (position[0] - position[1]) + (closests[0] - closests[1])

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

            #def heu_inside(board):
            #    final, winner = board.final_pos(1-player)
            #    if final:
            #        if winner == 0:
            #            return 10000
            #        else:
            #            return -10000
            #
            #    return board.heu()

            # boards = [board.copy_move(m) for m in moves]
            # move_order = [(board, heu_inside(board)) for board in boards]
            # move_order.sort(key=lambda tup: tup[1], reverse=not maximazing_player)

            if maximazing_player:  # is white (0)
                max_eval = -math.inf
                for m in moves:
                    evalt = minimax(board.copy_move(m), depth - 1, False, 1 - player, alpha, beta)
                    max_eval = max(max_eval, evalt)
                    alpha = max(alpha, evalt)
                    if beta <= alpha:
                        break
                return max_eval
            else:
                min_eval = math.inf
                for m in moves:
                    evalt = minimax(board.copy_move(m), depth - 1, True, 1 - player, alpha, beta)
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
                return max(ms_heuristic, key=ms_heuristic.get)
            else:
                ms_heuristic = {
                    m: minimax(self.copy_move(m), depth, True, 1-self.turn, -math.inf, math.inf) for m in
                    ms}
                return min(ms_heuristic, key=ms_heuristic.get)

        return None

    def alpha_beta_agent(self, n=2):
        return self.alpha_beta(n)

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
            print(f"action: {board.no_action}")
            board.print()
            if result == 0:
                # print("white has won")
                return 0
            else:
                # print("black has won")
                return 1

        if white:
            print(f"============ {board.turn} move ================")
            board.print()
            move = agentA(board)
        else:
            print(f"============ {board.turn} move ================")
            board.print()
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

        # print(f"steps {steps}, A-wins {agentA_wins}, B-wins {agentB_wins}")

    print(f"agent A won {agentA_wins}, and agent B won {agentB_wins}")

# temp = Board()
# print(temp.pieces)
# x = temp.position_singular(temp.pieces[0][8], False)
# print(x)
# print(rat_table[x])
# play_experiment(Board.random_agent, Board.random_agent, 1000) # ~ 500 500
# play_experiment(Board.agent_simulate, Board.random_agent, n=100)  # 67 33
# play_experiment(Board.alpha_beta_agent, Board.alpha_beta_agent, n=1) # 82 18
# play_experiment(Board.alpha_beta_agent, Board.agent_simulate, n=100)  # 95 5

class Player(object):
    my_player = None
    board = None

    def __init__(self):
        self.reset()

    def reset(self):
        self.board = Board()
        self.my_player = 1
        self.say('RDY')

    def say(self, what):
        sys.stdout.write(what)
        sys.stdout.write('\n')
        sys.stdout.flush()

    def hear(self):
        line = sys.stdin.readline().split()
        return line[0], line[1:]

    def loop(self):
        game_timeout=60
        while True:
            cmd, args = self.hear()
            if cmd == 'HEDID':
                unused_move_timeout, game_timeout = args[:2]
                game_timeout = float(game_timeout)
                move = tuple((int(m) for m in args[2:]))
                if move == (-1, -1, -1, -1):
                    move = None
                else:
                    xs, ys, xd, yd = move
                    move = ((ys, xs), (yd, xd))

                self.board.make_move(move)
            elif cmd == 'ONEMORE':
                self.reset()
                continue
            elif cmd == 'BYE':
                break
            else:
                assert cmd == 'UGO'
                # assert not self.game.move_list
                self.my_player = 0  # is white

            n = 2
            if game_timeout < 10:
                n = 1
            move = self.board.alpha_beta_agent(n)
            if move:
                self.board.make_move(move)
                fr, to = move
                ys, xs = fr
                yd, xd = to

                move = (xs, ys, xd, yd)
            else:
                self.board.make_move(None)
                move = (-1, -1, -1, -1)
            self.say('IDO %d %d %d %d' % move)


if __name__ == '__main__':
    player = Player()
    player.loop()