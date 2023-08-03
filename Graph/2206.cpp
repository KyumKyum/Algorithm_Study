// Algorithm Study
// Backjoon: 벽 부수고 이동하기 (2206)
// https://www.acmicpc.net/problem/2206

#include <iostream>
#include <queue>
#include <cstring>
#include <limits.h>
#include <algorithm>
#include <string>

using namespace std;

//* Strategy: BFS

struct Cell{
    short n;
    short m;
    bool collapse;
    int moved;
};

int board[1001][1001];
bool visited[1001][1001][2];
//* Boolean array to check visited.
//* Breaking wall will happen only once.
//* Will be differentiated by last index; 0 - not breaked 1 - breaked;
//* Breaking condition will be not overlapped, since breaking will be happen only once.
    //* normal -> normal -> BREAK! -> normal -> normal ...
int N, M = 0;

int move_n[4] = {-1, 1, 0, 0};
int move_m[4] = {0, 0, -1, 1};


int breakthrough(void){
    queue<Cell> bfs;
    int minimum = INT_MAX;
    Cell init = {0,0, false, 1};
    bfs.push(init);

    visited[0][0][0] = true;
    visited[0][0][1] = true;

    //* BFS for all direction
    //* If wall found, and it hadn't break anything,
    //* Break it. (push to the queue even if it is 1.)

    while(!bfs.empty()){
        Cell top = bfs.front();
        //* Visited

        //* Reched destination
        if(top.n == N-1 && top.m == M-1){
            minimum = min(top.moved, minimum);
            bfs.pop();
            break; //* First Reached == Shortest Path (BFS)
        }

        for(int i = 0; i < 4; i++){
            int new_n = top.n + move_n[i];
            int new_m = top.m + move_m[i];

            if(new_n < 0 || new_n >= N || new_m < 0 || new_m >= M)
                continue;

            if(visited[new_n][new_m][top.collapse]) continue; //* No need to visit space which is already in bfs queue.

            if(board[new_n][new_m] == 1 && !top.collapse && !visited[new_n][new_m][1]){
                visited[new_n][new_m][1] = true;
                Cell visit = {new_n, new_m, true, top.moved + 1};
                bfs.push(visit);
            }
            if(board[new_n][new_m] == 0 && !visited[new_n][new_m][0]){
                visited[new_n][new_m][top.collapse] = true;
                Cell visit = {new_n, new_m, top.collapse, top.moved + 1};
                bfs.push(visit);
            }

        }



        bfs.pop();
    }

    if(minimum == INT_MAX){
        minimum = -1; //* Impossible.
    }

    return minimum;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    memset(board, 0, sizeof(board));
    memset(visited, false, sizeof(visited));
    string movable;
    cin >> N >> M;

    for(int i = 0; i < N; i++){
        cin >> movable;
        for(int j = 0; j < M; j++){
            board[i][j] = movable[j] - '0';
        }
    }

    cout << breakthrough() << "\n";

    return 0;
}
