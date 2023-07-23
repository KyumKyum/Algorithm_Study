// Algorithm Study
// Backjoon: 할로윈의 양아치 (20303)
// https://www.acmicpc.net/problem/20303

#include <iostream>
#include <cstring>
#include <vector>
#include <iterator>
#include <algorithm>
#include <queue>

using namespace std;

//* Strategy: DP & Disjoint Set
//* Record Every Root for each friend.
//* If the root is same, the friend group will be the same.
//* Disjoint Set + BFS

struct knapsack{
    int weight;
    int value;
};

int parent[30010];
int lev[30010];
int candy[30010];
bool visited[30010];
int cache[30010][3010];
vector<knapsack> group;
queue<int> BFS;
vector<int> node[30010];

int N, M, K = 0;

int find_root(int e){
    if(parent[e] == -1){
        //* -1: Hadn't initialized: Root.
        return e;
    }

    return parent[e] = find_root(parent[e]); //* Recursively find parent, update it.
}

void make_friend(int x, int y){
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

    //* Merge Tree; y will be a new parent for x.
    parent[x] = y;

    //* If their level is same, increase parent-side level (level will be increased as 1. (new parent level created.))
    if(lev[x] == lev[y]){
        lev[y]++;
    }

    //* Add children info. node[parent] will have its children node. It will be used in BFS.
    node[y].push_back(x);

    return;
}

void merge_candy(int tgt){
    //* Group friend's candy in one group.
    //* Required procedure to solve in knapsack.
    int root = find_root(tgt);
    knapsack newGroup;
    int cur = 0;
    int weight = 0;
    int value = 0;

    if(visited[root]){
        //* This node had been visited! Same Set!
        //* No need to compute more.
        return;
    }
    visited[root] = true;
    BFS.push(root);

    while(!BFS.empty()){
        cur = BFS.front();
        //* Snatch!
        value += candy[cur];
        weight++;

        for(int i = 0; i < node[cur].size(); i++){
            BFS.push(node[cur][i]);
        }
        BFS.pop();
    }

    newGroup.value = value;
    newGroup.weight = weight;
    group.push_back(newGroup);
}

int snatch(int cryLimit, int groupNum){
    //* Default Knapsack Problem.

    int maxValue = 0;
    for(int tgt = 1; tgt <= groupNum; tgt++){
        for(int limit = 1; limit <= cryLimit; limit++) {
            if (limit < group[tgt-1].weight){
                cache[tgt][limit] = cache[tgt - 1][limit]; //* Not able to hold.
            }else{ //* Able to hold.
                cache[tgt][limit] = max(cache[tgt-1][limit], group[tgt-1].value + cache[tgt-1][limit-group[tgt-1].weight]);
                //* Didn't take
                //* or, put off current item and take the new one.
                    //* limit - grout[tgt].weight = remove item tgt.
                //* Update max value.
                maxValue = max(maxValue, cache[tgt][limit]);
            }
        }
    }

    return maxValue;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    fill(begin(parent), end(parent), -1);
    fill(begin(candy), end(candy), 0);
    fill(begin(lev), end(lev), 1);
    fill(begin(visited), end(visited), false);
    memset(cache, 0, sizeof(cache));
    int x ,y, size = 0;

    cin >> N >> M >> K;

    for(int i = 1; i <= N; i++){
        cin >> candy[i];
    }

    for(int i = 0; i < M; i++){
        cin >> x >> y;
        make_friend(x,y);
    }

    for(int i = 1; i <= N; i++){
        merge_candy(i);
    }

    /// * Solve like a knapsack problem.
    size = group.size();

    cout << snatch(K - 1, size) << "\n";

    return 0;
}