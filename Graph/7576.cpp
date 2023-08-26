// Algorithm Study
// Backjoon: 토마토 (7576)
// https://www.acmicpc.net/problem/7576

#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

//* Idea: BFS

int tomato[1001][1001];
bool discovered[1001][1001];
int N = 0, M = 0;

//* Left, Up, Right, Down
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

bool check(){
    for(int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            if(tomato[i][j] == 0) return false;
        }
    }
    return true;
}

int ripe(queue< pair<int, int> > q){
    int days = 0, num = 0; //* num: number of tomatoes affects within day.

    num = q.size(); //* init.

    while(!q.empty()){
        pair<int, int> cur = q.front();
        q.pop();

        tomato[cur.first][cur.second] = 1; //* Ripe!

        for(int i = 0; i < 4; i++){
            int ny = cur.first + dy[i];
            int nx = cur.second + dx[i];

            if(ny < 0 || ny >= M || nx < 0 || nx >= N) continue; //* Out of bound.
            if(discovered[ny][nx]) continue; //* Already Discovered.

            discovered[ny][nx] = true;
            if(tomato[ny][nx] == -1) continue; //* Wall

            q.push(pair<int, int>(ny, nx));
        }

        if(--num == 0){
            days++;
            num = q.size();
        }
    }

    return days;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    memset(tomato, 0, sizeof(tomato));
    memset(discovered, false, sizeof(discovered));

    int state = 0;
    queue<pair<int, int> > start;

    cin >> N >> M;

    for(int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            cin >> state;
            if(state == 1) {
                discovered[i][j] = true;
                start.push(pair<int, int>(i, j));
            }
            tomato[i][j] = state;
        }
    }

    int days = ripe(start);

    if(check()) cout << days - 1 << "\n"; //* Except the day 1.
    else cout << "-1\n";

    return 0;
}

