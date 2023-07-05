# Algorithm Study
# Backjoon: 감시 피하기 (18428)
# https://www.acmicpc.net/problem/18428

corridor = [['X' for i in range(10)] for j in range(10)]  # Basic data structure for corridor
possible = False
N = 0


def checkSurv(y, x):  # Check If Teacher can see students
    ty = y
    tx = x

    ty -= 1
    while ty >= 0:  # Upper
        if corridor[ty][tx] == 'S':  # Student Found
            return False
        if corridor[ty][tx] == 'O':  # Obstructed.
            break
        ty -= 1

    ty = y + 1

    while ty < N:  # Lower
        if corridor[ty][tx] == 'S':  # Student Found
            return False
        if corridor[ty][tx] == 'O':  # Obstructed.
            break
        ty += 1

    ty = y

    tx -= 1

    while tx >= 0:  # Left
        if corridor[ty][tx] == 'S':  # Student Found
            return False
        if corridor[ty][tx] == 'O':  # Obstructed.
            break
        tx -= 1

    tx = x + 1

    while tx < N:  # Right
        if corridor[ty][tx] == 'S':  # Student Found
            return False
        if corridor[ty][tx] == 'O':  # Obstructed.
            break
        tx += 1

    return True


def checkPossibility():  # Check if student is detectable
    global N

    for i in range(N):
        for j in range(N):
            if corridor[i][j] == 'T':
                if not checkSurv(i, j):  # Return false == Student is detectable
                    return False

    return True  # Return True == Student is undetectable


def findPossibility(obstacles, col, row):
    # Strategy: Just like normal enumeration problem, enumerate all possibilities using back-tracking.
    # Put the obstacle in the first place, recursively place obstacles in all possible place.
    # If possible case found, return immediately.
    global possible, N

    if obstacles <= 0:
        # Check possibility
        if checkPossibility():
            possible = True
        return

    while col < N:
        while row < N:
            if corridor[col][row] == 'X':
                corridor[col][row] = 'O'
                findPossibility(obstacles - 1, col, row)
                if possible:
                    return
                corridor[col][row] = 'X'
            row += 1
        row = 0
        col += 1

    return


if __name__ == '__main__':
    N = int(input())

    for i in range(N):
        line = list(input().split())
        for j in range(N):
            corridor[i][j] = line[j]

    findPossibility(3, 0, 0)

    print(f"{'YES' if possible else 'NO'}")
