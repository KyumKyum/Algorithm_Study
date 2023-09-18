// Algorithm Study
// Backjoon: Dance Dance Revolution (2342)
// https://www.acmicpc.net/problem/2342

#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstring>

using namespace std;

int step[100050];
int dp[100050][5][5];

int calculate_energy(int cur, int next){
    if(cur==next) return 1;
    else if(cur == 0) return 2; //* Start from the middle.
    else if((next != 0) && cur - next == -2 || cur - next == 2) return 4;
    return 3;
}

int DDR(int left, int right, int round){
    int &ret = dp[round][left][right];
    if(ret != -1) return ret;
    int next_step = step[round];
    if(next_step == 0) return 0; //* End of the step

    //* RULE: So same foot in the same area.
    if(right == next_step) ret = calculate_energy(right, next_step) + DDR(left, next_step, round+1);
    else if(left == next_step) ret = calculate_energy(left, next_step) + DDR(next_step, right, round+1);

    //* Take the minimum cost.
    return ret = min(
            calculate_energy(right, next_step) + DDR(left, next_step, round+1),
            calculate_energy(left, next_step) + DDR(next_step, right, round+1)
    );
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    fill(begin(step), end(step), 0);
    memset(dp, -1, sizeof(dp));

    int len = 0;
    while(true){
        cin >> step[len++];
        if(step[len-1] == 0) break;
    }

    cout << DDR(0, 0, 0) << "\n";

    return 0;
}
