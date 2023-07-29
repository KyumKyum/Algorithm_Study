// Algorithm Study
// Backjoon: 연구소 (14502)
// https://www.acmicpc.net/problem/14052

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

//* Strategy: Implementation + BF + DFS
//* Brute-force: BF all possibility to fill 3 walls.
    //* for each case, try diffusion for all possible case, get maximum value possible.
    //* Save all initial virus place in queue.
//* DFS: Spread by recursive call.

int lab[10][10];
int wall[100];
int N, M = 0;
vector< pair<int, int> > virus_init;
int v_init_size = 0;
int maximum = -1;

void convert(void){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            lab[i][j] = wall[(M * i) + j];
        }
    }
    return;
}

void spread(int y, int x){
    //* Check Up, Down, Left, Right. If blank exist, recursively spread.
    //* Check Up
    if(y > 0 && lab[y - 1][x] == 0){
        lab[y-1][x] = 2;
        spread(y-1, x);
    }
    //* Check Down
    if(y < N - 1 && lab[y + 1][x] == 0){
        lab[y+1][x] = 2;
        spread(y+1, x);
    }
    //* Check Left
    if(x > 0 && lab[y][x-1] == 0){
        lab[y][x-1] = 2;
        spread(y,x-1);
    }
    //* Check Right
    if(x < M - 1 && lab[y][x+1] == 0){
        lab[y][x+1] = 2;
        spread(y, x+1);
    }

    return;
}

void build(int start, int left){
    if(left <= 0){
        int safe = 0;
        //* check spread
        convert();

        for(int i = 0; i < v_init_size; i++){
            spread(virus_init[i].first, virus_init[i].second);
        }

        //* Count Blank Space
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                if(lab[i][j] == 0){
                    safe++;
                }
            }
        }

        maximum = max(maximum, safe);

        return;
    }

    for(int i = start; i < N * M; i++){
        if(wall[i] > 0){ //* Skip if it is not a blank.
            continue;
        }else{
            wall[i] = 1;
            build(i + 1, left - 1);
            wall[i] = 0;
        }
    }

    return;

}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    memset(lab, 0, sizeof(lab));

    int input = 0;
    pair<int, int> p;
    cin >> N >> M;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> input;
            if(input == 2){
                p.first = i;
                p.second = j;
                virus_init.push_back(p);
            }
            wall[(M * i) + j] = input;
        }
    }

    v_init_size = virus_init.size();

    build(0, 3);

    cout << maximum << "\n";

    return 0;
}