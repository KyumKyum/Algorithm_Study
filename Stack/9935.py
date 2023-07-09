# Algorithm Study
# # Backjoon: 문자열 폭발 (9935)
# # https://www.acmicpc.net/problem/9935

stackBuffer = ['-']
explosive = ['-']


def explosion(idx, explosiveLen):
    # Check Explosion
    for i in range(explosiveLen - 1):  # Last Stack element was checked, already omitted.
        if stackBuffer[(idx - i)] != explosive[(explosiveLen - 2) - i]:
            # Consecution broken; explosion won't happen
            return False

    # Pop stack element (Explosion)
    for i in range(explosiveLen - 1):
        stackBuffer.pop(-1)

    return True


if __name__ == "__main__":
    # Strategy: Push each element.
    # If last element of explosion string pushed, check occurrence
    # If occurrence Happens, Pop as many as length of explosion string.
    buffer = str(input())
    exp = str(input())

    explosiveLen = len(exp)
    stackBuffer = ['-'] * len(buffer)
    explosive = ['-'] * explosiveLen

    idx = 0
    eidx = 0

    explosive = [c for c in exp]

    # Explosive String
    for c in buffer:
        # 1. Check if current c is component of explosive string
        if c in explosive:
            eidx = explosive.index(c) + 1
        else:
            eidx = 0  # Reset

        if eidx == explosiveLen:
            if explosion(idx - 1, explosiveLen):
                idx -= explosiveLen - 1
                continue

        stackBuffer[idx] = c
        idx += 1

    if idx == 0:
        print("FRULA", end="")
    else:
        for i in range(idx):
            print(stackBuffer[i], end="")
    print("")
