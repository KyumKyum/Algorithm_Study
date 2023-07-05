# Algorithm Study
# Backjoon: 시계 맞추기 (27532)
# https://www.acmicpc.net/problem/27532
# GOLD 5

clock = [0] * 1500
clockNum = 0
minVal = -1


def splitClock(clockVal):
    hr, minute = map(int, clockVal.split(":"))
    return hr % 12, minute


def timeToMin(clockVal):
    hr, minute = splitClock(clockVal)
    return ((hr * 60) + minute) % 720


def clockGuess():
    global minVal
    R = 1

    while R <= 720:
        for i in range(clockNum):
            clock[i] = (clock[i] + (clockNum - (i + 1))) % 720

        clockNumForCurrentCase = len(set(clock[:clockNum]))

        if minVal > clockNumForCurrentCase:
            minVal = clockNumForCurrentCase

        R += 1
    return


if __name__ == '__main__':
    clockNum = int(input())
    minVal = clockNum

    for i in range(clockNum):
        clock[i] = timeToMin(input())

    clockGuess()

    print(f"{minVal}")
