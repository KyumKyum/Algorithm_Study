// Algorithm Study
// Backjoon: 욕심쟁이 판다 (1937)
// https://www.acmicpc.net/problem/1937

#include <iostream>
#include <cstring>

using namespace std;

int forest[510][510];
int cache[510][510];
int N = 0;
int maximum = -1;

int panda_move(int cur_y, int cur_x){
    //* Strategy: DP
    //* Recursively find possible path,
    //* Cache maximum path of subproblem.
    int& ret = cache[cur_y][cur_x];
    int moved = 0;

    if(ret != -1){
        return ret;
    }

    int bamboo = forest[cur_y][cur_x];
    if(cur_x > 0 && forest[cur_y][cur_x-1] > bamboo){ //* Move left
        moved = max(moved, 1 + panda_move(cur_y, cur_x - 1));
    }

    if(cur_x < N - 1 && forest[cur_y][cur_x+1] > bamboo){ //* Move right
        moved = max(moved, 1 + panda_move(cur_y, cur_x + 1));
    }

    if(cur_y > 0 && forest[cur_y - 1][cur_x] > bamboo){ //* Move Up
        moved = max(moved, 1 + panda_move(cur_y - 1, cur_x));
    }

    if(cur_y < N - 1 && forest[cur_y + 1][cur_x] > bamboo){ //* Move Up
        moved = max(moved, 1 + panda_move(cur_y + 1, cur_x));
    }

    ret = moved;
    maximum = max(maximum, moved);

    return moved;

}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    memset(forest, 0, sizeof(forest));
    memset(cache, -1, sizeof(cache));
    cin >> N;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> forest[i][j];
        }
    }

    for(int i = 0; i < N; i++){
        for(int  j = 0; j < N; j++){
            panda_move(i,j);
        }
    }

    cout << maximum + 1 << "\n"; //* Add 1; including current space.

    return 0;
}
