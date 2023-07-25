// Algorithm Study
// Backjoon: A -> B (16953)
// https://www.acmicpc.net/problem/16953

#include <iostream>

using namespace std;

//* Strategy: Greedy
//* Start from final value.
//* If it ends with 1, remove 1.
//* Else, make it half.
//* If the value is odd without ending 1, this is also cannot be done, return -1
//* Repeat until the value can be made.
//* If the value became less than initial value, this case cannot be done, return -1.

int convert(long long init, long long final){
    int operation = 1;

    while(init != final){
        if(final < init){
            //* This Case Cannot be done.
            operation = -1;
            break;
        }

        if(final % 10 == 1){
            //* It ends with 1, remove 1.
            final /= 10;
        }else if(final % 2 == 1){
            operation = -1;
            break;
        }
        else{
            //* make it half
            final /= 2;
        }
        operation++;
    }

    return operation;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    long long A, B = 0;
    cin >> A >> B;

    cout << convert(A, B) << "\n";
    return 0;
}