# Algorithm Study
# Backjoon: 히스토그램(1725)
# https://www.acmicpc.net/problem/1725

height = []


def moveIndexLeft(left, squareHeight):
    if height[left - 1] < squareHeight:  # Update only if lesser value newly arrived.
        squareHeight = height[left - 1]
    left -= 1

    return left, squareHeight

def moveIndefRight(right, squareHeight):
    if height[right + 1] < squareHeight:
        squareHeight = height[right + 1]
    right += 1

    return right, squareHeight

def getBigSquare(start, end, size):
    # Strategy: Available square will be divided into 3 cases.
    # Case 1: Square of the left of the middle.
    # Case 2: Square of the right of the middle.
    # Case 3: Square crosses the middle.
    # Recursively get left and right side of the square, and get the bigger one.
    # And compare the bigger one to case 3, get the biggest one.
    # Computing for case 3 will be done by expanding to the square with higher size.
    # print(f"[{start, end, size}]")
    if start == end:  # Base case - Size of target square is 1.
        return height[start]

    # Get Case 1 and Case 2.
    leftSide = rightSide = 0

    mid = int(size / 2)
    if size % 2 == 0:
        leftSide = getBigSquare(start, end - mid, mid)
        rightSide = getBigSquare(start + mid, end, mid)
    else: # Odd Number
        leftSide = getBigSquare(start, end - (mid + 1), mid)
        rightSide = getBigSquare(start + mid, end, mid + 1)

    # Get Bigger one
    bigger = leftSide if leftSide >= rightSide else rightSide

    # Get square crosses the middle
    across = 0
    left, right = start + (mid - 1), start + mid
    squareHeight = height[left] if height[left] < height[right] else height[right]
    for i in range(2, size + 1):
        trial = i * squareHeight
        if trial > across:
            across = trial

        if right == end:
            left, squareHeight = moveIndexLeft(left, squareHeight)
        elif left == start:
            right, squareHeight = moveIndefRight(right, squareHeight)
        elif height[left - 1] >= height[right + 1]:
            left, squareHeight = moveIndexLeft(left, squareHeight)
        else:
            right, squareHeight = moveIndefRight(right, squareHeight)

    biggest = across if across >= bigger else bigger
    return biggest


if __name__ == '__main__':
    N = int(input())

    for i in range(N):
        height.append(int(input()))

    print(f"{getBigSquare(0, N - 1, N)}")



    # while True:
    #
    #     testcase = list(map(int, input().split()))
    #
    #     if testcase[0] == 0:  # Get Input until it gets 0 as an first input
    #         break
    #
    #     height = [h for h in testcase[1:testcase[0] + 1]]
    #     ans.append(getBigSquare(0, testcase[0] - 1, testcase[0]))

    # ansLen = len(ans)
    # for i in range(ansLen):
    #     print(f"{ans[i]}")
