// Algorithm Study
// Backjoon: 구간 합 구하기 5 (11660)
// https://www.acmicpc.net/problem/11660

#include <iostream>
#include <cstring>
#include <iterator>

using namespace std;

int board[1025][1025];
int ans[100000];
int N, M = 0;

int subTotal(int x1, int y1, int x2, int y2){
    //* Get Sum by calculating following formula
    return  board[x2][y2] - board[x2][y1-1] - board[x1 - 1][y2] + board[x1-1][y1-1];
}

int main (void){
    //* Strategy: Prefix Sum
    ios::sync_with_stdio(false);
    memset(board, 0, sizeof(board));
    fill(begin(ans), end(ans), 0);

    int x1,y1,x2,y2 = 0;
    cin >> N >> M;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            cin >> board[i][j];
            //* Prefix Sum
            //* Save sum of x1,y1 -> x2,y2
            board[i][j] += (board[i][j-1] + board[i-1][j] - board[i-1][j-1]);
        }
    }

    for(int i = 0; i < M; i++){
        cin >> x1 >> y1 >> x2 >> y2;
        ans[i] = subTotal(x1, y1, x2, y2);
    }

    for(int i = 0; i < M; i++){
        cout<<ans[i]<< "\n";
    }

    return 0;
}

