# Algorithm Study
# Backjoon: 별 찍기 - 10 (2447)
# https://www.acmicpc.net/problem/2447

def star(i, j, N):
    # Strategy: Divide and Conquer:
    # Base case: 3*3 case
        # Print blank in the middle. -> i%3 == 1 and j%3 == 1
    # Recursive Strategy: If is not blank, print * only if N is 1, else, recursion.
        # Recursion to N/3: Solve problem in 3*3 base case.

    if int(i/N) % 3 == 1 and int(j/N) % 3 == 1:
        # Print Blank in the middle.
        print(" ", end="")
        return
    else:
        if int(N/3) == 0: # If Less than 1
            print("*", end="")
            return
        else:
            star(i,j,N/3)


if __name__ == "__main__":
    N = int(input())

    for i in range(N):
        for j in range(N):
            star(i, j, N)
        print("")

