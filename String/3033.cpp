// Algorithm Study
// Backjoon: 가장 긴 문자열 (3033)
// https://www.acmicpc.net/problem/3033

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
//* Idea: Suffix Array & LCP Array.
//* LCP array will contain Longest common prefix, which is happens at least 2 suffixes.
//* Suffixes will be prefixes of all substring.
//* Which means LCP for suffix == LCP for substring.
//* Print the highest number of lcp.

struct Cmp{
    vector<int>& group;
    int t;
    Cmp(vector<int>& _group, int _t): group(_group), t(_t) { //* Constructor: init group and t by given parameter.
        this->group = _group;
        this->t = _t;
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

int getLongestLCP(string s, vector<int> suffix_array){
    int size = suffix_array.size();
    int longestLCP = 0;
    vector<int> position(size, 0);

    for(int i = 0; i < size; i++){
        position[suffix_array[i]] = i;
    }

    int lcp_len = 0;

    for(int start = 0; start < size; start++){
        int suf_cur_pos = position[start];
        //* Position for current suffix; string[start: size - 1]
        //* Will get sorted location of string[start : size - 1]
        if(suf_cur_pos == 0) {
            //* Suffix located at last index cannot be compared.
            //* Skip, because it will have no LCP.
            continue;
        }

        int suf_pos_located_prev = suffix_array[suf_cur_pos - 1];
        //* Position for suffix located previous to current suffix.
        //* suffix_array[] == contains starting index of given position.

        //compare
        while( (start + lcp_len < size) && (suf_pos_located_prev + lcp_len < size) ){
            if(s[start + lcp_len] != s[suf_pos_located_prev + lcp_len]){
                break; //* Different Character!
            }
            lcp_len++;
        }

        //* compare and get the longest lcp.
        longestLCP = max(longestLCP, lcp_len);

        if(lcp_len > 0){
            lcp_len--; //* If lcp_len is longer than 1, lcp for next position will be lcp_len - 1.
        }
    }

    return longestLCP;
}


int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int L = 0;
    string s;
    cin >> L;
    cin >> s;

    vector<int> suffix_array = getSuffixArray(s);

    cout <<  getLongestLCP(s, suffix_array) << "\n";

    return 0;
}

