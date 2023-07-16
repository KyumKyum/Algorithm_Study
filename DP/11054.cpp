// Algorithm Study
// Backjoon: 가장 긴 바이토닉 부분 수열 (11054)
// https://www.acmicpc.net/problem/11054

#include <iostream>
#include <algorithm>
#include <cstring>
#include <iterator>

using namespace std;

int A[1001];
int LIS[1001];
int SIS[1001];
int N = 0;


int find_longest_bitonic(){
    int maximum = 0;
    //* Find LIS, SIS first.
    //* SIS: LIS of reversed array.
    //* maximum bitonic = LIS[i] + SIS[i] - 1 (duplicated (12345 / 521))
    //* Add both length
    for(int i = 1; i < N; i++){
        for(int j = 0; j < i; j++){
            if(A[j] < A[i])
                LIS[i] = max(LIS[i], LIS[j] + 1);
        }
    }

    for(int i = N - 2; i >= 0; i--){
        for(int j = N - 1; j >= i; j--){
            if(A[j] < A[i])
                SIS[i] = max(SIS[i], SIS[j] + 1);
        }
    }

    for(int i = 0; i < N; i++){
        maximum = max(maximum, LIS[i] + SIS[i] - 1);
    }
    return maximum; //* return without duplication

}

int main(void){
    int temp = 0;
    ios::sync_with_stdio(false);
    memset(A,-1,sizeof(A));
    fill(begin(LIS), end(LIS), 1);
    fill(begin(SIS), end(SIS), 1);

    cin >> N;

    for(int i = 0; i < N; i++){
        cin >> temp;
        A[i] = temp;
    }

    cout << find_longest_bitonic() << endl;

    return 0;
}