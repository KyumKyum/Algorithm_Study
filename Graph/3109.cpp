// Algorithm Study
// Backjoon: 빵집 (3109)
// https://www.acmicpc.net/problem/3109


#include <iostream>
#include <cstring>

using namespace std;

//* Idea: BFS + Greedy
//* BFS the possible route.
//* If possible route found via BFS, change those value as -2. This route will be assumed as a building (Impossible to pass)
//* If another trial of BFS fails, it means there is no more possible route for pipeline.
//* Greedy: The pipeline shouldn't be overlapped + If the place is impossible to place pipeline, it will be the same with the future. (This route is unable for all case)
//* If visited once, do not reset it.

int board[10001][501];
bool visited[10001][501];
int R = 0, C = 0;

int next_mv[3] = {-1, 0, 1};

bool pipelining(int y, int x){
    if(x == C - 1 && (y >= 0 && y < R)) return true; //* Found a possible way.

    for(int i = 0; i < 3; i++){
        int ny = y + next_mv[i];
        int nx = x + 1;

        if(nx < 0 || nx >= C || ny < 0 || ny >= R) continue; //* Out of bound.
        if(visited[ny][nx]) continue;

        visited[ny][nx] = true;
        if(board[ny][nx] < 0) continue; //* Not possible to pass.

        board[ny][nx] = -2;
        if(pipelining(ny, nx)) return true;
        board[ny][nx] = 0;
    }

    //* Tried all possible route.
    return false;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    memset(board, 0, sizeof(board));
    memset(visited, false, sizeof(visited));
    int possible = 0;

    cin >> R >> C;

    for(int i = 0; i < R; i++){
        string row;
        cin >> row;
        for(int j = 0; j < C; j++){
            if (row[j] == '.') board[i][j] = 0; //* Empty
            else board[i][j] = -1; //* Building.
        }
    }

    for(int c = 0; c < R; c++){
        if(board[c][0] == -2) continue;

        board[c][0] = -2; //* Try.
        visited[c][0] = true;

        if(pipelining(c, 0)){
            possible++;
        }else{
            board[c][0] = 0;
        }
    }

    cout << possible << "\n";

    return 0;
}