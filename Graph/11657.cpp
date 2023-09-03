// Algorithm Study
// Backjoon: 타임머신 (11657)
// https://www.acmicpc.net/problem/11657

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdint.h>

using namespace std;

//* Idea: Practicing Bellman-Ford.
//* IMPORTANT FEATURE: Need to check if it is reachable. (If the infinite cycle is unreachable to vertex connected to starting, it is still possible case.)

vector<pair <int, int> > adj[501];

const long long INF = INT64_MAX/2;

int N = 0, M = 0;

vector<long long> bellman_ford(int start){
    vector<long long> relaxed(N+1, INF); //* INT_MAX at long long type: prevent overflow while comparing

    //* Init.
    relaxed[start] = 0;
    bool is_updated = false;

    for(int i = 0; i < N; i++){
        //* Will iterate N amount.
       is_updated = false;

       for(int cur = 1; cur <= N; cur++){
           int cur_size = adj[cur].size();
           for(int next = 0; next < cur_size; next++){
               long long next_vertex = adj[cur][next].first;
               long long next_cost = adj[cur][next].second + relaxed[cur];
               if(relaxed[next_vertex] <= next_cost) continue;

               //* Update Happens.
               relaxed[next_vertex] = next_cost;
               is_updated = true;
               if(i == N-1){ //* At the last cycle if update happens, it means there is an infinite cycle.
                   //* Check if it is reachable.
                   if(relaxed[cur] >= INF/10) is_updated = false; //* Current vertex is not reachable from start 1. If was reachable, it will be lesser than INF/10
               }
           }
       }
       if(!is_updated) break; //* This SHOULD be executed if there is no cycle in current graph.
    }

    if(is_updated) relaxed[0] = -1; //* There is a cycle.
    else relaxed[0] = 0;

    return relaxed;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> N >> M;

    for(int i = 0; i < M; i++){
        int a = 0, b = 0, c = 0;
        cin >> a >> b >> c;

        //Uni-directional.
        adj[a].push_back(make_pair(b , c));
        //* Check they are reachable.
    }

    vector<long long> relaxed = bellman_ford(1);

    if(relaxed[0] == -1) cout << "-1\n"; //* Infinite Cycle.
    else {
        int size = relaxed.size();
        for(int i = 2; i < size; i++){ //* Print minimum path from city 1; ignore city 1.
            if(relaxed[i] > INF/10) cout << "-1\n"; //* INFINITE - M, M stands for "reasonably bigger value."
            else cout << relaxed[i] << "\n";
        }
    }

    return 0;
}