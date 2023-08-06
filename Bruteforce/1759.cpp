// Algorithm Study
// Backjoon: 암호 만들기 (1759)
// https://www.acmicpc.net/problem/1759

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

//* Strategy: BF + Backtracking
//* Sort input by increasing order (using priority queue)
//* Backtrack and print all possibilities.

priority_queue<char, vector<char>, greater<char> > letters;
vector<char> combination;
vector<char> sorted_letters;
int L, C = 0;

bool check_vowel(char c){
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
        return true;
    }
    return false;
}

void make_combination(int left, int start, bool vowel_included, int consonant_num){
    if(left <= 0){
        if( vowel_included && (consonant_num >= 2)){
            //* Condition: At least 1 vowel and 2 consonant.
            for(int i = 0; i < L; i++){
                cout << combination[i];
            }
            cout << "\n";
        }
        return;
    }

    for(int i = start; i < C; i++){
        combination.push_back(sorted_letters[i]);
        if(check_vowel(sorted_letters[i])){
            make_combination(left - 1, i + 1, true, consonant_num); //* Indicate this set include vowel.
        }else{
            make_combination(left - 1, i + 1, vowel_included, consonant_num + 1);
        }
        combination.pop_back();
    }
    return;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);
    char input;
    cin >> L >> C;

    for(int i = 0; i < C; i++){
        cin >> input;
        letters.push(input);
    }

    while(!letters.empty()){
        sorted_letters.push_back(letters.top());
        letters.pop();
    }

    make_combination(L, 0, false, 0);

    return 0;
}