// Algorithm Study
// Backjoon: 속타는 저녁 메뉴 (11585)
// https://www.acmicpc.net/problem/11585

#include <iostream>
#include <vector>

using namespace std;
//* Circular shift using KMP
//* It must be executed within O(N)

//* Circular Shift => KMP with two consecurive original string.
    //* find BAABAA from AABAAB by circular shift => KMP BAABAA to AABAABAABAAB => 2

vector<char> target;
vector<char> given;
int N = 0;

vector<int> getPartialMatch(vector<char> pattern){
    int size = pattern.size();
    vector<int> pi(size, 0 );
    //* Prefix: Points prefix's end.
    //* Suffix: Points suffix's end
    int prefix = 0;
    for(int suffix = 1; suffix < size; suffix++){
        //* If current prefix and suffix didn't match
        while(prefix > 0 && pattern[prefix] != pattern[suffix]){
            //* Only suffix will increase.
            //* Move Prefix : Move prefix to pi[lastly matched == prefix - 1] (Current prefix didn't match!)
                //* Move prefix to prefix of lastly matched string's prefix's last position.
            prefix = pi[prefix - 1];
        }
        if(pattern[prefix] == pattern[suffix]){
            //* If current prefix and suffix matches.
            //* Increase Both.
            prefix++;
            pi[suffix] = prefix;
        }
    }

    return pi;
}

int shift(void){
    int matches = 0, found = 0;
    //* Do KMP
    int tgt_size = target.size(), given_size = given.size();
    vector<int> pi = getPartialMatch(given);

    for(int i = 0; i < tgt_size; i++){
        //* Iterate all strings in target.
        while (matches > 0 && target[i] != given[matches]){
            //* It didn't match
            //* move matches.
            matches = pi[matches - 1];
        }

        if(target[i] == given[matches]){
            matches++;
            if(matches == given_size){
                //* Found!
                found++;
                matches = pi[matches - 1];
            }
        }
    }

    return found;
}

int gcd(int a, int b){
    //* Great Common Divisor: Euclidean Algorithm
    return b ? gcd(b, a%b) : a;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);
    char input;

    cin >> N;

    for(int i = 0; i < N; i++){
        cin >> input;
        target.push_back(input);
    }

    //* Make it double.
    for(int i = 0; i < N - 1; i++){
        //* Except for the last character. (Remove duplication.)
        target.push_back(target[i]);
    }
    for(int i = 0; i < N; i++){
        cin >> input;
        given.push_back(input);
    }

    int found = shift();
    int divisor = gcd(N, found);

    cout << found/divisor << "/" << N/divisor <<"\n";

    return 0;
}
