// Algorithm Study
// Backjoon: 도시 분할 계획 (1674)
// https://www.acmicpc.net/problem/1647

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

//* Idea: MST
//* Record longest distance between mst, and remove it.
//* Done by prim's algorithm.

struct Node {
    int dest;
    int dist; //* weight between the edges.

    Node(int _dest, int _dist){
        this->dest = _dest;
        this->dist = _dist;
    }
};

struct cmp{
    bool operator()(Node &node_a, Node &node_b){
        return node_a.dist > node_b.dist;
    }
};

vector<Node> nodes[100001];
vector<bool> visited;

priority_queue<Node, vector<Node>, cmp> pq;

int N = 0, M = 0; //* N == V, M == E

long long prim(){
    long long min_dist = 0;
    int maximum_dist = 0;

    //* Put information for starting edge.
    int first_size = nodes[1].size();
    for(int i = 0; i < first_size; i++){
        pq.push(nodes[1][i]);
    }

    visited[1] = true;

    while(!pq.empty()){
        //* 1. Get the next vertex.
        Node cur = pq.top();
        pq.pop();

        if(visited[cur.dest]) continue;

        visited[cur.dest] = true;
        min_dist += cur.dist;
        maximum_dist = max(maximum_dist, cur.dist);

        int cur_size = nodes[cur.dest].size();

        //* Check all possible path.
        for(int i = 0; i < cur_size; i++){
            if(visited[nodes[cur.dest][i].dest]) continue; //* no need to check visited vertex.
            pq.push(nodes[cur.dest][i]);
        }
    }

    return min_dist - maximum_dist; //* Need to remove the maximum distance; The mayor will cut off one of the rode.
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> N >> M;

    for(int i = 0; i <= N; i++){
        visited.push_back(false); //* Init
    }

    for(int i = 0; i < M; i++){
        int a = 0, b = 0, c = 0;
        cin >> a >> b >> c;

        //* NEED TO SAVE IN BOTH DIRECTION!!!
        nodes[a].push_back(Node(b,c));
        nodes[b].push_back(Node(a,c));
        //* There will be weight c for edge connecting vertex a and b.
    }

    cout << prim() << "\n";

    return 0;
}