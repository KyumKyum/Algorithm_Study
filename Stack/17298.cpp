// Algorithm Study
// Backjoon: 오큰수 (17298)
// https://www.acmicpc.net/problem/17298

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

//* Strategy: Stack.
//* Need to solve in O(n)

vector<int> values;
stack<int> idx;
int ans[1000000];

int N = 0;

void NGE(void){
    //* Enter first value into the stack (init)
    idx.push(0);

    for(int i = 1; i < N; i++){
        //* iterate all input, and update NGE.

        while(!idx.empty()){
            int top_idx = idx.top();

            if(values[top_idx] >= values[i]){
                //* Not an NGE, stop searching.
                break;
            }else{
                //* Found value's NGE
                //* Pop current index (founded), and record its NGE at its index.
                idx.pop();
                ans[top_idx] = values[i];
            }

        }

        idx.push(i); //* Need to find NGE of current index.
    }

    while(!idx.empty()){
        //* Remaining Index: -1
        int top_idx = idx.top();
        ans[top_idx] = -1;
        idx.pop();
    }

    return;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int input = 0;

    cin >> N;

    for(int i = 0; i < N; i++){
        cin >> input;
        values.push_back(input);
    }

    NGE();

    for(int i = 0; i < N; i++){
        cout << ans[i] << " ";
    }
    cout << "\n";

    return 0;
}
