// Algorithm Study
// Backjoon: ACM Craft (1005)
// https://www.acmicpc.net/problem/1005

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

//* Idea: Topological Sort.
//* Same in_degree == Maximum time for unit will be building time.

struct Unit{
    int idx;
    int delay;

    Unit(int _idx, int _delay){
        this->idx = _idx;
        this->delay = _delay;
    }
};

vector<int> ans;

int build(vector<int> adj[], vector<Unit> units, int in_degree[], int dest, int N){
    queue<int> t_sort;
    vector<int> dp_delay(N+1, 0);
    //* Find the starting point.
    //* Initialize time for build
    for(int i = 1; i <= N; i++){
        if(in_degree[i] <= 0) {
            //* Init building to build.
            dp_delay[i] = units[i].delay;
            t_sort.push(i);
        }
    }

    while(!t_sort.empty()){
        int cur = t_sort.front();
        t_sort.pop();
        //* Builds.
        //elapsed += units[cur].delay;

        //* If current unit is destination, ends the process.
        if(cur == dest) break;

        //* Remove in_degree connected.
        int size = adj[cur].size();
        for(int i = 0; i < size; i++){
            int next = adj[cur][i];
            in_degree[next]--; //* Remove in_degree

            //* DP Build Delay
            //* Required to build all required building before, get the maximum delay time.
            dp_delay[next] = max(dp_delay[next], dp_delay[cur] + units[next].delay);

            //* If connected vertex now has 0 in_degree, push into the queue.
            if(in_degree[next] <= 0) t_sort.push(next);
        }
    }

    return dp_delay[dest];
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int tc;
    cin >> tc;

    for(int i = 0; i < tc; i++){
        int in_degree[1001];
        vector<int> adj[1001];
        vector<Unit> units;
        int N = 0, K = 0, W = 0;
        memset(in_degree, 0, sizeof(in_degree));

        cin >> N >> K;

        units.push_back(Unit(0, 0)); //* Dummy Data;

        //* Get Unit Information
        for(int j = 1; j <= N; j++){
            int d = 0;
            cin >> d;
            units.push_back(Unit(j, d));
        }

        //* Get Route Information
        for(int j = 0; j < K; j++){
            int x = 0, y = 0;
            cin >> x >> y;
            adj[x].push_back(y);
            in_degree[y]++;
        }

        //* Get destination
        cin >> W;

        ans.push_back(build(adj, units, in_degree, W, N));
    }

    int size = ans.size();
    for(int i = 0; i < size; i++){
        cout << ans[i] << "\n";
    }

    return 0;
}