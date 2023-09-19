// Algorithm Study
// Backjoon: 피보나치 수 6 (11444)
// https://www.acmicpc.net/problem/11444

#include <iostream>
using namespace std;

#define ll long long

//* Idea: Divide and Conquer; Solve Fibonacci by using matrix.
//* F2 = [[1,1],[1,0]] * [F1, F0]t, F0 = 0 , F1 = 1.
//* [Fn+1, Fn] = [[1,1],[1,0]]^n * [1,0]t

const ll MOD = 1000000007;
ll** origin;
ll N = 0;


ll** matrix_multiply(ll** m1, ll** m2){
    ll** ret = new ll*[2];

    for(int i = 0; i < 2; i++){
        ret[i] = new ll[2];
    }

    ret[0][0] = ((m1[0][0] * m2[0][0]) + (m1[0][1] * m2[1][0])) % MOD;
    ret[0][1] = ((m1[0][0] * m2[0][1]) + (m1[0][1] * m2[1][1])) % MOD;
    ret[1][0] = ((m1[1][0] * m2[0][0]) + (m1[1][1] * m2[1][0])) % MOD;
    ret[1][1] = ((m1[1][0] * m2[0][1]) + (m1[1][1] * m2[1][1])) % MOD;

    return ret;
}

ll** square(ll** A, ll B){
    if(B == 1 || B == 0) return A; //* return origin A.

    ll** ret = square(A, B/2);

    ret = matrix_multiply(ret, ret);

    if(B % 2 == 1) ret = matrix_multiply(ret, origin);

    return ret;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    origin = new ll*[2];

    for(int i = 0; i < 2; i++){
        origin[i] = new ll[2];
    }

    origin[0][0] = 1; origin[0][1] = 1; origin[1][0] = 1; origin[1][1] = 0;
    cin >> N;

    ll** ret = square(origin, N);

    /*
     ret[0][0] == Fn+1
     ret[1][0] == ret[0][1] == Fn
     ret[1][1] == Fn-1
     */

    if(N == 0) cout << "0\n";
    else cout << ret[1][0] << "\n";

    return 0;
}




