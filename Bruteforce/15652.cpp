// Algorithm Study
// Backjoon: N과 M (4) (15652)
// https://www.acmicpc.net/problem/15652

#include <iostream>
#include <vector>
using namespace std;

int N, M = 0;
vector<int> permutation;

void solve(int start, int left){
    if(left <= 0){
        for(int i = 0; i < M; i++){
            cout << permutation[i] << " ";
        }

        cout << "\n";
        return;
    }
    for(int i = start; i <= N; i++){
        permutation.push_back(i);
        solve(i, left - 1);
        permutation.pop_back();
    }
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;

    solve(1, M);
    return 0;
}
