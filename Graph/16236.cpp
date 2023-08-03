// Algorithm Study
// Backjoon: 아기 상어 (16236)
// https://www.acmicpc.net/problem/16236

#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

//* Strategy: BFS
//* If there are no more fish that baby shark can eat, immediately return and print the total moved space.
//* If there is a fish, BFS the route toward the fish, find sequence: up, left, right, down.
//* If the shark ate the fish, bfs again.
//* If there are same number of fish available, choose one based on the priority. (Upper, then left first.)
//* After eat, fish size will grow based on its rules.

struct Shark{
    int size;
    int left; //* Required fish to grow
    int moved;
    pair<int, int> pos;
};

int sea[21][21];
bool visited[21][21];

//* Direction: Up, Left, Right, Down
int dy[4] = {-1, 0, 0, 1};
int dx[4] = {0, -1, 1, 0};

queue<Shark> bfs;
int N = 0;

int eat(pair<int, int> pos){
    int min_move, total = 0;
    bool eaten = false;
    bool found = false;
    bool call_mom = false;
    pair<int, int> tgt;
    Shark init = {2, 2, 0, pos};

    while(!call_mom){
        memset(visited, false, sizeof(visited));
        while(!bfs.empty()){
            bfs.pop(); //* Reset
        }
        eaten = false;
        found = false;
        init.moved = 0;
        visited[init.pos.first][init.pos.second] = true;
        tgt.first = -1;
        tgt.second = -1;
        min_move = -1;
        bfs.push(init); //* Start Position
        while(!bfs.empty()){
            if(eaten){
                break;
            }
            for(int i = 0; i < 4; i++){
                Shark baby = bfs.front();
                pair<int, int> &cur = baby.pos;
                int ny = cur.first + dy[i];
                int nx = cur.second + dx[i];

                if(ny < 0 || ny >= N || nx < 0 || nx >=N) continue;
                if(visited[ny][nx]) continue;
                if(sea[ny][nx] > baby.size) continue; //* Cannot Move space with fish bigger than current fish size.

                cur.first = ny;
                cur.second = nx;
                baby.moved++;

                if(sea[ny][nx] != 0){ //* It's a fish!
                    if(sea[ny][nx] < baby.size){
                        //* Baby shark will eat the fish!
                        if(!found){
                            found = true;
                            tgt.first = ny;
                            tgt.second = nx;
                            min_move = baby.moved;
                            init = baby;
                        }else{
                            if(baby.moved == min_move){ //* If there are multiple fish are able to eat.
                                if(ny < tgt.first){ //* Prioritize Upper position
                                    tgt.first = ny;
                                    tgt.second = nx;
                                    init = baby;
                                }else if(ny == tgt.first && nx < tgt.second){ //* Prioritize left if y position is the same
                                    tgt.first = ny;
                                    tgt.second = nx;
                                    init = baby;
                                }
                            }
                        }
                    }
                }

                visited[cur.first][cur.second] = true;
                bfs.push(baby);
            }
            bfs.pop();
        }
        if(found){
            sea[tgt.first][tgt.second] = 0;
            if(--init.left <= 0){
                init.size += 1;
                init.left = init.size;
            }
            eaten = true;
            total += init.moved;
            init = init; //* Update start position.
        }else{
            //* BFS All place, but not able to find destination.
            //* Finish BFS (No fish available. Perhaps the baby shark was crowded by bigger fish even there are still many fish available.)
            call_mom = true;
        }
        //* Check if All place is visited.
    }
    return total;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    memset(sea, 0, sizeof(sea));
    memset(visited, false, sizeof(visited));

    int input = 0;
    pair<int, int> pos;
    cin >> N;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> input;
            sea[i][j] = input;
            if(input == 9){ //* Baby shark init position.
                pos.first = i;
                pos.second = j;
                sea[i][j] = 0; //* Assume current space as empty
            }
        }
    }

    cout << eat(pos) << "\n";

    return 0;
}