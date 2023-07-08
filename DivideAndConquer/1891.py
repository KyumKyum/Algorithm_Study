# Algorithm Study
# Backjoon: 사분 (1891)
# https://www.acmicpc.net/problem/1891

pos = []
mvHorizontal = {1:2, 2:1, 3:4, 4:3}
mvVertical = {1:4, 2:3, 3:2, 4:1}


def moveHorizontal(idx, x):
    if idx < 0:
        if x == 0:
            return 0
        else:  # Error Case: Out of bound
            return -1

    tgt = pos[idx]
    leap = 0

    if x > 0: # Move Right
        if tgt == 1 or tgt == 4:  # Leap Happens in odd number
            leap = int((x + 1) / 2)
        else:
            leap = int(x / 2)
    elif x < 0:  # Move Left
        if tgt == 2 or tgt == 3:
            leap = -int((abs(x - 1)) / 2)
        else:
            leap = -int((abs(x))/2)

    # If x is even, the position itself wouldn't change
    if abs(x) % 2 == 1:
        pos[idx] = mvHorizontal.get(tgt)

    return moveHorizontal(idx - 1, leap)


def moveVertical(idx, y):
    if idx < 0:  # Error Case: Out of bound
        if y == 0:
            return 0
        else:
            return -1

    tgt = pos[idx]
    leap = 0

    if y > 0:  # Move Up
        if tgt == 1 or tgt == 2:  # Leap Happens in odd number
            leap = int((y + 1) / 2)
        else:
            leap = int(y / 2)
    elif y < 0:  # Move Down
        if tgt == 3 or tgt == 4:
            leap = -int((abs(y - 1)) / 2)
        else:
            leap = -int((abs(y)) / 2)

    # If x is even, the position itself wouldn't change
    if abs(y) % 2 == 1:
        pos[idx] = mvVertical.get(tgt)

    return moveVertical(idx - 1, leap)


def quarter(idx, x, y):
    # Strategy: Divide to the least quarter, apply movement
    # If changes over the border happens, recursively apply it.
    if moveHorizontal(idx, x) == -1 or moveVertical(idx, y) == -1:
        return -1

    return 0


if __name__ == '__main__':
    num, d = map(int, input().split())

    pos = [int(x) for x in str(d)]

    x, y = map(int, input().split())
    test = -6
    if quarter(num - 1, x, y) == -1:  # give the last element of the position
        print("-1")  # Not Possible Case
    else:
        for i in range(num):
            print(f"{pos[i]}", end="")
        print("")

