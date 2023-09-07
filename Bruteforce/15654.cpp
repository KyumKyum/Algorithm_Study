// Algorithm Study
// Backjoon: N과 M (5) (15654)
// https://www.acmicpc.net/problem/15654

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//* Idea: BF + Back tracking

int N = 0, M = 0;
vector<int> input;
vector<bool> selected;
vector<int> print;

void backtrack(int left){
    if(left <= 0){
        for(int i = 0; i < print.size(); i++){
            cout << print[i] << " ";
        }
        cout << "\n";
        return;
    }

    for(int i = 0; i < input.size(); i++){
        if(selected[i]) continue;
        selected[i] = true;
        print.push_back(input[i]);
        backtrack(left-1);
        print.pop_back();
        selected[i] = false;
    }
    return;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> N >> M;

    input = vector<int>(N,0);
    selected = vector<bool>(N, false);

    for(int i = 0; i < N; i++){
        cin >> input[i];
    }

    sort(input.begin(), input.end());

    backtrack(M);
    return 0;
}

