// Algorithm Study
// Backjoon: 서강그라운드 (14938)
// https://www.acmicpc.net/problem/14938

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits.h>

using namespace std;

//* Idea: Dijkstra
//* It can also be solved via Floyd-Warshall

struct cmp{
    bool operator()(pair<int, int> &_p1, pair<int, int> &_p2){
        return _p1.second > _p2.second;
    }
};

vector<int> field;
vector< pair<int, int> > route[101];

int N = 0, M = 0, R = 0; // Vertex, Recon, Edge

vector<int> dijkstra(int start){
    vector<int> dist = vector<int>(N+1, INT_MAX);
    priority_queue<pair<int, int>, vector< pair<int, int> >, cmp> pq;
    //* Init.
    pq.push(make_pair(start, 0));
    dist[start] = 0;

    while(!pq.empty()){
        int cur = pq.top().first;
        int cost = pq.top().second;
        pq.pop();

        int size = route[cur].size();

        for(int i = 0; i < size; i++){
            int next = route[cur][i].first;
            int next_cost = route[cur][i].second + cost;

            if(dist[next] <= next_cost) continue;
            dist[next] = next_cost;
            pq.push(make_pair(next, next_cost));
        }
    }

    return dist;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int maximum_loot = 0;

    cin >> N >> M >> R;

    field = vector<int>(N+1, 0);
    for(int i = 1; i <= N; i++){
        cin >> field[i]; //* Get Item info.
    }

    for(int i = 0; i < R; i++){
        int v1 = 0, v2 = 0, e = 0;
        cin >> v1 >> v2 >> e;

        //* Bi-Directional
        route[v1].push_back(make_pair(v2, e));
        route[v2].push_back(make_pair(v1, e));
    }

    for(int i = 1; i <= N; i++){
        vector<int> dist = dijkstra(i);
        int possible_loot = 0;

        for(int j = 1; j <= N; j++){
            if(dist[j] <= M) possible_loot += field[j];
        }
        maximum_loot = max(maximum_loot, possible_loot);
    }

    cout << maximum_loot << "\n";

    return 0;
}