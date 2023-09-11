// Algorithm Study
// Backjoon: 파이프 옮기기 1 (17070)
// https://www.acmicpc.net/problem/17070

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

struct Pipe{
    pair<short, short> pos; //* Last Position
    char dir; //* H: Horizontal, V: Vertical, D: Diagonal

    Pipe(pair<short, short> _pos, char _dir){
        this->pos = _pos;
        this->dir = _dir;
    }
};

short house[20][20];
int N = 0;
int possibilities = 0;

bool check_horizontal(int y, int x){
    if(x+1 <= N && house[y][x+1] == 0) return true;
    return false;
}

bool check_vertical(int y, int x){
    if(y+1 <= N && house[y+1][x] == 0) return true;
    return false;
}

bool check_diagonal(int y, int x){
    if(check_horizontal(y,x) && check_vertical(y,x) && house[y+1][x+1] == 0) return true;
    return false;
}

void move_pipe(Pipe pipe){
    //* Base Case
    short py = pipe.pos.first;
    short px = pipe.pos.second;

    if(py == N && px == N){
        //* Reached to the end.
        possibilities++;
        return;
    }

    //* Move Pipe.
    if(pipe.dir == 'H'){
        //* 2 Cases
        if(check_horizontal(py, px)){
            house[py][px+1] = 1;
            move_pipe(Pipe(make_pair(py, px+1), 'H'));
            house[py][px+1] = 0;
        }
        if(check_diagonal(py, px)){
            house[py][px+1] = 1; house[py+1][px] = 1; house[py+1][px+1] = 1;
            move_pipe(Pipe(make_pair(py+1, px+1), 'D'));
            house[py][px+1] = 0; house[py+1][px] = 0; house[py+1][px+1] = 0;
        }
    }
    if(pipe.dir == 'D'){
        //* 3 Cases
        if(check_horizontal(py, px)){
            house[py][px+1] = 1;
            move_pipe(Pipe(make_pair(py, px+1), 'H'));
            house[py][px+1] = 0;
        }
        if(check_vertical(py, px)){
            house[py+1][px] = 1;
            move_pipe(Pipe(make_pair(py+1, px), 'V'));
            house[py+1][px] = 0;
        }
        if(check_diagonal(py, px)){
            house[py][px+1] = 1; house[py+1][px] = 1; house[py+1][px+1] = 1;
            move_pipe(Pipe(make_pair(py+1, px+1), 'D'));
            house[py][px+1] = 0; house[py+1][px] = 0; house[py+1][px+1] = 0;
        }
    }
    if(pipe.dir == 'V'){
        //* 2 Cases
        if(check_vertical(py, px)){
            house[py+1][px] = 1;
            move_pipe(Pipe(make_pair(py+1, px), 'V'));
            house[py+1][px] = 0;
        }
        if(check_diagonal(py, px)){
            house[py][px+1] = 1; house[py+1][px] = 1; house[py+1][px+1] = 1;
            move_pipe(Pipe(make_pair(py+1, px+1), 'D'));
            house[py][px+1] = 0; house[py+1][px] = 0; house[py+1][px+1] = 0;
        }
    }

    return;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(house, 0, sizeof(house));

    cin >> N;

    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            cin >> house[i][j];
        }
    }

    house[1][1] = 1; house[1][2] = 1; //* init.
    move_pipe(Pipe(make_pair(1,2), 'H'));

    cout << possibilities << "\n";

    return 0;
}
