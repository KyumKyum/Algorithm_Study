#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

#define ll long long

using namespace std;

const ll INF = LLONG_MAX;

vector<pair<int, int>> adj[1001];
ll trace[1001];
int parent[1001];

int n, m, start, destination;

void dijkstra(int src) {
  fill(trace, trace + 1001, INF);
  fill(parent, parent + 1001, 0);

  trace[src] = 0;
  parent[src] = 0;

  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>>
      pq;

  pq.emplace(0, src);

  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();

    if (d > trace[u])
      continue;

    for (auto &[v, w] : adj[u]) {
      if (trace[v] > d + w) {
        trace[v] = d + w;
        parent[v] = u;
        pq.emplace(trace[v], v);
      }
    }
  }
}

vector<int> buildPath(int s, int d) {
  vector<int> path;
  for (int cur = d; cur != 0; cur = parent[cur]) {
    path.push_back(cur);
  }
  reverse(path.begin(), path.end());
  return path;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
  }
  cin >> start >> destination;

  dijkstra(start);

  cout << trace[destination] << "\n";

  auto path = buildPath(start, destination);
  cout << path.size() << "\n";
  for (int x : path) {
    cout << x << " ";
  }
  cout << "\n";

  return 0;
}
