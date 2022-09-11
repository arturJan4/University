# chess agent using heuristic function
# uses own and opponent pieces values
# and own and opponent # of possible moves

# analysis playing a random agent after 100 moves for multiple games

import chess
import chess.engine
import chess.svg
import random
import math
import time
import sys


class Chess:
    def __init__(self):
        self.board = chess.Board()

    def update(self, uci_move):
        """make a move """
        try:
            move = chess.Move.from_uci(uci_move)
        except ValueError:
            raise Exception("Unknown move from UCI")

        if move not in self.board.legal_moves:
            raise Exception("Move not in legal moves")

        self.board.push(move)
        out = self.board.outcome()
        if out is None:
            return None
        if out.winner is None:
            return 0
        if out.winner:
            return -1
        else:
            return +1

    def moves(self):
        """:returns all legal moves as string"""
        return [str(m) for m in self.board.legal_moves]

    def result(self):
        """ check after 100 moves or at the end -> task specific"""
        if self.board.outcome() is None:
            return -100

        if self.board.outcome().winner == chess.WHITE:
            return 100 - self.board.fullmove_number
        else:
            return -1000

    def draw(self):
        print(f"move: {self.board.fullmove_number}")
        print(self.board)
        print("===============")


class AgentRandom:
    def __init__(self, board):
        self.board = board

    def get_move(self):
        return self.make_move_random()

    def make_move_random(self):
        legal_moves = list(self.board.legal_moves)
        return str(random.choice(legal_moves))


def play_game(AgentA, AgentB, draw=False):
    """ returns score """
    game_board = Chess()
    white = AgentA(game_board.board)
    black = AgentB(game_board.board)

    moves = 0
    while moves < 100:  # 100 full moves
        white_m = white.get_move()
        res = game_board.update(white_m)
        if draw:
            game_board.draw()
        if res is not None:  # win/loss/draw
            break

        black_m = black.get_move()
        res = game_board.update(black_m)
        if draw:
            game_board.draw()
        if res is not None:  # win/loss/draw
            break

    return game_board.result() # score function


def play_random(gamesn=50, draw=False):
    games = 0
    score = 0
    while games < gamesn:
        games += 1
        score = play_random_game(AgentScore, AgentRandom, draw)

    return score