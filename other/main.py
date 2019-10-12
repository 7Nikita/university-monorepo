from game import Game


def main():
    game = Game()
    turn = 0

    while game.check_status():
        game.print_field()
        game.current_position = game.get_ai_move() if turn else game.get_move()
        game.field[game.current_position[0]][game.current_position[1]] = False
        turn ^= 1

    print('Defeat' if turn else 'Victory')


if __name__ == '__main__':
    main()
