// Algorithm Study
// Backjoon: N과 M (2) (15650)
// https://www.acmicpc.net/problem/15650

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
        solve(i + 1, left - 1);
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
