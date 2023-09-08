// Algorithm Study
// Backjoon: 플로이드 (11404)
// https://www.acmicpc.net/problem/11404

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <limits.h>

const int INF = INT_MAX / 2; //* Prevent Overflow.

using namespace std;

//* Idea: Floyd-Warshall

vector< pair<int, int> > adj[101];
int dist[101][101];
int N = 0, M = 0;

void floyd_warshall(){

    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            dist[i][j] = INF;
        }
    }
    for(int i = 1; i <= N; i++){
        int size = adj[i].size();
        dist[i][i] = 0; //* Same place == 0;
        for(int j = 0; j < size; j++){
            //* There could be multiple possible path exist. Record the minimum.
            dist[i][adj[i][j].first] = min(dist[i][adj[i][j].first], adj[i][j].second);
        }
    }

    for(int mid = 1; mid <= N; mid++){
        //* Mid - node in the middle.
        for(int i = 1; i <= N; i++){
            for(int j = 1; j <= N; j++){
                if(i == mid || j == mid) continue; //* mid must be a middle node.
                dist[i][j] = min(dist[i][j], dist[i][mid] + dist[mid][j]); //* Get the minimum value.
            }
        }
    }

    for(int i = 1; i <=N; i++){
        for(int j = 1; j <= N; j++){
            if(dist[i][j] == INF) cout << "0 ";
            else cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(dist, 0, sizeof(dist));

    cin >> N >> M;

    for(int i = 0; i < M; i++){
        int a = 0, b = 0, c = 0;
        cin >> a >> b >> c;

        adj[a].push_back(make_pair(b,c));
    }

    floyd_warshall();
    return 0;
}