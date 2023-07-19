// Algorithm Study
// Backjoon: 연속합  (1912)
// https://www.acmicpc.net/problem/1912

#include <iostream>
#include <iterator>
#include <algorithm>
#include <limits.h>

using namespace std;

int input[100001];
int DP[100001];
int N = 0;

int cons_sum(){
    int maximum = INT_MIN;
    // * Strategy: DP
    //* Keep track the maximum value
    //* DP[i] = max(DP[i-1] + input[i], input[i]
    //* return maximum. (maximum = max(DP[i], maximum)
    for(int i = 1; i <= N; i++){
        DP[i] = max(DP[i-1] + input[i], input[i]);
        maximum = max(DP[i], maximum);
    }

    return maximum;

}

int main(void){
    cin >> N;
    fill(begin(DP), end(DP), 0);

    for(int i = 1; i <= N; i++){
        cin >> input[i];
    }

    cout << cons_sum() <<endl;
    return 0;
}