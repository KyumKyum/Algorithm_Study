// Algorithm Study
// Backjoon: 거짓말 (1043)
// https://www.acmicpc.net/problem/1043

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

//* Strategy: Disjoint Set
//* Record root for every friend. Related firend will have same root.
//* Prune group which shares same root with friend knows truth.

int parent[60];
int lev[60];
vector<int> prune;
vector<int> group[60];
int N,M = 0;

int find_root(int e){
    if(parent[e] == -1){
        //* This hasn't been initialized. == Root.
        return e;
    }

    return parent[e] = find_root(parent[e]); //* set compression
}

void make_group(int x, int y){
    //* Find root
    x = find_root(x);
    y = find_root(y);

    //* If they are the same set, there is no need to make them as friend. (They are already a friend!)
    if(x == y){
        return;
    }

    //* If their tree level is different, tree with lower level will be inserted as a child.
    if(lev[x] > lev[y]){
        swap(x,y);
    }

    //* Merge Graph; y will be a new parent for x.
    parent[x] = y;

    //* If their level is same, increase parent-side level (level will be increased as 1. (new parent level created.))
    if(lev[x] == lev[y]){
        lev[y]++;
    }

    return;
}

int tell_lie(void){
    int possible = M;
    int prune_size = prune.size();
    bool tell_lie = true;

    for(int i = 0; i < M; i++){
        int size = group[i].size();
        tell_lie = true;
        for(int j = 0; j < size; j++){
            if(!tell_lie){
                //* Not possible; break;
                break;
            }
            for(int k = 0; k < prune_size; k++){
                if(find_root(group[i][j]) == find_root(prune[k])){
                    //* This group has people who know the truth.
                    tell_lie = false;
                    possible -= 1;
                    break;
                }
            }
        }
    }

    return possible;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    fill(begin(parent), end(parent), -1);
    fill(begin(lev), end(lev), 1);

    int prune_num, tgt = 0;
    int incoming, person = 0;

    cin >> N >> M;

    cin >> prune_num;

    for(int i = 0; i < prune_num; i++){
        cin >> tgt;
        prune.push_back(tgt);
    }

    for(int i = 0; i < M; i++){
        int prev = 0;
        cin >> incoming;
        for(int j = 0; j < incoming; j++){
            if(j > 0){
                prev = person;
                cin >> person;
                make_group(prev, person);
            }else{
                cin >> person;
            }
            group[i].push_back(person);
        }
    }

    if(prune_num > 0){
        //* Search additional root shares with friends knows truth.
        cout << tell_lie() << "\n";
    }else{
        //* Tell lie to all groups!
        cout << M << "\n";
    }

    return 0;
}






