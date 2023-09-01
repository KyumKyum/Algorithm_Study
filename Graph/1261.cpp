// Algorithm Study
// Backjoon: 알고스팟 (1261)
// https://www.acmicpc.net/problem/1261

#include <iostream>
#include <deque>
#include <cstring>

using namespace std;

//* Idea: 0-1 BFS

struct Space{
    int x;
    int y;
    short weight;
    int breaks;

    Space(int _y, int _x, int _weight, int _breaks){
        this->y = _y;
        this->x = _x;
        this->weight = _weight;
        this->breaks = _breaks;
    }
};

deque< Space> ZObfs;
//* x, y, weight(0/1)
char board[101][101];
bool visited[101][101];

int N = 0, M = 0;

int dy[4] = {0, -1, 1, 0};
int dx[4] = {1, 0, 0, -1};

int maze(){
    ZObfs.push_front(Space(0,0,0, 0));
    visited[0][0] = true;

    while (!ZObfs.empty()){
        Space cur = ZObfs.front();
        ZObfs.pop_front();
        if(cur.y == M-1 && cur.x == N-1) return cur.breaks; //* Reached to the end.

        for(int i = 0; i < 4; i++){
            int ny = cur.y + dy[i];
            int nx = cur.x + dx[i];

            if(nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
            if(visited[ny][nx]) continue; //* Already Visited

            visited[ny][nx] = true;

            if(board[ny][nx] == '1') ZObfs.push_back(Space(ny, nx, 1, cur.breaks + 1));
            else ZObfs.push_front(Space(ny, nx, 0, cur.breaks));
        }
    }

    return -1; //* This shouldn't be executed.
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    memset(board, 0, sizeof(board));
    memset(visited, false, sizeof(visited));

    cin >> N >> M;

    for(int i = 0; i < M; i++){
        string row;
        cin >> row;
        for(int j = 0; j < N; j++){
            board[i][j] = row[j];
        }
    }

    cout << maze() << "\n";

    return 0;
}