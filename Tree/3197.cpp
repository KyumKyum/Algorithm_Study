// Algorithm Study
// Backjoon: 백조의 호수 (3197)
// https://www.acmicpc.net/problem/3197

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

//* Idea: BFS + Disjoint Set
//* Init. Check All discrete space via BFS.
    //* By using queue, check next area to melt. (-2)
//* Check separation vis Disjoint Set.
//* Melt: Melt all area within queue, and
    //* Case 1: Next possible position is also an ice: push its position.
    //* Case 2: Next possible position is an empty space, but different area : Merge them.
//* If the place of two swans became union, terminate the process and return a result.
//* Assume swan as an empty space.

struct Melt_to{
    pair<int, int> pos;
    int change_to;

    Melt_to(pair<int, int> _pos, int _change_to){
        this->pos = _pos;
        this->change_to = _change_to;
    }
};

int lake[1501][1501];
queue< pair<int, int> > swan_pos;
queue< Melt_to > will_melt;
int swan_label[2];
vector<int> parent;
vector<int> lev;
bool discovered[1501][1501];

int R = 0, C = 0;



int dx[4] = {0, -1, 1, 0}; //Up, left, right, down
int dy[4] = {-1, 0, 0, 1};

int find(int x){
    if(parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void merge(int a, int b){
    int pa = find(a);
    int pb = find(b);

    if(pa == pb) return; //* Same Parent.

    if(lev[pa] > lev[pb]) swap(pa, pb);

    parent[pa] = pb;

    if(lev[pa] == lev[pb]) lev[pa]++;
    return;
}

void make_separation(int val, pair<int, int> pos){
    queue< pair<int, int> > q;
    discovered[pos.first][pos.second] = true;
    lake[pos.first][pos.second] = val;
    q.push(pos);

    while (!q.empty()){
        pair<int, int> cur = q.front();
        q.pop();

        for(int i = 0; i < 4; i++){
            int ny = cur.first + dy[i];
            int nx = cur.second + dx[i];

            if(ny < 0 || ny >= R || nx < 0 || nx >= C) continue;
            if(discovered[ny][nx]) continue;

            discovered[ny][nx] = true;

            if(lake[ny][nx] == -1){
                //* Target to be melted
                lake[ny][nx] = -2; //* Check
                will_melt.push(Melt_to(pair<int, int>(ny, nx), val));
                continue;
            }


            lake[ny][nx] = val;
            q.push(pair<int, int>(ny, nx));
        }
    }

    return;
}

int label(){
    int cnt = 1;
    int swan_cnt = 0;
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            if(lake[i][j] == 0){
                //* Make Separation
                make_separation(cnt, pair<int, int>(i, j));
                cnt++;
            }
            if(!swan_pos.empty() && swan_cnt < 2){
                if(swan_pos.front().first == i && swan_pos.front().second == j){
                    swan_label[swan_cnt++] = lake[i][j]; //* Memory swan's position.
                    swan_pos.pop();
                }
            }
        }
    }

    return cnt;
}

void melt(){
    int size = will_melt.size();

    for(int i = 0; i < size; i++){
        Melt_to cur = will_melt.front();
        lake[cur.pos.first][cur.pos.second] = cur.change_to; //* Melted.
        for(int idx = 0; idx < 4; idx++){
            int ny = cur.pos.first + dy[idx];
            int nx = cur.pos.second + dx[idx];

            if(ny < 0 || ny >= R || nx < 0 || nx >= C) continue;
            if(lake[ny][nx] == -1){
                lake[ny][nx]= -2;
                will_melt.push(Melt_to(pair<int, int>(ny, nx), cur.change_to));
            }else if(lake[ny][nx] > 0 && lake[ny][nx] != lake[cur.pos.first][cur.pos.second]){
                //* If melted area meets another empty area, merge them.
                merge(lake[ny][nx], lake[cur.pos.first][cur.pos.second]);
            }
        }

        will_melt.pop();
    }

    return;
}

int required_days(){
    int days = 0;
    while(find(swan_label[0]) != find(swan_label[1])){
        days++;
        melt();
    }
    return days;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    memset(discovered, false, sizeof(discovered));

    cin >> R >> C;

    for(int i = 0; i < R; i++){
        string row;
        cin >> row;
        for(int j = 0; j < C; j++){
            if(row[j] == '.') lake[i][j] = 0; //* Empty
            else if(row[j] == 'L') {
                lake[i][j] = 0;
                swan_pos.push(pair<int, int>(i, j));
            } //* Swan
            else lake[i][j] = -1; //* Wall.
        }
    }

    int num_of_parent = label();


    for(int i = 0; i <= num_of_parent; i++){
        parent.push_back(i);
        lev.push_back(1);
    }



    cout << required_days() << "\n";
    return 0;
}

