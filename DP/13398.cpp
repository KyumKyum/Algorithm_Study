// Algorithm Study
// Backjoon: 연속합 2  (13398)
// https://www.acmicpc.net/problem/13398

#include <iostream>
#include <cstring>
#include <limits.h>

using namespace std;

int input[100000];
int DP[100000][2];
int N = 0;

int cons_sum(){
    int maximum = INT_MIN;

    //* Strategy: 1921
    //* DP[-][0] = Never been removed.
    //* DP[-][1] = Element Removed
    //* Calculate Both Cases
    //* DP[-][0] ==> Calculate same as BOJ 1921
    //* DP[-][1] ==> 2 cases
        //* 1. The Element Already had been removed (DP[i-1][1] + input[i])
        //* 2. Current element will be removed (DP[i-1][0])
    //* Save the bigger value.

    maximum = DP[0][0] = DP[0][1] = input[0]; //* Init. (If input length is 1)

    for(int i = 1; i < N; i++){
        DP[i][0] = max(DP[i-1][0] + input[i], input[i]);
        DP[i][1] = max(DP[i-1][1] + input[i] , DP[i-1][0]);
        maximum = max(DP[i][1], max(DP[i][0], maximum));
    }

    return maximum;

}

int main(void){
    cin >> N;
    memset(DP, 0, sizeof(DP));

    for(int i = 0; i < N; i++){
        cin >> input[i];
    }

    cout << cons_sum() <<endl;
    return 0;
}
