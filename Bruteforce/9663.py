# Algorithm Study
# Backjoon: N-Queen (9663)
# https://www.acmicpc.net/problem/9663

col = [True] * 15
left_diag = [True] * 30
right_diag = [True] * 30
N = 0
possibleCase = 0


def isPossible(y, x):
    if col[x] and left_diag[y - x + N] and right_diag[y + x]:
        return True

    return False


def nQueen(y):
    global possibleCase

    # Strategy: Backtracking: Prune not possible cases.
    # Before put new queen, check if it is possible.
    # If is not possible, immediately return and try another.
    # Searching all row and column will be inefficient.

    # Remove Row possibility by add y value after appending.
    # Column Case: Save x index at row[].
        # If row = [0], (0,0), (1,0), (2,0).... will be detected.
    # Left Diagonal Case = Subtracting both y,x will result same value.
        # (2,0), (3,1), (4,2) ... => all 2.
        # All N to prevent Minus Value (0,2) (1,3) (2,4)... => all -2 + N
            # Least Value = (0,N - 1) => -(N-1) + N = 1
            # Maximum Value = (N-1, 0) => N-1 + N = 2N - 1
    # Right Diagonal Case = Adding both value will result same value.
        # (2,0) (1,1) (0,2) = all 2.
            # Least Value = (0,0) = 0
            # Maximum Value = (N-1, N-1) = 2N - 2

    if y >= N:
        possibleCase += 1
        return

    for x in range(N):
        if isPossible(y, x):
            col[x], left_diag[y - x + N], right_diag[y + x] = False, False, False
            nQueen(y + 1)  # Remove Same Row Possibility
            col[x], left_diag[y - x + N], right_diag[y + x] = True, True, True

    return


if __name__ == '__main__':
    N = int(input())
    nQueen(0)

    print(f"{possibleCase}")
