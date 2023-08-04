// Algorithm Study
// Backjoon: 집합 (11723)
// https://www.acmicpc.net/problem/11723

#include <iostream>
#include <string>

#define ADD "add"
#define REMOVE "remove"
#define CHECK "check"
#define TOGGLE "toggle"
#define ALL "all"
#define empty "EMPTY"

using namespace std;

//* Practicing Bitmask.

int set = (1 << 20); //* empty set

void add_op(int element){
    set |= ( 1 << (element - 1) );
    return;
}

void remove_op(int element){
    set &= ~(1 << (element - 1));
    return;
}

int check_op(int element){
    if(set & (1 << (element - 1))){
        return 1;
    }
    return 0;
}

void toggle_op(int element){
    set ^= (1 << (element - 1));
    return;
}

void all_op(void){
    set = (1<<20) - 1;
    return;
}

void empty_op(void){
    set = (1<<20);
    return;
}


int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int M, param = 0;
    string op;
    cin >> M;

    for(int i = 0; i < M; i++){
        cin >> op;

        if((op == ADD) == 1){
            cin >> param;
            add_op(param);
        }else if((op == REMOVE) == 1){
            cin >> param;
            remove_op(param);
        }else if((op == CHECK) == 1){
            cin >> param;
            cout << check_op(param) << "\n";
        }else if((op == TOGGLE) == 1){
            cin >> param;
            toggle_op(param);
        }else if((op == ALL) == 1){
            all_op();
        }else{ //* Empty
            empty_op();
        }
    }
    return 0;
}
