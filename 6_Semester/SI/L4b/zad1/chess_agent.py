# easy chess agent playing against random moves
# uses scholar's mate and only piece value heuristic

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
            return 100 - (self.board.fullmove_number / 2 + 1)
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


class AgentScore:
    def __init__(self, board):
        self.board = board
        self.pieces_values = {
            chess.PAWN: 1,
            chess.KNIGHT: 2,
            chess.BISHOP: 3,
            chess.ROOK: 5,
            chess.QUEEN: 10,
            chess.KING: 100
        }

    def get_move(self):
        """returns move using some strategy"""
        legal_moves = self.board.legal_moves

        # scholars mate
        if self.board.fullmove_number == 1 and chess.Move.from_uci("e2e4") in legal_moves:
            return "e2e4"
        if self.board.fullmove_number == 2 and chess.Move.from_uci("f1c4") in legal_moves:
            return "f1c4"
        if self.board.fullmove_number == 3 and chess.Move.from_uci("d1h5") in legal_moves:
            return "d1h5"

        # calculate score for each move
        m_score = {str(m): self.score(m) for m in legal_moves}
        i, max_score = max(m_score.items(), key=lambda x: x[1])

        # if there are more items of same score
        ms = list(filter(lambda a: a[1] == max_score, m_score.items()))

        # pick random
        if ms:
            return random.choice(ms)[0]
        else:
            return random.choice(legal_moves)

    def score(self, move):
        """ calculate score after making a given move"""
        result = 0
        self.board.push(move)

        if self.board.outcome() is not None:
            winner = self.board.outcome().winner
            if winner is None:
                result = -math.inf
            elif winner == chess.WHITE:
                result = math.inf
            else:
                result = -math.inf
        else:
            for piece, score in self.pieces_values.items():
                result += len(self.board.pieces(piece, chess.WHITE)) * score
                result -= len(self.board.pieces(piece, chess.BLACK)) * score

        self.board.pop()
        return result


def play_random_game(AgentA, AgentB, draw=False):
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


    return game_board.result()


def play_random(gamesn=50, draw=False):
    games = 0
    score = 0
    while games < gamesn:
        games += 1
        score = play_random_game(AgentScore, AgentRandom, draw)

    return score


for i in range(5):
    score = play_random(50, False)
    print(score/50)