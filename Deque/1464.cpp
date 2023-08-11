// Algorithm Study
// Backjoon: 뒤집기 3 (1464)
// https://www.acmicpc.net/problem/1464

#include <iostream>
#include <deque>
#include <string>

using namespace std;

//* Idea: Deque + Greedy
//* Push each character into deque.
//* Greedier Approach: We cannot change string which is already sorted (reversed or not).
//* Reverse => Only happens if deque.rear() is bigger than current character and deque front is bigger or same with current character
    //* If so, simply push_front to the character. (If we reverse the already sorted array, it must be re-reversed again immediately)
    //* BCD AF => Reverse! (push_front_ => ABCD F (DCBA F -> ABCD F)
    //* AAC B => No Reverse! (Since deque.front() is smaller than current characer -> breaks the sorted string.) => AABC

deque<char> reverse_string(string input){
    int size = input.size();
    deque<char> deq;

    for(int i = 0; i < size; i++){
        //* extract element.
        if(deq.empty()){
            //* If deque is empty, push the current element.
            deq.push_back(input[i]);
        }else{
            //* Compare with the last element.
            if(deq.back() <= input[i]){
                //* If is in order, last < cur, then push.
                deq.push_back(input[i]);
            }else{
                //* else, reverse the deq and push.
                //* Reverse:
                    //* Assuming the front part is already sorted
                    //* If reverse the front part, it is required to re-reverse the array.
                    //* Then, reversing ==> Put the input[i] at the front.
                if(deq.back() > input[i] && deq.front() >= input[i]){
                    //* Reverse happens in this condition (this element needs to go front.)
                    deq.push_front(input[i]);
                }else{
                    //* Sadly, there is no way to sort this in order.
                    deq.push_back(input[i]);
                }
            }
        }
    }

    return deq;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    string input;

    cin >> input;

    deque<char> ret = reverse_string(input);

    while(!ret.empty()){
        cout << ret.front();
        ret.pop_front();
    }
    cout << "\n";

    return 0;
}