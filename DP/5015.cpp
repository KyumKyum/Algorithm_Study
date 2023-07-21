// Algorithm Study
// Backjoon: ls (5015)
// https://www.acmicpc.net/problem/5015
#include <iostream>
#include <cstring>
#include <string>
#include <iterator>
#include <vector>

using namespace std;

string pattern;
int N = 0;
char cache[111][111];
vector<string> ans;
vector<string> list;

bool ls(int pSize, int sSize, string& dir){
    //* start: word start
    //* size: pattern size
    //* Strategy: DP
    char&ret = cache[pSize][sSize];
    if(ret != -1){
        return ret;
    }

    //* If pattern ended, string need to be ended
    if(pSize >= pattern.length() && sSize == dir.length()){
        return ret = 1;
    }

    //* Check if matched
    if(pSize < pattern.length() && sSize < dir.length()
        && dir[sSize] == pattern[pSize]){
        return ret = ls(pSize + 1, sSize + 1, dir);
    }

    //* If '*', match 0 ~ N letters.
    if(pattern[pSize] == '*'){
        if(ls(pSize + 1, sSize, dir) || (sSize < dir.length() && ls(pSize, sSize + 1, dir))){
            return ret = 1;
        }
    }
    //* All other cases are false.
    return ret = 0;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    fill(begin(pattern), end(pattern), ' ');
    fill(begin(ans), end(ans),(char*)0);

    memset(cache, -1, sizeof(cache));
    cin >> pattern;
    cin >> N ;
    list.resize(N);
    for(int i = 0; i < N; i++){
        cin >> list[i];
        if(ls(0,0, list[i]) == 1){
            ans.push_back(list[i]);
        }
        memset(cache, -1, sizeof(cache));
    }

    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << "\n";
    }

    return 0;
}


