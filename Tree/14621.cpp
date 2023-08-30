// Algorithm Study
// Backjoon: 나만 안되는 연애 (14621)
// https://www.acmicpc.net/problem/14621

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//* Idea: MST
//* If the connected vector are the same type, skip it. (Not a target edge)
//* If the possible edges are less than N-1, print -1.
//* Done by kruskal's algorithm

struct Node {
    int from;
    int to;
    int dist; //* weight between the edges.

    Node(int _from, int _to, int _dist){
        this->from = _from;
        this->to = _to;
        this->dist = _dist;
    }
};

bool compare(Node &node_a, Node &node_b){
    return node_a.dist < node_b.dist;
}

vector<Node> nodes;
vector<char> univ_type;
vector<int> parent;

int N = 0, M = 0;

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

int get_mst(){
    int size = nodes.size();
    int num_edges = 0;
    int min_dist = 0;

    for(int i = 0; i < size; i++){
        if(!merge(nodes[i].from, nodes[i].to)) continue; //* Already in MST.

        min_dist += nodes[i].dist;
        num_edges++;
    }

    if(num_edges < N-1){
        //* Didn't meet the minimum requirement.
        return -1;
    }
    return min_dist;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> N >> M;
    parent.push_back(0); //* init.
    univ_type.push_back('E'); //* init.

    for(int i = 1; i <= N; i++){
        char type;
        cin >> type;
        univ_type.push_back(type);
        parent.push_back(i);
    }

    for(int i = 0; i < M; i++){
        int u = 0, v = 0, d = 0;
        cin >> u >> v >> d;

        if(univ_type[u] == univ_type[v]) continue; //* Connected with the same type.

        nodes.push_back(Node(u,v,d));
    }

    sort(begin(nodes), end(nodes), compare);

    cout << get_mst() << "\n";

    return 0;
}