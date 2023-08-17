// Algorithm Study
// Backjoon: Suffix Array (9284)
// https://www.acmicpc.net/problem/9284

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
//* Suffix Array & LCP Array Tutorial. => Mamber-Myers & Kasai

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

vector<int> getLCPArray(string s, vector<int> suffix_array){
    //* Kasai's Algorithm
    //* Facts:
        //* 1. In the sorted array of suffix, suffix will have longer LCP with suffix located nearby.
        //* 2. In the sorted array of suffix, lcp(suffix_array[i - 1], suffix_array[i]) has more than 1 lcp, position[suffix_array[i-1]+1)] will be smaller than position[suffix_array[i]+1)
            //* ana (suffix_array[1] = 3) vs anana (suffix_array[2] = 1) => lcp == 3
            //* position[3+1] == 4 (na)  < position[(1+1) => 2] == 5 ==> 4 < 5
        //* 3. In the sorted array of suffix, lcp(suffix_array[i-1] + 1, suffix_array[i] + 1) == lcp(suffix_array[i-1], suffix_array[i]) - 1
            //* lcp(suffix_array[1], suffix_array[2]) == ana vs anana => ana (lcp == 3)
            //* lcp(position[4], position[2]) == na (ana -> na) vs nana (anana -> nana) => na (lcp == 2)

    int size = suffix_array.size();
    vector<int> position(size, 0); //* position == Inverted array of suffix array; Return its dictionary order by its starting index.
    vector<int> lcp_array(size, 0);

    for(int i = 0; i < size; i++){
        position[suffix_array[i]] = i;
    }

    //* Idea:
        //* If lcp with i-1, i is more than 1, the lcp for i, i+1 will have i-1 lcp.

    int lcp_len = 0;

    for(int start = 0; start < size; start++){
        //* Will Sweep all string index, 0 ~ size-1.
        int suf_cur_pos = position[start];
        //* Position for current suffix; string[start: size - 1]
        //* Will get sorted location of string[start : size - 1]
        if(suf_cur_pos == 0) {
            //* Suffix located at last index cannot be compared.
            lcp_array[suf_cur_pos] = -1;
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

        //* Record lcp for current position.
        lcp_array[suf_cur_pos] = lcp_len;

        if(lcp_len > 0){
            lcp_len--; //* If lcp_len is longer than 1, lcp for next position will be lcp_len - 1.
        }
    }

    return lcp_array;

}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s;
    cin >> s;

    vector<int> suffix_array = getSuffixArray(s);
    vector<int> lcp_array = getLCPArray(s, suffix_array);

    int size = suffix_array.size();

    for(int i = 0; i < size; i++){
        cout << suffix_array[i] + 1<< " ";
    }
    cout << "\n";

    for(int i = 0; i < size; i++){
        if(lcp_array[i] == -1) cout << "x ";
        else cout << lcp_array[i] << " ";
    }
    cout << "\n";

    return 0;
}
