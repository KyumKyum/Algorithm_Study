// Algorithm Study
// Backjoon: AC (5430)
// https://www.acmicpc.net/problem/5430

#include <iostream>
#include <deque>
#include <queue>
#include <string>
#include <sstream>

using namespace std;

//* Idea: Deque
//* Operation 'R' => pop_back -> push_front
//* Operation 'D' => pop_front

//* Need to execute reverse operation in O(1)
//* Declare another deque reversed version of array
    //* Reverse Operation: swap original array with reversed one.
    //* Delete Operation: arr.pop_front(), reversed.pop_back()

string ans[100];
int TC, N = 0;

string execute(queue<char> ops, deque<string> arr, deque<string> reversed){
    while(!ops.empty()){
        char op = ops.front();

        if(op == 'R'){
            //* Reverse
            swap(arr, reversed);
        }else if(op == 'D'){
            //* Delete
            if(arr.empty()){
                //* Error
                return "error";
            }
            arr.pop_front();
            reversed.pop_back();
        }

        ops.pop();
    }

    //* Generate Answer
    string ret = "[";
    while(!arr.empty()){
        ret.append(arr.front()).append(",");
        arr.pop_front();
    }

    if(ret[ret.size()-1] == ','){
        ret = ret.substr(0, ret.size() - 1); //* Remove last comma
    }
    ret.append("]");

    return ret;
}

string AC(){
    string operation;
    string input;
    queue<char> ops;
    deque<string> arr;
    deque<string> reversed;

    int arr_size;

    cin >> operation;
    int len = operation.length();
    for(int i = 0; i < len; i++){
        ops.push(operation[i]);
    }

    cin >> arr_size;
    cin >> input;
    //* Remove [ and ]
    input = input.substr(1, input.size()-2);
    //* Remove ,
    stringstream ss(input);
    string temp;

    while(getline(ss, temp, ',')) {
        arr.push_back(temp);
        reversed.push_front(temp);
    }

    return execute(ops, arr, reversed);
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> TC;

    for(int i = 0; i < TC; i++){
        ans[i] = AC();
    }

    for(int i = 0; i < TC; i++){
        cout << ans[i] << "\n";
    }
    return 0;
}