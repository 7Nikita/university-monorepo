import random
from os import system


class Game:

    field_size = 8
    field_offset = 2
    field = [[False] * 12] * 12
    dx = [-2, -2, -1, -1, 1, 1, 2, 2]
    dy = [-1, 1, -2, 2, -2, 2, -1, 1]

    def __init__(self):
        # current position is D4
        self.current_position = [5, 5]
        self.init_field()

    def init_field(self):
        for i in range(self.field_offset, len(self.field) - self.field_offset):
            self.field[i] = [False] * self.field_offset + [True] * self.field_size + [False] * self.field_offset

    def check_status(self) -> bool:
        for x, y in zip(self.dx, self.dy):
            if self.field[self.current_position[0] + y][self.current_position[1] + x]:
                return True
        return False

    def get_possible_moves(self) -> [int, int]:
        possible_moves = []
        for x, y in zip(self.dx, self.dy):
            if self.field[self.current_position[0] + y][self.current_position[1] + x]:
                possible_moves.append([self.current_position[0] + y, self.current_position[1] + x])
        return possible_moves

    def get_move(self) -> [int, int]:
        flag = False
        move = []
        possible_moves = self.get_possible_moves()
        while not flag:
            move = input('Enter your move: ')
            flag, move = self.parse_move(move, self.current_position)
            flag = move in possible_moves
        return move

    def get_ai_move(self) -> [int, int]:
        possible_moves = self.get_possible_moves()
        return possible_moves[random.randint(0, len(possible_moves) - 1)]

    def refresh_game(self):
        self.__init__()

    def print_field(self):
        self.refresh_console()
        upper_border = [' '] + [chr(i) for i in range(ord('A'), ord('H') + 1)]
        left_border = [i for i in range(1, 9)]
        possible_move = self.get_possible_moves()
        print(possible_move)
        print(*upper_border, sep=' ')
        for i in range(self.field_size):
            print(left_border[i], end=' ')
            for j in range(self.field_size):
                if [j + self.field_offset, i + self.field_offset] == self.current_position:
                    print('0', end=' ')
                else:
                    print(' ' if [j + self.field_offset, i + self.field_offset] in possible_move else 'X', end=' ')
            print()

    @staticmethod
    def refresh_console():
        # clear the terminal screen
        system('clear')

    def parse_move(self, move, current_position):
        move = move.strip()
        if len(move) != 2:
            return False, []
        if not move[0].isalpha() or not move[1].isdigit():
            return False, []
        if move[0].lower() > 'h' or move[1] == '0' or move[1] == '9':
            return False, []
        move = [ord(move[0].lower()) - ord('a') + self.field_offset, ord(move[1]) - ord('1') + self.field_offset]
        if move == current_position:
            return False, []
        return True, move
