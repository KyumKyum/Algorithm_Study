// Algorithm Study
// Backjoon: 가장 긴 증가하는 부분 수열 (11053)
// https://www.acmicpc.net/problem/11053

#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

int arr[1000];
int dp[1000];

int findLongest(int N){
    //* Strategy: DP
    //* dp[i] => Length of longest increasing enumeration until arr[i]
    //* Find all value bigger than next index,
    //* dp[i] = max(dp[i], dp[j] + 1) (Add 1 to the longest increasing enumeration)

    int ans = 1; //* At least LIE will be 1.

    for(int i = 1; i < N; i++){
        for (int j = 0; j < i; j++){
            if(arr[j] < arr[i]){
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        ans = max(ans, dp[i]);
    }

    return ans;

}

int main(void){
    ios::sync_with_stdio(false);
    int N, input = 0;
    fill(begin(dp), end(dp), 1);

    cin >> N;


    for(int i = 0; i < N; i++){
        cin >> input;
        arr[i] = input;
    }

    cout << findLongest(N) << endl;

    return 0;
}
