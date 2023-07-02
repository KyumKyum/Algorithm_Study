# Algorithm Study
# Backjoon: Blackjack (2789)
# https://www.acmicpc.net/problem/2798

opt, N, M = -1, 0, 0
# N: Number of card
# M: Target number
card = []
used = [False] * 100
# def find():
# Strategy: recursively call find(), update variable opt if result value is bigger than opt, but not exceed M.


def findFirstNotPicked(picked_last):
    # Always find bigger index than current - Remove duplication
    while picked_last < N:
        if not used[picked_last]:
            return picked_last
        picked_last += 1

    return -1


def blackjack(picked_left, sum, picked_last):
    global opt

    if sum > M:  # Base case: If the value is already bigger than M
        return

    if picked_left <= 0:  # Base case: Picked all cards required
        if opt < sum:  # If summation is bigger than opt, less than M
            opt = sum  # Update
        return

    chosen = findFirstNotPicked(picked_last)

    if chosen == -1:  # Base case: no cards are left to choose
        return

    while chosen < N:
        used[chosen] = True  # Used
        sum += card[chosen]  # Add value
        blackjack(picked_left - 1, sum, chosen)
        used[chosen] = False  # Release
        sum -= card[chosen]  # remove value, try another.
        chosen += 1

    return


if __name__ == '__main__':
    N, M = map(int, input().split())
    card = list(map(int, input().split()))
    blackjack(3, 0, 0)

    print(f"{opt}")
