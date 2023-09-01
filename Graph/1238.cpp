// Algorithm Study
// Backjoon: 파티 (1238)
// https://www.acmicpc.net/problem/1238

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

//* Idea: Dijkstra
//* Practicing dijkstra.
//* Need to get both forward and backward.
//* Backward: X -> A. Dijkstra starting from x.
//* Forward: A -> X. Dijkstra starting from x, INVERTED path information. (a->b => b->a)

struct cmp{
    bool operator()(pair<int, int> &a, pair<int, int> &b){
        return a.second > b.second;
    }
};



int N = 0, M = 0, X = 0;

vector<int> dijkstra(vector< pair<int, int> > adj[] ,int start){
    vector< int > dist;

    for(int i = 0; i <= N; i++){
        dist.push_back(INT_MAX); //* Init.
    }

    dist[start] = 0; //* Starting node;
    priority_queue< pair<int, int>, vector<pair<int, int> >, cmp > pq;
    pq.push(pair<int, int>(start, 0));

    while (!pq.empty()){
        pair<int, int> cur = pq.top(); pq.pop();

        int cur_node = cur.first;
        int cur_dist = cur.second;
        int size = adj[cur_node].size();

        for(int i = 0; i < size; i++){
            int next_node = adj[cur_node][i].first;
            int next_dist = adj[cur_node][i].second + cur_dist;

            if(dist[next_node] > next_dist){
                //* Shorter path; update.
                dist[next_node] = next_dist;
                pq.push(pair<int, int>(next_node, next_dist));
            }
        }
    }

    return dist;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int max_weight = 0;
    cin >> N >> M >> X;

    vector< pair<int, int> > forward[1001];
    vector<pair<int, int> > backward[1001];

    for(int i = 0; i < M; i++){
        int from = 0, to = 0, time = 0;
        cin >> from >> to >> time;

        forward[to].push_back(pair<int, int>(from, time)); //* Inverted. A -> X will be calculated as X -> A with inverted path.
        backward[from].push_back(pair<int, int>(to, time)); //* X -> A
    }

    vector<int> a_to_x = dijkstra(forward, X);
    vector<int> x_to_a = dijkstra(backward, X);

    for(int i = 1; i <= N; i++){
        max_weight = max(max_weight, a_to_x[i] + x_to_a[i]);
    }

    cout << max_weight << "\n";

    return 0;
}
