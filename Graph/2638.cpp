// Algorithm Study
// Backjoon: 치즈 (2638)
// https://www.acmicpc.net/problem/2638

#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

//* Strategy: Implementation + BFS
//* Seperate open and closed space using BFS, mark open place as 2.
//* Melt will be performed only for open place (2)

int board[100][100];
int N, M = 0;
int elapsed = 0;

bool check(void){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(board[i][j] == 1){
                //* There are still cheese left.
                //* return false.
                return false;
            }
        }
    }
    return true;
}

void reset(void){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(board[i][j] == 2){
                board[i][j] = 0;
            }
        }
    }
    return;
}

void separate(void){
    //* Seperate outer space by BFS
    queue< pair<int, int> > search;
    pair<int,int> loc;
    loc.first = 0;
    loc.second = 0;
    search.push(loc); //* First blank space

    while(!search.empty()){
        //* Search right, left, up and under
        pair<int, int> cur = search.front();
        board[cur.first][cur.second] = 2; //* 2: open space
        if(cur.second + 1 < M && board[cur.first][cur.second + 1] == 0){
            //* If left is empty
            board[cur.first][cur.second + 1] = 2;
            loc.first = cur.first;
            loc.second = cur.second + 1;
            search.push(loc);
        }
        if(cur.first + 1 < N && board[cur.first + 1][cur.second] == 0){
            //* If under is empty
            board[cur.first + 1][cur.second] = 2;
            loc.first = cur.first + 1;
            loc.second = cur.second;
            search.push(loc);
        }
        if(cur.first > 0 && board[cur.first - 1][cur.second] == 0){
            //* If Upper is empty
            board[cur.first - 1][cur.second] = 2;
            loc.first = cur.first - 1;
            loc.second = cur.second;
            search.push(loc);
        }
        if(cur.second > 0 && board[cur.first][cur.second - 1] == 0){
            //* If right  is empty
            board[cur.first][cur.second - 1] = 2;
            loc.first = cur.first;
            loc.second = cur.second - 1;
            search.push(loc);
        }

        search.pop();
    }

    return;
}

void melt(void){
    //* Span all location, mark the target area will be melted.
    queue< pair<int, int> > melted;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(board[i][j] == 1){
                //* Check if current area will be melted.
                int exposed = 0;
                //* Assume there is no cheese in the border.
                if(board[i-1][j] == 2){ //* Check upper
                    exposed++;
                }
                if(board[i+1][j] == 2) { //* Check under
                    exposed++;
                }
                if(board[i][j-1] == 2){ //* Check Left
                    exposed++;
                }
                if(board[i][j+1] == 2){ //* Check Right
                    exposed++;
                }

                if(exposed >= 2){
                    pair<int, int> p;
                    p.first = i;
                    p.second = j;
                    melted.push(p);
                }
            }
        }
    }

    //* Melt!
    while(!melted.empty()){
        board[melted.front().first][melted.front().second] = 0;
        melted.pop();
    }
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    memset(board, 0, sizeof(board));

    int cheese = 0;

    cin >> N >> M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> cheese;
            board[i][j] = cheese;
        }
    }

    while(!check()){
        separate();
        melt();
        reset();
        elapsed++;
    }

    cout << elapsed << "\n";

    return 0;
}
