# Algorithm Study
# ALGOSPOT: CLOCKSYNC
# https://www.algospot.com/judge/problem/read/CLOCKSYNC

switch = [
    [0, 1, 2],
    [3, 7, 9, 11],
    [4, 10, 14, 15],
    [0, 4, 5, 6, 7],
    [6, 7, 8, 10, 12],
    [0, 2, 14, 15],
    [3, 14, 15],
    [4, 5, 7, 14, 15],
    [1, 2, 3, 4, 5],
    [3, 4, 5, 9, 13]
]
clock = [0] * 16
testcase = [0] * 30
minPressVal = -1


def checkSync():
    for i in range(16):
        if clock[i] != 12:
            return False  # Return false if some clock left without sync
    return True  # Return true it all clocks are synchronized.


def press(switch_num):
    for tgt in switch[switch_num]:
        clock[tgt] += 3

        if clock[tgt] == 15:
            clock[tgt] = 3  # Return to 3


def clockSync(switch_num, pressed):
    global minPressVal

    if checkSync():
        if minPressVal == -1 or minPressVal > pressed:
            minPressVal = pressed

    if switch_num > 9:
        return  # Switch out of range

    # Strategy: All switches can be pressed without order,
    # All switches will be pressed maximum 3.
    # (4 cases in maximum: not pressed, pressed once, pressed twice, pressed three times)
    for i in range(4):
        clockSync(switch_num + 1, pressed)
        press(switch_num)
        pressed += 1


if __name__ == '__main__':
    testNum = int(input())
    for i in range(testNum):
        minPressVal = -1  # Reset
        clock = list(map(int, input().split()))
        clockSync(0, 0)
        testcase[i] = minPressVal

    for i in range(testNum):
        print(f"{testcase[i]}")
