// Algorithm Study
// Backjoon: 찾기 (1786)
// https://www.acmicpc.net/problem/1786

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//* Idea: KMP
//* Practice KMP.

string T, P;

vector<int> getPartialMatch(const string& pattern) {
    //* Generate partial match array used for KMP.
    int size = pattern.length();
    vector<int> pi(size, 0);
    int start = 1, match = 0;

    while(start + match < size){ //* Find all matches
        if(pattern[start + match] == pattern[match]){
            //* If matches.
            match++;
            pi[start + match - 1] = match;
        }else{
            //* Find next starting point.
            //* Apply KMP in here too.
            if(match == 0){ //* No Matches:
                start++;
            }else{
                start += match - pi[match - 1]; //* Move to suffix matches with current prefix.
                match = pi[match - 1]; //* No need to check information already found.
            }
        }

    }

    return pi;
}

void KMP(void){
    int T_size = T.length();
    int P_size = P.length();
    int start = 0, match = 0;
    vector<int> ans;

    vector<int> pi = getPartialMatch(P);

    while(start + P_size <= T_size){
        if(match < P_size && T[start + match] == P[match]) { //* match can be overflow. Prevent Segfault.
            //* If matches
            match++;
            if(match == P_size){
                //* Found the matching sub string!
                ans.push_back(start + 1);
            }
        }else{
            //* Find next searching place
            if(match == 0){
                //* No match, start searching from next place.
                start++;
            }else{
                //* KMP: Find its pi value, and move it. (T's suffix => P's prefix)
                start += match - pi[match - 1];
                match = pi[match - 1]; //* No need to start the matching from start.
                //* As we know T's suffix => P's prefix, we can guarantee the same string of prefix and suffix.
            }
        }
    }

    int ans_size = ans.size();

    cout << ans_size << "\n";

    for(int i = 0; i < ans_size; i++){
        cout << ans[i] << " ";
    }
    cout << "\n";

    return;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    getline(cin, T);
    getline(cin, P);

    KMP();

    return 0;
}