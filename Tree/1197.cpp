// Algorithm Study
// Backjoon: 최소 스패닝 트리 (1197)
// https://www.acmicpc.net/problem/1197

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//* Done by kruskal's algorithm

struct Node {
    int src;
    int dest;
    int dist; //* weight between the edges.

    Node(int _src, int _dest, int _dist){
        this->src = _src;
        this->dest = _dest;
        this->dist = _dist;
    }
};

bool compare(Node &node_a, Node &node_b){
    return node_a.dist < node_b.dist;
}

vector<Node> nodes;
vector<int> parent;

int V = 0, E = 0;

//* Union-find
int find(int x){
    if(parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

bool merge(int x, int y){
    int px = find(x);
    int py = find(y);

    if(px == py) return false; //* Already visited.

    parent[py] = px; //* Merge.
    return true;
}

long long kruskal(int edges){
    long long min_weight = 0;

    for(int i = 0; i < edges; i++){
        if(merge(nodes[i].src, nodes[i].dest)){
            //* Include as a tree.
            min_weight += nodes[i].dist;
        }
    }

    return min_weight;
}


int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> V >> E;

    //* Set Vertex Information.
    for(int i = 0; i <= V; i++){
        parent.push_back(i);
    }

    //* Get Input.
    for(int i = 0; i < E; i++){
        int a = 0, b = 0, c = 0;
        cin >> a >> b >> c;
        nodes.push_back(Node(a,b,c));
    }

    sort(begin(nodes), end(nodes), compare);

    cout << kruskal(E) << "\n";

    return 0;
}
