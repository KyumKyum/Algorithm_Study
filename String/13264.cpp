// Algorithm Study
// Backjoon: 접미사 배열2 (13264)
// https://www.acmicpc.net/problem/13264

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
//* Suffix Array Tutorial. => Mamber-Myers

struct Cmp{
    vector<int>& group;
    int t;
    Cmp(vector<int>& _group, int _t): group(_group), t(_t) {
        group = _group;
        t = _t;
    }

    bool operator() (int a, int b){
        //* Diff first letter: return group with higher order
        if(group[a] != group[b]) return group[a] < group[b];
        //* Same First letter,: compare first t. (use information from already sorted.)
        return group[a+t] < group[b+t];
    }
};

vector<int> getSuffixArray(string s){
    int size = s.length(), t = 1;
    vector<int> group(size + 1);
    //* Group: suffix group sorted based on t'th letter.
    vector<int> suffix_array(size); //* suffix array.

    for(int i = 0; i < size; i++){
        group[i] = s[i];
        suffix_array[i] = i;
    }
    group[size] = -1; //* Prevent overflow.

    while(t < size){
        //* Search lgn.
        Cmp comparator(group, t);
        sort(suffix_array.begin(), suffix_array.end(), comparator);

        t *= 2;
        if(t >= size) break; //* Completed!

        //* Make group;
        vector<int> group_new(size + 1);
        group_new[size] = -1;
        group_new[suffix_array[0]] = 0; //* Set first.

        for(int i = 1; i < size; i++){
            if(comparator(suffix_array[i-1], suffix_array[i])){
                //* if they are in different group.
                group_new[suffix_array[i]] = group_new[suffix_array[i-1]] + 1;
            }else{
                //* They are in the same group.
                group_new[suffix_array[i]] = group_new[suffix_array[i-1]];
            }
        }

        group = group_new;
    }

    return suffix_array;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s;
    cin >> s;

    vector<int> suffix_array = getSuffixArray(s);

    int size = suffix_array.size();
    for(int i = 0; i < size; i++){
        cout << suffix_array[i] << "\n";
    }

    return 0;
}
