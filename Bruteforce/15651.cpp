// Algorithm Study
// Backjoon: N과 M (3) (15651)
// https://www.acmicpc.net/problem/15651

#include <iostream>
#include <vector>
using namespace std;

int N, M = 0;
vector<int> permutation;

void solve(int left){
    if(left <= 0){
        for(int i = 0; i < M; i++){
            cout << permutation[i] << " ";
        }

        cout << "\n";
        return;
    }
    for(int i = 1; i <= N; i++){
        permutation.push_back(i);
        solve( left - 1);
        permutation.pop_back();
    }
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;

    solve( M);
    return 0;

}
