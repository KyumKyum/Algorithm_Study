// Algorithm Study
// Backjoon: 집합의 표현 (1717)
// https://www.acmicpc.net/problem/1717

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
//* Practicing Disjoint Set

vector<int> parent;
vector<int> lev;
vector<bool> ans;

int find(int x){
    if(parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void merge(int x, int y){
    int root_x = find(x);
    int root_y = find(y);

    if(root_x == root_y) return;

    //* Shorter Tree will be a subtree of Longer tree.
    if(lev[root_x] < lev[root_y]) swap(root_x, root_y);
    parent[root_y] = root_x;

    if(lev[root_x] == lev[root_y]) lev[root_x]++;

    return;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N = 0, M = 0;

    cin >> N >> M;

    //* Init
    for(int i = 0; i <= N; i++){
        parent.push_back(i);
    }

    lev = vector<int>(parent.size() + 1, 1);

    for(int i = 0; i < M; i++){
        int op = 0, a = 0, b = 0;
        cin >> op >> a >> b;
        if(op == 0){
            merge(a,b);
        }else if(op == 1){
            ans.push_back(find(a) == find(b));
        }
    }

    int size = ans.size();
    for(int i = 0; i < size; i++){
        if(ans[i]) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}