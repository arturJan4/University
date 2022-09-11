import sys
import queue

# cooperative 2-move mate
# assumptions:
# black king is cooperative
# white king already castled

# some moves might be out of bounds or illegal!
# all 8 possible king moves
KING_MOVES = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
# all 28 possible rook moves (only one coordinate changes -> vertical/horizontal moves)
ROOK_MOVES = [(x, 0) for x in range(-7, 8) if x != 0] + [(0, y) for y in range(-7, 8) if y != 0]


class BoardState:
    """
    wk - white king position e.g. ("b2")
    wr - white rook
    bk - black king
    turn - "black"|"white"
    next/prev - pointer to next/prev State
    """
    def __init__(self, wk, wr, bk, turn):
        self.wk = wk
        self.wr = wr
        self.bk = bk
        self.turn = turn
        # self.next = None
        self.prev = None

    @staticmethod
    def to_position(string_coordinates):
        """Converts string to column, row pair (e.g. "b3" -> 1, 2"""
        col = ord(string_coordinates[0]) - ord('a')
        row = ord(string_coordinates[1]) - ord('1')

        return col, row

    @staticmethod
    def to_state(column, row):
        """Converts position to string equivalent"""
        column_char = chr(ord('a') + column)
        row_char = chr(ord('1') + row)

        return column_char + row_char

    @staticmethod
    def state_from_line(line):
        """Converts line input to State object"""
        turn, wk, wr, bk = line.split()
        return BoardState(wk, wr, bk, turn)

    def __str__(self):
        """String representation of a State"""
        return " ".join([self.turn, self.wk, self.wr, self.bk])

    def append_state(self, s):
        """Linked list of States (for reconstructing moves)"""
        self.next = s
        s.prev = self

    def rook_moves(self):
        """Set of all possible rook moves from current State"""
        if self.turn == "black":
            return []

        # pieces coordinates
        col, row = BoardState.to_position(self.wr)
        # print("rook position", col, row)
        col_bk, row_bk = BoardState.to_position(self.bk)
        col_wk, row_wk = BoardState.to_position(self.wk)

        moves = []

        for move in ROOK_MOVES:
            new_col, new_row = col + move[0], row + move[1]  # do the move

            # prune out of bounds
            if new_col < 0 or new_col > 7:
                continue
            if new_row < 0 or new_row > 7:
                continue

            # prune other king's positions
            if new_row == row_bk and new_col == col_bk:
                continue
            if new_row == row_wk and new_col == col_wk:
                continue

            # prune if there is another piece in the way
            # horizontal move
            if new_row == row:
                if (row == row_bk) and ((new_col < col_bk < col) or (new_col > col_bk > col)):
                    continue
                if (row == row_wk) and ((new_col < col_wk < col) or (new_col > col_wk > col)):
                    continue
            # vertical move
            if new_col == col:
                if (col == col_bk) and ((new_row < row_bk < row) or (new_row > row_bk > row)):
                    continue
                if (col == col_wk) and ((new_row < row_wk < row) or (new_row > row_wk > row)):
                    continue

            # print("move option", new_col, new_row)

            # prune king takes rook
            temp_state = BoardState(self.wk, BoardState.to_state(new_col, new_row), self.bk, "black")
            if temp_state.is_check():
                bk_area = []
                wk_area = []
                for move in KING_MOVES:
                    bk_area.append((col_bk + move[0], row_bk + move[1]))
                    wk_area.append((col_wk + move[0], row_wk + move[1]))

                if ((new_col, new_row) in bk_area) and not ((new_col, new_row) in wk_area):
                    continue

            moves.append((new_col, new_row))

        return moves

    def king_moves(self):
        """Set of all possible moves of a king from current State"""

        # king's coordinates
        col, row = BoardState.to_position(self.wk)
        # different color's king's coordinates
        col_other, row_other = BoardState.to_position(self.bk)
        col_wr, row_wr = BoardState.to_position(self.wr)

        moves = []
        capture_rook = False  # TODO

        # swap
        if self.turn == "black":
            col, col_other = col_other, col
            row, row_other = row_other, row

        for move in KING_MOVES:
            new_col, new_row = col + move[0], row + move[1]  # do the move

            # prune out of bounds
            if new_col < 0 or new_col > 7:
                continue
            if new_row < 0 or new_row > 7:
                continue

            # special case (white rook can be taken by a black king)
            # happens only if there is no other move from black
            # TODO: is this even needed here
            if self.turn == "black" and new_row == row_wr and new_col == col_wr:
                capture_rook = True
                continue

            # prune rook's and other king's positions
            if new_row == row_other and new_col == col_other:
                continue
            if new_row == row_wr and new_col == col_wr:
                continue

            # prune other king's surrounding 3x3 area
            legal = True
            for move_other in KING_MOVES:
                new_col_other, new_row_other = col_other + move_other[0], row_other + move_other[1]
                if new_row == new_row_other and new_col == new_col_other:
                    legal = False
                    break

            # prune rook's horizontal/vertical line for black king's move without white king in the way
            if self.turn == "black":
                if new_row == row_wr and not ((row_wr == row_other) and (col < col_other < col_wr)):
                    continue
                if new_col == col_wr and not ((col_wr == col_other) and (row < row_other < row_wr)):
                    continue

            if not legal:
                continue

            moves.append((new_col, new_row))

        # # special case (white rook can be taken by a black king)
        # if not moves and capture_rook:
        #     return -1

        return moves

    def is_check(self):
        # only white has material for a mate
        if self.turn == 'white':
            return False

        # pieces coordinates
        col_wk, row_wk = BoardState.to_position(self.wk)
        col_bk, row_bk = BoardState.to_position(self.bk)
        col_wr, row_wr = BoardState.to_position(self.wr)

        # TODO: assumption -> king cannot trapped be in the corner with the rook close
        # it must be rook checking the king

        if (col_wr == col_bk and not (row_wr < row_wk < row_bk)) or ((row_wr == row_bk) and not (col_wr < col_wk < col_bk)):
            return True

        return False

    def is_checkmate(self):
        """Check if current state position is a checkmate (remember turn)"""
        # only black can be mated
        if self.turn == 'white':
            return False

        # pieces coordinates
        col_wk, row_wk = BoardState.to_position(self.wk)
        col_bk, row_bk = BoardState.to_position(self.bk)
        col_wr, row_wr = BoardState.to_position(self.wr)

        # might be stalemate!
        if not self.is_check():
            return False

        # try to move black king
        for move in self.king_moves():
            temp_state = BoardState(self.wk, self.wr, BoardState.to_state(move[0], move[1]), self.turn)

            if not temp_state.is_check():
                return False

        return True

    def generate_states(self):
        """Generate all possible (legal) states from current state"""
        # black rook can move anywhere (except wk, bk positions)
        # if white king is reaching it -> it should be protected by black king
        # black king can move anywhere (except br, wk) where it is not checked
        # white king can move anywhere (except br, bk) where it is not checked

        states = []

        new_turn = "black"
        if self.turn == "black":
            new_turn = "white"

        if self.turn == "white":
            new_turn = "black"
            for move in self.king_moves():
                wk_new = BoardState.to_state(move[0], move[1])
                states.append(BoardState(wk_new, self.wr, self.bk, new_turn))

        if self.turn == "black":
            new_turn = "white"
            for move in self.king_moves():
                bk_new = BoardState.to_state(move[0], move[1])
                states.append(BoardState(self.wk, self.wr, bk_new, new_turn))

        for move in self.rook_moves():
            wr_new = BoardState.to_state(move[0], move[1])
            states.append(BoardState(self.wk, wr_new, self.bk, new_turn))

        return states

    def print_board(self):
        BLUE = '\033[94m'
        GREEN = '\033[92m'
        ENDC = '\033[0m'

        wk_chr = BLUE + "K" + ENDC
        wr_chr = BLUE + "R" + ENDC
        bk_chr = GREEN + "K" + ENDC

        print("TURN:", self.turn)
        if self.is_checkmate():
            print("#")
        elif self.is_check():
            print("+")

        for i in range(7, -1, -1):  # rows (up to down)
            for j in range(0, 8):  # columns (left to right)
                # string comparisons
                if BoardState.to_state(j, i) == self.wk:
                    print(wk_chr, end=" ")
                elif BoardState.to_state(j, i) == self.wr:
                    print(wr_chr, end=" ")
                elif BoardState.to_state(j, i) == self.bk:
                    print(bk_chr, end=" ")
                else:
                    print("*", end=" ")
            print("")


