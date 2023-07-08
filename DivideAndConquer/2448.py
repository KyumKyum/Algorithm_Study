# Algorithm Study
# Backjoon: 별 찍기 - 11 (2448)
# https://www.acmicpc.net/problem/2448

N = 0
starBoard = [[' ']]


def star(i, j, N):
    if N == 3: # Base Case
        starBoard[i][j] = '*'
        starBoard[i+1][j-1] = '*'
        starBoard[i+1][j+1] = '*'
        for weight in range(-2, 3):
            starBoard[i+2][j+weight] = '*'
    else:
        # Strategy: Divide into 3 problems
        # upper triangle
        # left triangle
        # right triangle
        subStar = int(N/2)
        star(i,j,subStar)
        star(i+subStar, j - subStar, subStar)
        star(i+subStar, j+subStar, subStar)
        return


if __name__ == '__main__':
    N = int(input())

    totalWidth = 2 * N - 1
    starBoard = [[' ' for _ in range(totalWidth)] for _ in range(N)]
    star(0, N-1, N) # Start from the middle

    for i in range(N):
        for j in range(totalWidth):
            print(f"{starBoard[i][j]}", end="")
        print("")

