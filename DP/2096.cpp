// Algorithm Study
// Backjoon: 내려가기 (2096)
// https://www.acmicpc.net/problem/2096

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int sw_max[3]; //* Must be int (short => overflow)
int sw_min[3];
int N = 0;

void go_down(){
    //* Strategy: Sliding Window + DP
    //* Resolve possible maximum, minimum value for each level (sliding window)
    int l, m ,r = 0;
    int temp_l, temp_m, temp_r = 0;
    cin >> N;

    cin >> l >> m >> r;
    sw_max[0] = sw_min[0] = l;
    sw_max[1] = sw_min[1] = m;
    sw_max[2] = sw_min[2] = r;

    for(int i = 1; i < N; i++){
        cin >> l >> m >> r;
        //* Maximum: try all possible tile, and record the maximum
        temp_l = max(sw_max[0], sw_max[1]) + l;
        temp_m = max(max(sw_max[0], sw_max[1]), sw_max[2]) + m;
        temp_r = max(sw_max[1], sw_max[2]) + r;

        sw_max[0] = temp_l;
        sw_max[1] = temp_m;
        sw_max[2] = temp_r;

        //* Minimum: try all possible tile, and record the minimum
        temp_l = min(sw_min[0] , sw_min[1]) + l;
        temp_m = min(min(sw_min[0], sw_min[1]), sw_min[2]) + m;
        temp_r = min(sw_min[1], sw_min[2]) + r;

        sw_min[0] = temp_l;
        sw_min[1] = temp_m;
        sw_min[2] = temp_r;
    }
}

int main(void){
    memset(sw_max, 0, sizeof(sw_max));
    memset(sw_min, 0, sizeof(sw_min));

    go_down();

    int maximum = max(max(sw_max[0], sw_max[1]), sw_max[2]);
    int minimum = min(min(sw_min[0], sw_min[1]), sw_min[2]);

    cout << maximum << " " << minimum << endl;
    return 0;
}
