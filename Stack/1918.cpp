// Algorithm Study
// Backjoon: 후위 표기식 (1918)
// https://www.acmicpc.net/problem/1918

#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

//* Idea: Stack
//* 3 Cases
//* '(' -> Push into a stack
//* operator -> Before push into a stack, check the precedence. If op has less or equal precedence, print the top and pop. ((* == /) > (+ == -))
//* ')' -> Print and pop until pop '('
//* operand -> print it immediately
//* After searching all string, if the stack is not empty, print and pop till the stack became empty.

vector<char> post_order(string &eq){
    vector<char> ans;
    stack<char> stk;
    int size = eq.size();

    for(int i = 0; i < size; i++){
        char ch = eq[i];
        if(ch == '('){
            stk.push(ch);
        }else if(ch == '*' || ch == '/'){
            //* High precedence.
            while(!stk.empty() && (stk.top() == '*' || stk.top() == '/')){ //* Print if top operator has same precedence.
                ans.push_back(stk.top());
                stk.pop();
            }
            stk.push(ch);
        }else if(ch == '+' || ch == '-'){
            //* Low precedence.
            while(!stk.empty() && (stk.top() != '(')){ //* Print all operands.
                ans.push_back(stk.top());
                stk.pop();
            }
            stk.push(ch);
        }else if(ch == ')'){
            while(stk.top() != '('){
                ans.push_back(stk.top());
                stk.pop();
            }
            stk.pop(); //* pop '('
        }else{
            //* Print the operand
            ans.push_back(ch);
        }
    }

    while(!stk.empty()){
        ans.push_back(stk.top());
        stk.pop();
    }

    return ans;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    string eq;

    cin >> eq;
    vector<char> post = post_order(eq);

    int size = post.size();
    for(int i = 0; i < size; i++){
        cout << post[i];
    }
    cout << "\n";

    return 0;
}