def solve(state):
    pass
    # BFS code
    # queue:
    # check if state was "visited" -> if yes -> return
    # generate possible moves from given state -> cutoff bad ones (stalemate and illegal moves)
    # next move == next state
    # push state to queue
    # keep a list of "visited" states

    q = queue.Queue()
    q.put(state)

    visited = set()
    visited.add(str(state))

    while not q.empty():
        current_state = q.get()
        # current_state.print_board()

        if current_state.is_checkmate():
            # current_state.print_board()
            return current_state

        for state in current_state.generate_states():
            if str(state) not in visited:
                state.prev = current_state
                visited.add(str(state))
                q.put(state)

    return -1


def unwind_state(state):
    states = []

    temp = state

    while temp is not None:
        states.append(temp)
        temp = temp.prev

    #for i in range(len(states)-1, -1, -1):
    #   states[i].print_board()

    return len(states) - 1

# tests
# line = "black a2 e4 a4"
# state = BoardState.state_from_line(line)
# print(state)
# state.print_board()
# print(BoardState.to_position('c4'))
# print(BoardState.to_state(2, 3))
# for move in state.rook_moves():
#     print(move)
# for move in state.king_moves():
#     print(move)
# print(state.is_check())
# print(state.is_checkmate())
# state_solved = solve(state)
# unwind_state(state_solved)

