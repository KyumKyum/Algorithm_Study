#include <algorithm>
#include <iostream>
#include <vector>

#define MAX 50001

using namespace std;

vector<int> tree[MAX];
int parent[MAX], depth[MAX];
int N, M;

void dfs(int node, int p) {
  parent[node] = p;
  for (int child : tree[node]) {
    if (child == p)
      continue;
    depth[child] = depth[node] + 1;
    dfs(child, node);
  }
}

int lca(int u, int v) {
  // ensure u is the deeper node
  if (depth[u] < depth[v])
    swap(u, v);

  // climb u up until both depths match
  while (depth[u] > depth[v])
    u = parent[u];

  // climb both until they meet
  while (u != v) {
    u = parent[u];
    v = parent[v];
  }

  return u;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N;
  // read exactly N-1 edges
  for (int i = 0; i < N - 1; i++) {
    int a, b;
    cin >> a >> b;
    tree[a].push_back(b);
    tree[b].push_back(a);
  }

  depth[1] = 0; // choose 1 as the root
  dfs(1, 0);    // parent of root = 0 (unused)

  cin >> M;
  while (M--) {
    int u, v;
    cin >> u >> v;
    cout << lca(u, v) << '\n';
  }

  return 0;
}
