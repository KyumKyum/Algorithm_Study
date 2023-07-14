// Algorithm Study
// Backjoon: 전깃줄 (2565)
// https://www.acmicpc.net/problem/2565

#include <iostream>
#include <algorithm>
#include <iterator>
#include <map>

using namespace std;

map<int, int> line;
int dp[100];
int pole[100];

int line_cut(int N){
    //* Strategy: Based on https://yabmoons.tistory.com/572
    //* 와,..이게 최대 증가하는 부분 수열로 풀 수 있다고는 생각도 못했다...
    //* 1. Sort the input by left pole
        //* This is done by map (sort by key)
    //* 2. Find Longest increasing enumeration from the right pole.
    //* 3. N - len(LIS)

    int LIS = 0;

    for(int i = 1; i < N; i++){
        for (int j = 0; j < i; j++){
            if(pole[j] < pole[i]){
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        LIS = max(LIS, dp[i]);
    }

    return N - LIS;

}

int main(void){
    ios::sync_with_stdio(false);
    int N,a,b,idx = 0;
    fill(begin(dp), end(dp), 1);
    fill(begin(pole), end(pole), -1);

    cin >> N;
    for (int i = 0; i < N; i++){
        cin >> a >> b;
        line.insert(make_pair(a, b));
    }

    for(map<int,int>::iterator iter = line.begin(); iter != line.end(); iter++){
        pole[idx++] = iter->second;
    }

    cout << line_cut(N) << endl;

    return 0;
}