# line = "white a2 e4 a5"
# state = BoardState.state_from_line(line)
# print(state)
# state.print_board()
# print(BoardState.to_position('c4'))
# print(BoardState.to_state(2, 3))
# for move in state.rook_moves():
#    print(move)
# print("kings:")
# for move in state.king_moves():
#     print(move)
# print(state.is_check())
# print(state.is_checkmate())
# state_solved = solve(state)
# unwind_state(state_solved)

# line = "white b6 c4 b8"
# state = BoardState.state_from_line(line)
# print(state)
# state.print_board()
# print(BoardState.to_position('c4'))
# print(BoardState.to_state(2, 3))
# for move in state.rook_moves():
#     print(move)
# print("kings:")
# for move in state.king_moves():
#     print(move)
# print(state.is_check())
# print(state.is_checkmate())
# #for state in state.generate_states():
#     #state.print_board()
# state_solved = solve(state)
# unwind_state(state_solved)

# line = "black b6 d8 b8"
# state = BoardState.state_from_line(line)
# print(state)
# state.print_board()
# for move in state.rook_moves():
#     print(move)
# print("king:")
# for move in state.king_moves():
#     print(move)
# print(state.is_check())
# print(state.is_checkmate())

# line = "white e6 e8 c8"
# state = BoardState.state_from_line(line)
# print(state)
# state.print_board()
# for move in state.rook_moves():
#     print(move)
# print("king:")
# for move in state.king_moves():
#     print(move)
# print(state.is_check())
# print(state.is_checkmate())
# for state in state.generate_states():
#     state.print_board()

with open("zad1_input.txt", "r") as rd:
    with open("zad1_output.txt", "w") as wr:
        if len(sys.argv) > 2:
            print('wrong arguments, use "python3 z1.py" or "python3 z1.py debug"')
            sys.exit(1)

        debug = False
        if len(sys.argv) == 2 and sys.argv[1] == "debug":
            debug = True

        for line in rd:
            state = BoardState.state_from_line(line)
            print(unwind_state(solve(state)), file=wr)
