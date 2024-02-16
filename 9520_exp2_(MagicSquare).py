import random

def print_board(board):
    for row in board:
        print(" | ".join(row))
        if row != board[-1]:
            print("-" * 9)


def check_win(board, player):
    for i in range(3):
        if all([cell == player for cell in board[i]]) or all([board[j][i] == player for j in range(3)]):
            return True
    if all([board[i][i] == player for i in range(3)]) or all([board[i][2 - i] == player for i in range(3)]):
        return True
    return False


def is_board_full(board):
    return all([cell != " " for row in board for cell in row])


def get_best_move(board):
    magic_square = [[8, 1, 6], [3, 5, 7], [4, 9, 2]]
    best_move = None
    max_score = -1
    for i in range(3):
        for j in range(3):
            if board[i][j] == " ":
                score = 0
                for k in range(3):
                    score += magic_square[i][k] if board[i][k] == "O" else 0
                    score += magic_square[k][j] if board[k][j] == "O" else 0
                score += magic_square[i][j] if i == j else 0
                score += magic_square[i][2 - j] if i + j == 2 else 0
                if score > max_score:
                    max_score = score
                    best_move = (i, j)
    return best_move


def computer_turn(board):
    move = get_best_move(board)
    board[move[0]][move[1]] = "O"
    print("Computer's move:")
    print_board(board)


def player_turn(board):
    while True:
        try:
            row = int(input("Enter row (1, 2, or 3): ")) - 1
            col = int(input("Enter column (1, 2, or 3): ")) - 1
            if 0 <= row < 3 and 0 <= col < 3 and board[row][col] == " ":
                board[row][col] = "X"
                print_board(board)
                break
            else:
                print("Invalid move! Try again.")
        except ValueError:
            print("Invalid input! Please enter a number.")


def play_game():
    board = [[" " for _ in range(3)] for _ in range(3)]
    print("Welcome to Tic Tac Toe with Magic Square Method!")
    print_board(board)
    while True:
        player_turn(board)
        if check_win(board, "X"):
            print("Congratulations! You win!")
            break
        if is_board_full(board):
            print("It's a draw!")
            break
        computer_turn(board)
        if check_win(board, "O"):
            print("Computer wins! Better luck next time.")
            break

play_game()
