import random


def main():
    print("  (Black, White)")
    for i in range(100):
        print(f"game {i}: {play()}")


def play():
    "Plays a game and returns the score."
    white = 0
    black = 0
    rook_position = generate_random_position()
    bishop_position = generate_random_position(
        occupied_positions=[rook_position]
    )
    queen_position = generate_random_position(
        occupied_positions=[rook_position, bishop_position]
    )

    if diagonal_offense(queen_position, rook_position) or straight_offense(
        queen_position, rook_position
    ):
        black += 1
    if diagonal_offense(queen_position, bishop_position) or straight_offense(
        queen_position, bishop_position
    ):
        black += 1

    if diagonal_offense(bishop_position, queen_position):
        white += 1
    if straight_offense(rook_position, queen_position):
        white += 1

    return black, white


def generate_random_position(occupied_positions=None):
    """Generates a random position in the 8x8 chessboard."""
    if occupied_positions is None:
        x = random.choice(range(1, 9))
        y = random.choice(range(1, 9))
        return x, y

    if len(occupied_positions) == 1:  # 1 occupied position
        x, y = occupied_positions[0]
        while (x, y) == occupied_positions:
            x = random.choice(range(1, 9))
            y = random.choice(range(1, 9))
        return x, y

    x, y = occupied_positions[0]  # 2 occupied positions
    while (x, y) == occupied_positions[0] or (x, y) == occupied_positions[1]:
        x, y = generate_random_position()
    return x, y


def straight_offense(attacker_position, defender_position):
    """Attacker eats defender if they have the same x or y, i.e. if they are on
    the same horizontal or vertical line."""
    if attacker_position[0] == defender_position[0]:
        return True
    if attacker_position[1] == defender_position[1]:
        return True
    return False


def diagonal_offense(attacker_position, defender_position):
    """Attacker eats defender if the slope of the line which their coordinates
    define is 1 or -1, i.e. if the attacker is the center of the axes then the
    defender must lie on y=x or y=-x.
    If attacker eats defender with straight offense return, as straight offense
    and diagonal offense are mutually exclusive."""
    if straight_offense(attacker_position, defender_position):
        return False
    diff_x = attacker_position[0] - defender_position[0]
    diff_y = attacker_position[1] - defender_position[1]
    slope = diff_y // diff_x
    if slope == 1 or slope == -1:
        return True
    return False


if __name__ == "__main__":
    main()
