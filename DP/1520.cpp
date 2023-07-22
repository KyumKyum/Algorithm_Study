// Algorithm Study
// Backjoon: 내리막길 (1520)
// https://www.acmicpc.net/problem/1520

#include <iostream>
#include <cstring>

using namespace std;

int stairs[510][510];
int cache[510][510];
int N, M = 0;

int go_down(int cur_y, int cur_x){
    //* Strategy: DP
    //* Recursively find possible path,
    //* Cache maximum path of subproblem.
    if(cur_y == M - 1 && cur_x == N - 1){
        return 1; //* Reached to the end
    }

    int& ret = cache[cur_y][cur_x];
    int moved = 0;

    if(ret != -1){
        return ret;
    }

    int height = stairs[cur_y][cur_x];
    if(cur_x > 0 && stairs[cur_y][cur_x-1] < height){ //* Move left
        moved += go_down(cur_y, cur_x-1);
    }

    if(cur_x < N - 1 && stairs[cur_y][cur_x+1] < height){ //* Move right
        moved += go_down(cur_y, cur_x+1);
    }

    if(cur_y > 0 && stairs[cur_y - 1][cur_x] < height){ //* Move Up
        moved += go_down(cur_y - 1, cur_x);
    }

    if(cur_y < M - 1 && stairs[cur_y + 1][cur_x] < height){ //* Move Down
        moved += go_down(cur_y + 1, cur_x);
    }

    ret = moved;
    return moved;

}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    memset(stairs, 0, sizeof(stairs));
    memset(cache, -1, sizeof(cache));
    cin >> M >> N;

    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            cin >> stairs[i][j];
        }
    }

    cout << go_down(0,0) << "\n";

    return 0;
}
