# Algorithm Study
# Backjoon: Moo 게임 (5904)
# https://www.acmicpc.net/problem/5904

N = 0


def Moo(N, S, K):
    # Strategy: Recursively find its associated set.
    # If position associated to S, recursively find its position.
    # Else, Calculate K + 3 (m...o) and return it.

    midVal = K + 3  # number of moo...oo in the middle. (S + K+3 + S)
    segment = int((S - midVal) / 2)  # Segment of front/behind of midval.

    if segment < N <= segment + midVal:  # If It is middle of the value,
        if N == segment + 1:  # If N is the first value of segment
            return 'm'
        else:
            return 'o'
    else:
        newN = int(N % (segment + midVal))
        # Get position value after mid value (S(2) -> pos 1 == pos 16 (first element of S(k-1))
        return Moo(newN, segment, K - 1)


if __name__ == "__main__":
    N = int(input())
    S, K = 3, 0  # Init value 3 ("moo")

    while N > S:  # If required position is bigger than current enumeration,
        K += 1
        S = 2 * S + K + 3  # S(k-1) + m o(*k+2) + S(k-1)

    print(f"{Moo(N, S, K)}")
