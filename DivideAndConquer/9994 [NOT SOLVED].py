# Algorithm Study
# Backjoon: Secret Code (9994)
# https://www.acmicpc.net/problem/9994

code = []
possibleCase = 0


def checkCode(start, mid, size):
    global possibleCase
    for i in range(size):
        # print(f"{code}, {start, mid, size} {start + i} vs {start + mid + 1 + i}")
        if code[start + i] != code[mid + i]:
            return  # Front is not a code

    possibleCase += 1
    return


def secretCode(start, end, size):
    # Strategy: Divide and Conquer
    # Find the secret code.
    # If code found, recursively find another code inside the divided code.
    # Recursively do it.

    # Way to find the code
    # Code length must be odd number (code + (code + 1))
    # Divide into code, code` (code` size == code + 1)
    # If Valid, recursively calls.
    # If Not, return immediately

    # Base Case: start == end -> 1 code
    if start == end or start + 1 == end:  # Not available Code
        return
    elif size % 2 == 0:
        return  # Length should be in odd number

    mid = int(size/2)


    # Case 1: front component is a code. ((code + 1) + code)
    secretCode(start, start + mid, mid + 1)
    checkCode(start, start + mid + 1, mid) # Remove Last Character
    checkCode(start + 1, start + mid + 1, mid) # Remove First Character
    # Case 2: rear component is a code (code + (code + 1))
    secretCode(start + mid, end, mid + 1)
    checkCode(start, start + mid, mid) # Remove Last Character
    checkCode(start, start + mid + 1, mid) # Remove First Character
    return


if __name__ == '__main__':
    code = [c for c in str(input())]
    size = len(code)
    secretCode(0, size - 1, size)
    print(f"{possibleCase}")
