// Algorithm Study
// Backjoon: N과 M (9) (15663)
// https://www.acmicpc.net/problem/15654

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

//* Idea: BF + Back tracking
//* Remove duplication via set.

int N = 0, M = 0;
vector<int> input;
vector<bool> selected;
vector<int> print;
vector<string> ans;
set<string> cache;

void backtrack(int left){
    if(left <= 0){
        string str;
        for(int i = 0; i < print.size(); i++){
           str += to_string(print[i]).append(" ");
        }

        if(cache.find(str) == cache.end()){
            //* New!
            ans.push_back(str);
            cache.insert(str);
        }

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

    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << "\n";
    }

    return 0;
}

