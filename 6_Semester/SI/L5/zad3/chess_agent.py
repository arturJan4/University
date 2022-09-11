import chess
import chess.engine
import chess.polyglot
import chess.syzygy
import chess.svg
import random
import math
import time
import sys

reader = chess.polyglot.open_reader("data/polyglot/baron30.bin")
tablebase = chess.syzygy.open_tablebase("data/syzygy") # sygyzy ending table

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
            chess.PAWN: 100,
            chess.KNIGHT: 320,
            chess.BISHOP: 340,
            chess.ROOK: 500,
            chess.QUEEN: 900,
            chess.KING: 20000
        }

        #https://www.chessprogramming.org/Simplified_Evaluation_Function
        # piece-square tables
        self.pawns_table = [
            0,  0,  0,  0,  0,  0,  0,  0,
            50, 50, 50, 50, 50, 50, 50, 50,
            10, 10, 20, 30, 30, 20, 10, 10,
            5,  5, 10, 25, 25, 10,  5,  5,
            0,  0,  0, 20, 20,  0,  0,  0,
            5, -5,-10,  0,  0,-10, -5,  5,
            5, 10, 10,-20,-20, 10, 10,  5,
            0,  0,  0,  0,  0,  0,  0,  0
        ]

        self.knights_table = [
            -20, -10, -10, -10, -10, -10, -10, -20,
            -10, 0, 0, 0, 0, 0, 0, -10,
            -10, 0, 5, 10, 10, 5, 0, -10,
            -10, 5, 5, 10, 10, 5, 5, -10,
            -10, 0, 10, 10, 10, 10, 0, -10,
            -10, 10, 10, 10, 10, 10, 10, -10,
            -10, 5, 0, 0, 0, 0, 5, -10,
            -20, -10, -10, -10, -10, -10, -10, -20
        ]

        self.bishops_table = [
            -20, -10, -10, -10, -10, -10, -10, -20,
            -10, 0, 0, 0, 0, 0, 0, -10,
            -10, 0, 5, 10, 10, 5, 0, -10,
            -10, 5, 5, 10, 10, 5, 5, -10,
            -10, 0, 10, 10, 10, 10, 0, -10,
            -10, 10, 10, 10, 10, 10, 10, -10,
            -10, 5, 0, 0, 0, 0, 5, -10,
            -20, -10, -10, -10, -10, -10, -10, -20
        ]

        self.rooks_table = [
            0, 0, 0, 0, 0, 0, 0, 0,
            5, 10, 10, 10, 10, 10, 10, 5,
            -5, 0, 0, 0, 0, 0, 0, -5,
            -5, 0, 0, 0, 0, 0, 0, -5,
            -5, 0, 0, 0, 0, 0, 0, -5,
            -5, 0, 0, 0, 0, 0, 0, -5,
            -5, 0, 0, 0, 0, 0, 0, -5,
            0, 0, 0, 5, 5, 0, 0, 0
        ]

        self.queens_table = [
            -20, -10, -10, -5, -5, -10, -10, -20,
            -10, 0, 0, 0, 0, 0, 0, -10,
            -10, 0, 5, 5, 5, 5, 0, -10,
            -5, 0, 5, 5, 5, 5, 0, -5,
            0, 0, 5, 5, 5, 5, 0, -5,
            -10, 5, 5, 5, 5, 5, 0, -10,
            -10, 0, 5, 0, 0, 0, 0, -10,
            -20, -10, -10, -5, -5, -10, -10, -20
        ]

        # TODO: change for endgame
        self.kings_table = [
            -30, -40, -40, -50, -50, -40, -40, -30,
            -30, -40, -40, -50, -50, -40, -40, -30,
            -30, -40, -40, -50, -50, -40, -40, -30,
            -30, -40, -40, -50, -50, -40, -40, -30,
            -20, -30, -30, -40, -40, -30, -30, -20,
            -10, -20, -20, -20, -20, -20, -20, -10,
            20, 20, 0, 0, 0, 0, 20, 20,
            20, 30, 10, 0, 0, 10, 30, 20
        ]

        # self.score_position()

    def get_move(self):
        """returns move using some strategy"""
        # opening
        db_move = reader.get(self.board)
        if db_move:
            return str(db_move.move)

        ms = self.alpha_beta(1)
        if ms:
            return str(ms)
        else:
            raise RuntimeError("alpha-beta error")

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

    def alpha_beta(self, depth):
        def minimax(depth, maximazing_player, alpha, beta):
            if depth == 0 or (self.board.outcome() is not None):
                return self.score_position()

            moves = self.board.legal_moves
            if maximazing_player:  # is white (0)
                max_eval = -math.inf
                for move in moves:
                    self.board.push(move)
                    evalt = minimax(depth - 1, False, alpha, beta)
                    self.board.pop()
                    max_eval = max(max_eval, evalt)
                    alpha = max(alpha, evalt)
                    if beta <= alpha:
                        break
                return max_eval
            else:
                min_eval = math.inf
                for move in moves:
                    self.board.push(move)
                    evalt = minimax(depth - 1, True, alpha, beta)
                    self.board.pop()
                    min_eval = min(min_eval, evalt)
                    beta = min(beta, evalt)
                    if beta <= alpha:
                        break
                return min_eval

        ms = self.board.legal_moves
        if ms:
            if self.board.turn == chess.WHITE:
                ms_heuristic = {}
                for m in ms:
                    self.board.push(m)
                    ms_heuristic[m] = minimax(depth, False, -math.inf, math.inf)
                    self.board.pop()

                ms = [m for m, h in sorted(ms_heuristic.items(), key=lambda x: x[1], reverse=True)]
                return ms[0]  # pick biggest
            else:
                ms_heuristic = {}
                for m in ms:
                    self.board.push(m)
                    ms_heuristic[m] = minimax(depth, True, -math.inf, math.inf)
                    self.board.pop()
                ms = [m for m, h in sorted(ms_heuristic.items(), key=lambda x: x[1], reverse=False)]
                return ms[0]  # pick smallest

        return None

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

    def score_position(self):
        result = 0

        if self.board.outcome() is not None:
            winner = self.board.outcome().winner
            if winner is None:
                result = -10000
            elif winner == chess.WHITE:
                result = 1000000
            else:
                result = -1000000
        else:
            wdl = tablebase.get_wdl(self.board)

            if wdl:
                if wdl == 0:
                    return -10000

                if self.board.turn and wdl > 0:
                    return 1000000
                elif self.board.turn and wdl < 0:
                    return -1000000
                elif not self.board.turn and wdl > 0:
                    return -1000000
                else:
                    return 1000000

            for piece, score in self.pieces_values.items():
                result += len(self.board.pieces(piece, chess.WHITE)) * score
                result -= len(self.board.pieces(piece, chess.BLACK)) * score

            result += sum([self.pawns_table[i] for i in self.board.pieces(chess.PAWN, chess.WHITE)]) - sum([self.pawns_table[chess.square_mirror(i)] for i in self.board.pieces(chess.PAWN, chess.BLACK)])
            result += sum([self.knights_table[i] for i in self.board.pieces(chess.KNIGHT, chess.WHITE)]) - sum([self.knights_table[chess.square_mirror(i)] for i in self.board.pieces(chess.KNIGHT, chess.BLACK)])
            result += sum([self.bishops_table[i] for i in self.board.pieces(chess.BISHOP, chess.WHITE)]) - sum([self.bishops_table[chess.square_mirror(i)] for i in self.board.pieces(chess.BISHOP, chess.BLACK)])
            result += sum([self.rooks_table[i] for i in self.board.pieces(chess.ROOK, chess.WHITE)]) - sum([self.rooks_table[chess.square_mirror(i)] for i in self.board.pieces(chess.ROOK, chess.BLACK)])
            result += sum([self.queens_table[i] for i in self.board.pieces(chess.QUEEN, chess.WHITE)]) - sum([self.queens_table[chess.square_mirror(i)] for i in self.board.pieces(chess.QUEEN, chess.BLACK)])
            result += sum([self.kings_table[i] for i in self.board.pieces(chess.KING, chess.WHITE)]) - sum([self.kings_table[chess.square_mirror(i)] for i in self.board.pieces(chess.KING, chess.BLACK)])

            # mobility
            saved_turn = self.board.turn
            mobility = 0
            self.board.turn = chess.WHITE
            mobility += len(list(self.board.legal_moves))
            self.board.turn = chess.BLACK
            mobility -= len(list(self.board.legal_moves))
            # print(result, mobility*3)
            result += mobility * 3
            self.board.turn = saved_turn

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

#test = Chess()
#for i in test.board.pieces(chess.PAWN, chess.WHITE):
#    print(i)

#play_random(1, True)
for i in range(5):
    score = play_random(1, True)
    print(score)