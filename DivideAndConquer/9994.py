# Algorithm Study
# Backjoon: Secret Code (9994)
# https://www.acmicpc.net/problem/9994

code = []
possibleCase = 0


def secretCode(start, size):
    global possibleCase
    # Strategy: Divide and Conquer
    # Find the secret code.
    # If code found, recursively find another code inside the divided code.
    # Recursively do it.

    # Way to find the code
    # Code length must be odd number (code + (code + 1))
    # Divide into code, code` (code` size == code + 1)
    # If Valid, recursively calls.
    # If Not, return immediately

    # Base Case: if size is less than 2 or in even number
    if size <= 2 or size % 2 == 0:
        return

    mid = int(size/2)  # Middle index, part of the code
    # Case 1: left part is a code
    leftCode = code[start : start + mid + 1]
    rightAppended = code[start + mid + 1 : start + size]

    # Case 2: right part is appended
    leftAppended = code[start : start + mid]
    rightCode = code[start + mid : start + size]

    if rightAppended == leftCode[0 : len(leftCode) - 1]:
        possibleCase += 1
        secretCode(start, mid + 1)  # This code could be made recursively
    #
    if rightAppended == leftCode[1 : len(leftCode)]:
        possibleCase += 1
        secretCode(start, mid + 1)  # This code could be made recursively
    #
    if leftAppended == rightCode[0 : len(rightCode) - 1]:
        possibleCase += 1
        secretCode(start + mid, mid + 1)  # This code could be made recursively
    #
    if leftAppended == rightCode[1 : len(rightCode)]:
        possibleCase += 1
        secretCode(start + mid, mid + 1)  # This code could be made recursively

    return


if __name__ == '__main__':
    code = [c for c in str(input())]
    size = len(code)
    secretCode(0, size)
    print(f"{possibleCase}")
