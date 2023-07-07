# Algorithm Study
# Backjoon: 행렬 곱셈 (10830)
# https://www.acmicpc.net/problem/10830

matrix = [[0 for i in range(5)] for j in range(5)]
ident = [[0 for i in range(5)] for j in range(5)]


def matrixMultiply(ma, mb, N):
    # Matrix multiply
    res = [[0 for _ in range(5)] for _ in range(5)]
    for i in range(N):
        for j in range(N):
            for k in range(N):
                res[i][j] += ma[i][k] * mb[k][j]
            res[i][j] = res[i][j] % 1000

    return res


def squareMatrix(N, B):
    if B == 0:
        return ident  # Return Identity

    if B % 2 != 0:
        return matrixMultiply(squareMatrix(N, B - 1), matrix, N)  # Odd Case
    else:  # Even Case
        divided = squareMatrix(N, int(B / 2))
        return matrixMultiply(divided, divided, N)


if __name__ == '__main__':
    for i in range(5):
        ident[i][i] = 1  # Define Identity

    N, B = map(int, input().split())

    for j in range(N):
        row = list(map(int, input().split()))
        for k in range(N):
            matrix[j][k] = row[k]

    res = squareMatrix(N, B)

    for i in range(N):
        for j in range(N):
            print(f"{res[i][j]}", end=" ")
        print("")
