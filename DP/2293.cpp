// Algorithm Study
// Backjoon: 동전 1 (2293)
// https://www.acmicpc.net/problem/2293

#include <iostream>
#include <cstring>

using namespace std;

int coin[102];
int cache[10002];
int N,K = 0;
int num = 0;

void coin_case(){

    for(int i = 1; i <= N; i++){
        for(int j = coin[i]; j <= K; j++){
            //* Calcualte All values that can be made with coin[i]
            //* ex: coin -> 1, Case to make value 1 == 1 (0 + 1)
            //* coin -> 2 -> Case to make value 2 == 2 (1 + 1, 0 + 2)
            //* coin -> 3 -> case to make value 3 == 3 (1 + 1 + 1, 2 + 1, 0 + 3)
            cache[j] = cache[j] + cache[j - coin[i]]; //* Calculate number of cases to make value K with value j and coin i.
            //* If I need to make value j with coin i, I need to add number of cases possible to make value j - i
        }
    }

    num = cache[K];
}

int main(void){
    // Strategy: DP
    //* Cache: Number of cases available to make current value.
    //* cache[a] = b : There are b kinds of cases able to make value of coin[a].
    ios::sync_with_stdio(false);
    memset(cache, 0, sizeof(cache));
    cache[0] = 1; //* cache[0] == number of case to make value K with coin with value K (only one case possible!)

    cin >> N >> K;
    for(int i = 1; i <= N; i++){
        cin >> coin[i];
    }

    coin_case();

    cout << num << endl;
    return 0;
}