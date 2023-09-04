// Algorithm Study
// Backjoon: 웜홀 (1865)
// https://www.acmicpc.net/problem/1865

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

//* Idea: Bellman-Ford

vector<string> ans;

int TC = 0, N = 0, M = 0, W = 0;

bool check_loop(vector<long long> relaxed, vector<pair<int, int> > adj[]){
    for(int here = 1; here <= N; here++){
        int size = adj[here].size();
        for(int next = 0; next < size; next++){
            int there = adj[here][next].first;
            long long cost = adj[here][next].second + relaxed[here];
            if(relaxed[there] > cost){
                //* Relax should not be happened!
                //* Check if is reachable.
                return true;
                //if(relaxed[here] < INF/10) return true; //* Reachable from starting point -> Has infinite loop
            }
        }
    }

    return false; //* No infinite loop
}

bool has_infinite_loop(vector<pair<int, int> > adj[]){
    //* Bellman-Ford Algorithm.
    vector<long long> relaxed = vector<long long>(N+1, 0); //* No need for INF.
    //* Only check if there is an infinite cycle.
//    relaxed[1] = 0; //* Every point can be starting point.

    for(int itr = 0; itr < N-1; itr++){
        for(int here = 1; here <= N; here++){
            int size = adj[here].size();
            for(int next = 0; next < size; next++){
                int there = adj[here][next].first;
                long long cost = adj[here][next].second + relaxed[here];
                relaxed[there] = min(relaxed[there], cost); //* Relaxation
            }
        }
    }
    return check_loop(relaxed, adj);
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> TC;

    for(int i = 0; i < TC; i++){
        int s = 0, e = 0, t = 0;
        vector< pair<int, int> > adj[501];
        cin >> N >> M >> W;

        for(int j = 0; j < M; j++){

            cin >> s >> e >> t;

            //* Road will be bi-directional
            adj[s].push_back(make_pair(e,t)); //* Edge
            adj[e].push_back(make_pair(s,t)); //* Edge
        }

        for(int j = 0; j < W; j++){
            cin >> s >> e >> t;
            //* Wormholes will be uni-directional.
            adj[s].push_back(make_pair(e, -t)); //* Edge; Wormholes.
        }

        if(has_infinite_loop(adj)) ans.push_back("YES");
        else ans.push_back("NO");
    }

    int size = ans.size();
    for(int i = 0; i < size; i++) cout << ans[i] << "\n";

    return 0;
}