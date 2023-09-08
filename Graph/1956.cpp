// Algorithm Study
// Backjoon: 운동 (1956)
// https://www.acmicpc.net/problem/1956

#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>
#include <cstring>

using namespace std;

//* Idea: Floyd-Warshall
const int INF = INT_MAX / 2;
vector< pair<int, int> > adj[401];
int dist[401][401];
int V = 0, E = 0;

int workout(){
    int result = INF;

    for(int i = 1; i <= V; i++){
        int size = adj[i].size();
        for(int j = 0; j < size; j++){
            dist[i][adj[i][j].first] = adj[i][j].second;
        }
    }

    //* Floyd-Warshall

    for(int k = 1; k <= V; k++){
        for(int i = 1; i <= V; i++){
            for(int j = 1; j <= V; j++){
                //* Remove condition if (i==j) continue;
                if(i == k || k == j) continue; //* k must be in the middle.
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }


    for(int i = 1; i <= V; i++){
        result = min(result, dist[i][i]);
        //* Get the minimum value that makes a cycle.
    }

    return (result == INF) ? -1 : result;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(dist, 0, sizeof(dist));

    cin >> V >> E;
    //* Set up
    for(int i = 1; i <= V; i++){
        for(int j = 1; j <= V; j++){
            //* REMOVE i==j continue; There could be a cycle; there will be a way to return it's original place.
            dist[i][j] = INF;
        }
    }

    for(int i = 0; i < E; i++){
        int a = 0, b = 0, c = 0;
        cin >> a >> b >> c;
        adj[a].push_back(make_pair(b,c));
    }

    cout << workout() << "\n";
    return 0;
}

