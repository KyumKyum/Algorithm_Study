//
// Created by Kyumin's Dev on 2023/07/12.
//
/*# Algorithm Study
# Backjoon: 박스 채우기 (1493)
# https://www.acmicpc.net/problem/1493
 */
#include <iostream>
using namespace std;

int cubes[20] = {0};
bool possible = false;
int required = 0;

void fillUp(int l, int w, int h) {
    //* Strategy: Divide and Conquer
    // Greedy Approach: Fill Up With the biggest cube first.
    if (l <= 0 || w <= 0 || h <= 0){
        return;  // All Space are filled.
    }

    int edge = 0;
    possible = false;

    for (int i = 19; i >= 0; i--){
        // Find Biggest Cube First.
        if (cubes[i] == 0)
            continue;

        //* Edge Computation: Bit Shift
        //* More Faster than 3 multiplication
        edge = 1 << i;
        if (l >= edge && w >= edge && h >= edge){
            possible = true;
            cubes[i] -= 1;
            required += 1;
            break;
        }
    }

    if (!possible) {
        return; //* No more cube left.
    }

    /*
     * Divide Strategy: Divide into 3 squares
    Square 1: width based -> edge, width - edge, edge
    Square 2: remaining after Square 1 -> length - edge, width, edge
    Square 3: remaining after Square 1 & 2 => Upper part, length, width, height - edge
     */
    fillUp(edge, w - edge, edge); // Square 1
    fillUp(l - edge, w, edge);
    fillUp(l, w, h-edge);
}

int main(){
    long length, width, height = 0;
    int N, idx, num = 0;
    cin >> length >> width >> height;
    cin >> N;

    for(int i = 0; i < N; i++){
        cin >> idx >> num;
        cubes[idx] = num;
    }

    fillUp(length, width, height);

    if (!possible){
        cout << "-1"<< endl;
    }else{
        cout << required << endl;
    }

    return 0;
}