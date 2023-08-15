// Algorithm Study
// Backjoon: 회문 (17609)
// https://www.acmicpc.net/problem/17609

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//* Idea: Two-Pointer

vector<int> ans;
int T = 0;

int check_palindrome(const string str, int front, int back, bool strict){
    while(front < back){
        if(str[front] == str[back]){
            front++;
            back--;
        }else{
            if(!strict) return 2; //* Already removed one letter
            return min(check_palindrome(str, front, back-1, false), check_palindrome(str, front+1, back, false));
            //* Return small value (if one of case became palindrome(1), it returns 1.)
        }
    }

    if(!strict){
        return 1;
    }
    return 0;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    string str;
    cin >> T;

    for(int i = 0; i < T; i++){
        cin >> str;
        ans.push_back(check_palindrome(str, 0, str.length() - 1, true));
    }

    int size = ans.size();

    for(int i = 0; i < size; i++){
        cout << ans[i] << "\n";
    }

    return 0;
}
