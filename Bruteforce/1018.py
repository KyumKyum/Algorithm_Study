# Algorithm Study
# Backjoon: 채스판 다시 칠하기 (1018)
# https://www.acmicpc.net/problem/1018
# SILVER 4

# Will Define W = 1, B = -1
width, height = 0, 0
board = [[-1 for i in range(50)] for j in range(50)]
minNumToFill = -1


def checkIfCorrect(current, expected):  # Return True if current value is same with expected.
    if current == expected:
        return True

    return False


def findMinValToFill(widthStart, heightStart):
    global minNumToFill
    fillForward, fillInverse = 0, 0

    expectedColor = board[heightStart][widthStart]

    # Case 1: Fill Forward - Start from Right Upper Corner
    for hidx in range(8):
        for widx in range(8):
            if not checkIfCorrect(board[heightStart + hidx][widthStart + widx], expectedColor):
                fillForward += 1
            expectedColor *= -1  # expect opposite color in next cell.
        expectedColor *= -1
        # Not inverting expected color (Invert again), as the pattern should also be ensured vertically.

    # Case 2: Fill Inverse - Start from Left Lower Corner
    # Be careful with misunderstanding that counting inverse is duplication.
    for hidx in reversed(range(8)):
        for widx in range(8):
            if not checkIfCorrect(board[heightStart + hidx][widthStart + widx], expectedColor):
                fillInverse += 1
            expectedColor *= -1  # expect opposite color in next cell.
        expectedColor *= -1
        # Not inverting expected color (Invert again), as the pattern should also be ensured vertically.

    numToFill = fillForward if fillForward <= fillInverse else fillInverse

    if minNumToFill == -1 or minNumToFill > numToFill:
        minNumToFill = numToFill

    return


def fillChessBoard():
    # Strategy: Find all 8*8 chess board, check minimum number to fill
    widthStart, heightStart = 0, 0
    while heightStart + 8 <= height:  # find until reach to height limit.
        while widthStart + 8 <= width:  # find until reach to width limit.
            findMinValToFill(widthStart, heightStart)
            widthStart += 1
        widthStart = 0
        heightStart += 1

    return


if __name__ == '__main__':
    height, width = map(int, input().split())

    for i in range(height):
        lineInfo = list(input())
        for j in range(width):
            board[i][j] = 1 if lineInfo[j] == 'W' else -1

    fillChessBoard()
    print(f"{minNumToFill}")
