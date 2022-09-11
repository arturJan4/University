# chess agent using the minmax algorithm (alpha-beta wiithout transpositions, iterative deepening, aspiration windows, etc. only a simple version)
# heuristic uses pieces values and mobility
# also promotes certain squares for given pieces
# polyglot was used for playing openings from opening book (small one for this example)
# syzygy was used for precomputated endings (easy to include db's that weight >100GB)

import chess
import chess.engine
import chess.polyglot
import chess.syzygy
import random
import math
import time
import sys

reader = chess.polyglot.open_reader("data/polyglot/baron30.bin")
tablebase = chess.syzygy.open_tablebase("data/syzygy")  # sygyzy ending table

class Chess:
    def __init__(self):
        self.board = chess.Board()
        self.pieces_values = {
            chess.PAWN: 100,
            chess.KNIGHT: 320,
            chess.BISHOP: 340,
            chess.ROOK: 500,
            chess.QUEEN: 900,
            chess.KING: 20000
        }

        # https://www.chessprogramming.org/Simplified_Evaluation_Function
        # piece-square tables
        self.pawns_table = [
            0, 0, 0, 0, 0, 0, 0, 0,
            50, 50, 50, 50, 50, 50, 50, 50,
            10, 10, 20, 30, 30, 20, 10, 10,
            5, 5, 10, 25, 25, 10, 5, 5,
            0, 0, 0, 20, 20, 0, 0, 0,
            5, -5, -10, 0, 0, -10, -5, 5,
            5, 10, 10, -20, -20, 10, 10, 5,
            0, 0, 0, 0, 0, 0, 0, 0
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

        self.score_position()

    def get_move(self, timeout):
        """returns move using some strategy"""
        # opening
        db_move = reader.get(self.board)
        if db_move:
            return str(db_move.move)

        if timeout < 15:
            ms = self.alpha_beta(0)
        elif timeout < 30:
            ms = self.alpha_beta(1)
        else:
            ms = self.alpha_beta(2)

        return ms

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

            result += sum([self.pawns_table[chess.square_mirror(i)] for i in self.board.pieces(chess.PAWN, chess.WHITE)]) - sum(
                [self.pawns_table[i] for i in self.board.pieces(chess.PAWN, chess.BLACK)])
            result += sum([self.knights_table[chess.square_mirror(i)] for i in self.board.pieces(chess.KNIGHT, chess.WHITE)]) - sum(
                [self.knights_table[i] for i in self.board.pieces(chess.KNIGHT, chess.BLACK)])
            result += sum([self.bishops_table[chess.square_mirror(i)] for i in self.board.pieces(chess.BISHOP, chess.WHITE)]) - sum(
                [self.bishops_table[i] for i in self.board.pieces(chess.BISHOP, chess.BLACK)])
            result += sum([self.rooks_table[chess.square_mirror(i)] for i in self.board.pieces(chess.ROOK, chess.WHITE)]) - sum(
                [self.rooks_table[i] for i in self.board.pieces(chess.ROOK, chess.BLACK)])
            result += sum([self.queens_table[chess.square_mirror(i)] for i in self.board.pieces(chess.QUEEN, chess.WHITE)]) - sum(
                [self.queens_table[i] for i in self.board.pieces(chess.QUEEN, chess.BLACK)])
            result += sum([self.kings_table[chess.square_mirror(i)] for i in self.board.pieces(chess.KING, chess.WHITE)]) - sum(
                [self.kings_table[i] for i in self.board.pieces(chess.KING, chess.BLACK)])

            # mobility
            saved_turn = self.board.turn
            mobility = 0
            self.board.turn = chess.WHITE
            mobility += len(list(self.board.legal_moves))
            self.board.turn = chess.BLACK
            mobility -= len(list(self.board.legal_moves))
            # print(result, mobility*3)
            result += mobility / 2
            self.board.turn = saved_turn

        return result

    def update(self, uci_move):
        try:
            move = chess.Move.from_uci(uci_move)
        except ValueError:
            raise Exception("Wrong move")

        if move not in self.board.legal_moves:
            raise Exception("Wrong move")

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
        return [str(m) for m in self.board.legal_moves]

    def score(self, move):
        result = 0
        self.board.push(move)

        if self.board.outcome() is not None:
            winner = self.board.outcome().winner
            if winner is None:
                result = -math.inf
            elif winner == chess.WHITE:
                result =  math.inf
            else:
                result = -math.inf
        else:
            for piece, score in self.pieces_values.items():
                result += len(self.board.pieces(piece, chess.WHITE)) * score
                result -= len(self.board.pieces(piece, chess.BLACK)) * score

        self.board.pop()
        return result

    def draw(self):
        print(self.board)


class Player(object):
    game = None
    my_player = None

    def __init__(self):
        self.reset()

    def reset(self):
        self.game = Chess()
        self.my_player = 1
        self.timeout = 60
        self.say('RDY')

    def say(self, what):
        sys.stdout.write(what)
        sys.stdout.write('\n')
        sys.stdout.flush()

    def hear(self):
        line = sys.stdin.readline().split()
        return line[0], line[1:]

    def loop(self):
        while True:
            cmd, args = self.hear()
            if cmd == 'HEDID':
                unused_move_timeout, unused_game_timeout = args[:2]
                self.timeout = float(unused_game_timeout)
                move = args[2]

                # he moved
                self.game.update(move)
            elif cmd == 'ONEMORE':
                self.reset()
                continue
            elif cmd == 'BYE':
                break
            else:
                assert cmd == 'UGO'
                # assert not self.game.move_list
                self.my_player = 0

            # pick my move
            move = self.game.get_move(self.timeout)
            # raise Exception(f"{move}")
            self.game.update(str(move))

            self.say('IDO ' + str(move))

#print("My agent " + str(play(AgentHillClimbing)))
#print("Stockfish " + str(play(AgentStockfish)))

if __name__ == '__main__':
    player = Player()
    player.loop()

