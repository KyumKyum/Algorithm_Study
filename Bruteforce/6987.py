# Algorithm Study
# Backjoon: 월드컵 (6987)
# https://www.acmicpc.net/problem/6987
import copy

# Enumerate All Possible Cases
rounds = [(0, 1), (0, 2), (0, 3), (0, 4), (0, 5),
          (1, 2), (1, 3), (1, 4), (1, 5),
          (2, 3), (2, 4), (2, 5),
          (3, 4), (3, 5),
          (4, 5)]
result = [[0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0]]
win = [0, 0, 0, 0, 0, 0]
tie = [0, 0, 0, 0, 0, 0]
lose = [0, 0, 0, 0, 0, 0]

testcase = [0] * 4
possible = False


def nextRound(round):
    # Strategy: Try All Possible 3 cases: win, lose, tie
    # Order is not important. No require loop to get all enumeration
    global possible

    if round >= 15:  # All Game Set
        # Check if this case is valid.

        for i in range(6):
            if result[i][0] != win[i] or result[i][1] != tie[i] or result[i][2] != lose[i]:
                possible = False  # Only possible if all case is right
                return

        possible = True
        return

    team = rounds[round]
    ta, tb = team[0], team[1]
    # Team A Win (Team B Lose)
    win[ta] += 1
    lose[tb] += 1
    if win[ta] <= result[ta][0] and lose[tb] <= result[tb][2]:  # Search more if current case is possible
        nextRound(round + 1)
        if possible:
            return
    win[ta] -= 1
    lose[tb] -= 1

    # Tie
    tie[ta] += 1
    tie[tb] += 1
    if tie[ta] <= result[ta][1] and tie[tb] <= result[tb][1]:  # Search more if current case is possible
        nextRound(round + 1)
        if possible:
            return
    tie[ta] -= 1
    tie[tb] -= 1

    # Team B Win (Team A Lose)
    win[tb] += 1
    lose[ta] += 1
    if win[tb] <= result[tb][0] and lose[ta] <= result[ta][2]:  # Search more if current case is possible
        nextRound(round + 1)
        if possible:
            return
    win[tb] -= 1
    lose[ta] -= 1

    return


if __name__ == '__main__':
    for i in range(4):
        case = list(map(int, input().split()))
        for j in range(6):
            for k in range(3):
                result[j][k] = case[(j * 3) + k]

        #Preprocess
        WIN, LOSE, TIE = 0, 0, 0
        verified = True
        for team in range(6):
            WIN += result[team][0]
            TIE += result[team][1]
            LOSE += result[team][2]
            if result[team][0] + result[team][1] + result[team][2] != 5:
                testcase[i] = 0
                verified = False
                break

        if WIN + LOSE + TIE != 30:
            testcase[i] = 0
            verified = False

        if not verified:
            continue

        nextRound(0)
        testcase[i] = 1 if possible else 0
        possible = False
        win = [0, 0, 0, 0, 0, 0]
        tie = [0, 0, 0, 0, 0, 0]
        lose = [0, 0, 0, 0, 0, 0]

    for i in range(4):
        print(f"{testcase[i]}", end=" ")
    print("")
