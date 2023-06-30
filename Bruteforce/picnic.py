# Algorithm Study
# ALGOSPOT: PICNIC
# https://www.algospot.com/judge/problem/read/PICNIC

relationship = [[False for i in range(10)] for j in range(10)]  # 2D array to save relationship information
res = [0] * 50  # Number of testcase

def findFirst(taken):
    for i in range(len(taken)):
        if not taken[i]:
            return i

    return -1  # All taken; base case


def checkIfValidRel():
    for i in range(10):
        for j in range(10):
            if relationship[i][j]:
                return True

    return False  # All available friends are expended.


def findSet(taken):
    # Search Set. If there is a friend, put it and check if array is full.
    # Start from the first set.

    target = findFirst(taken)

    if target == -1:
        # Base Case: target == -1; end of searching
        return 1

    if not checkIfValidRel():
        # Base Case: All available set are used, but still some element are not taken.
        # This set cannot be made.
        return 0

    ans = 0

    partner = target + 1  # Start from next element
    while partner < len(taken):
        if not taken[partner] and relationship[target][partner]:
            # If current target and partner is not taken and friend, make them as a friend.
            taken[target] = taken[partner] = True  # Taken
            relationship[target][partner] = relationship[partner][target] = False  # Used Relationship
            ans += findSet(taken)
            taken[target] = taken[partner] = False  # Find another set.
            relationship[target][partner] = relationship[partner][target] = True  # Relinquish relationship

        partner += 1

    return ans


def picnic():
    num, friend = map(int, input().split())  # First input: total number and friend number
    friendSet = list(map(int, input().split()))
    head = 0

    while head < friend:  # Second input: friend set info.
        a, b = friendSet[2 * head], friendSet[2 * head + 1]
        relationship[a][b] = relationship[b][a] = True  # Set Relationship
        head += 1

    taken = [False] * num
    ans = findSet(taken)

    return ans


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    testcase = int(input())

    for i in range(testcase):
        relationship = [[False for i in range(10)] for j in range(10)]  # Reset
        res[i] = picnic()

    for idx in range(testcase):
        print(f"{res[idx]}")
