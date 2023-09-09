// Algorithm Study
// Backjoon: 최단경로 (1753)
// https://www.acmicpc.net/problem/1753

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits.h>

using namespace std;

//* Idea: Dijkstra
const int INF = INT_MAX/2;

struct cmp{
    bool operator()(pair<int, int> &_a, pair<int, int> &_b){
        return _a.second > _b.second;
    }
};

vector< pair<int,int> > adj[20001];
int V = 0, E = 0, K = 0;

vector<int> dijkstra(){
    vector<int> dist = vector<int>(V+1, INF);
    priority_queue< pair<int, int>, vector< pair<int, int> >, cmp> pq;

    //*init
    dist[K] = 0;
    pq.push(make_pair(K,0));

    while(!pq.empty()){
        int cur = pq.top().first;
        int cost = pq.top().second;
        pq.pop();

        int size = adj[cur].size();
        for(int i = 0; i < size; i++){
            int next = adj[cur][i].first;
            int estimated_cost = adj[cur][i].second + cost;
            if(dist[next] > estimated_cost){
                dist[next] = estimated_cost;
                pq.push(make_pair(next, estimated_cost));
            }
        }
    }

    return dist;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> V >> E;
    cin >> K;

    for(int i = 0; i < E; i++){
        int u = 0, v = 0, w = 0;
        cin >> u >> v >> w;
        adj[u].push_back(make_pair(v,w));
    }

    vector<int> dist = dijkstra();

    for(int i = 1; i <= V; i++){
        if(dist[i] == INF) cout << "INF\n";
        else cout << dist[i] << "\n";
    }

    return 0;
}