// Algorithm Study
// Backjoon: 교수님은 기다리지 않는다. (3830)
// https://www.acmicpc.net/problem/3830

#include <iostream>
#include <vector>

using namespace std;

//* Idea : Disjoint Set
//* If the student examined, make as an union.
//* If they are has a different parent, it means they had not examined.

vector<int> parent;
vector<long long> weight;

int N, M = 0;

int find(int x){
    if(parent[x] == x) return x;
    int p = find(parent[x]);
    weight[x] += weight[parent[x]]; //* Weight: weight x ~ parent[x] + parent[x] ~ root
    return parent[x] = p;
}

void merge(int a, int b, int w){
    int pa = find(a);
    int pb = find(b);

    if(pa == pb) return;

    //* Pa -> root for all tree.
    //* Pass the heavier element to child
    weight[pb] = weight[a] - weight[b] + w;
    parent[pb] = pa; //* Make pa as a root.

    return;
}


int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    while(true){
        cin >> N >> M;

        if(N == 0 && M == 0) break;

        parent.clear();
        weight.clear();

        for(int i = 0; i <= N; i++){
            parent.push_back(i);
            weight.push_back(0);
        }

        for(int i = 0; i < M; i++){
            char op;
            int a, b;
            cin >> op;
            if(op == '?'){
                cin >> a >> b;
                if(find(a) != find(b)) cout << "UNKNOWN\n";
                else cout << weight[b] - weight[a] << "\n";
            }else{ //* Examine
                long long w;
                cin >> a >> b >> w;
                merge(a,b,w);
            }
        }
    }

    return 0;
}
