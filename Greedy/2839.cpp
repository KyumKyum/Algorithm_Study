// Algorithm Study
// Backjoon: 설탕배달 (2839)
// https://www.acmicpc.net/problem/2839

#include <iostream>

//* Strategy: Greedy
//* Firsty check if can wrapped with 5kg
//* If it is, wrap all rest of them.
//* If not, wrap 3kg from it and check it again

using namespace std;

int sugar_delivery(int sugar){
    int wrapper = 0;

    while(sugar > 0){
        if(sugar <= 2){
            //* This case cannot be done.
            wrapper = -1;
            break;
        }

        if(sugar % 5 == 0){
            //* Wrap it all with 5kg.
            wrapper += sugar / 5;
            break;
        }else{
            //* Wrap 3 kg from it.
            sugar -= 3;
            wrapper++;
        }
    }

    return wrapper;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;

    cout << sugar_delivery(N) << "\n";
    return 0;
}
