// Algorithm Study
// Backjoon: RGB 거리 (1149)
// https://www.acmicpc.net/problem/1149

#include <iostream>
#include <cstring>
#include <algorithm>
#include <limits.h>

using namespace std;

int N = 0;
int RGB[3][1000];
int cache[1000][3];
int min_cost = INT_MAX;

int RGB_street(int left, int fill, int cost){
    //* DP Strategy: cache[level][RGB index] <- will cache min value by selecting current color.
    int cost_below_level = INT_MAX;

    if(left <= 0){
        min_cost = min(min_cost, cost);
        return cost;
    }

    for(int i = 0; i < 3; i++){
        if(i == fill)
            continue;

        int& ret = cache[N-left][i];

        if(ret == -1){
            ret = RGB_street(left - 1, i, cost + RGB[i][N - left]) - cost;
            cost_below_level = min(cost_below_level, ret);
            //* Recursively try all value, except i.
        }else{
            //* Cached Value
            min_cost = min(min_cost, ret + cost);
            cost_below_level = min(cost_below_level, ret);
        }


    }
    return cost_below_level + cost;
}

int main(void){
    memset(RGB, -1, sizeof(RGB));
    memset(cache, -1, sizeof(cache));
    int r,g,b = 0;

    cin >> N;

    for(int i = 0; i < N; i++){
        cin >> r >> g >> b;
        RGB[0][i] = r;
        RGB[1][i] = g;
        RGB[2][i] = b;
    }

    RGB_street(N,-1, 0);

    cout << min_cost << endl;
    return 0;
}