// Algorithm Study
// Backjoon: 시저 암호 (1893)
// https://www.acmicpc.net/problem/1893

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//* Idea: KMP + BF (Try all shift cases.)
//* Manage shift with map.


string encrypted;
vector< vector<int> > ans;

vector<int> getPartialMatch(string pattern){
    int size = pattern.size();
    vector<int> pi(size, 0);

    int prefix = 0;
    for(int suffix = 1; suffix < size; suffix++){
        while(prefix > 0 && pattern[prefix] != pattern[suffix]){
            prefix = pi[prefix - 1];
        }
        if(pattern[prefix] == pattern[suffix]){
            prefix++;
            pi[suffix] = prefix;
        }
    }

    return pi;
}

bool decrypt_KMP(string pattern){
    bool found = false;
    int matched = 0;

    int CT_size = encrypted.length(), P_size = pattern.size();
    vector<int> pi = getPartialMatch(pattern);

    for(int i = 0; i < CT_size; i++){

        while(matched > 0 && encrypted[i] != pattern[matched]){
            matched = pi[matched - 1];
        }

        if(encrypted[i] == pattern[matched]){
            matched++;
            if(matched == P_size){
                if(found){
                    //* Error. Same pattern exists!
                    return false;
                }
                found = true;
                matched = pi[matched - 1];
            }
        }
    }

    return found;
}

vector<int> caesar_found(){
    vector<int> available_pos;
    map<char, char> shift_arr;
    string input, original;
    int shift_len = 0, original_len = 0;

    cin >> input; //* Get shift value.
    shift_len = input.length();

    for(int i = 0; i < shift_len - 1; i++){
        pair<char, char> p(input[i], input[i+1]);
        shift_arr.insert(p);
    }
    pair<char, char> p(input[shift_len-1], input[0]);
    shift_arr.insert(p); //* Insert last -> first shift value.


    cin >> original; //* Get original and encrypted value.
    original_len = original.length();

    cin >> encrypted;
    for(int i = 0; i < shift_len; i++){
        if(decrypt_KMP(original)){
            available_pos.push_back(i);
        }
        //* shift the given string
        for(int j = 0; j < original_len; j++){
            original[j] = shift_arr.find(original[j])->second;
        }
    }

    return available_pos;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int TC = 0;
    cin >> TC;

    for(int i = 0; i < TC; i++){
        ans.push_back(caesar_found());
    }

    int len = ans.size();

    for(int i = 0; i < len; i++){
        int ans_size = ans[i].size();
        if(ans_size == 0){
            cout << "no solution";
        }else if(ans_size == 1){
            cout << "unique: " << ans[i][0];
        }else{
            cout << "ambiguous: ";
            for(int j = 0; j < ans_size; j++){
                cout << ans[i][j] << " ";
            }
        }
        cout << "\n";
    }

    return 0;
}
