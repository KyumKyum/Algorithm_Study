#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#define INF 1'000'000'000

using namespace std;

vector<pair<int, int>> adj[2001]; // adj[u] = {v, weight}
int dist_s[2001], dist_g[2001], dist_h[2001];
vector<int> candidates;

void dijkstra(int start, int dist[]) {
  fill(dist, dist + 2001, INF);
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

  dist[start] = 0;
  pq.push({0, start});

  while (!pq.empty()) {
    pair<int, int> cur = pq.top();
    pq.pop();

    int u = cur.second;
    int cur_dist = cur.first;

    if (dist[u] < cur_dist) // Already found a shortest path.
      continue;

    for (pair<int, int> a : adj[u]) {
      int v = a.first;
      int cost = a.second;
      if (dist[v] > dist[u] + cost) {
        dist[v] = dist[u] + cost;
        pq.push({dist[v], v});
      }
    }
  }
}

void solve() {
  int T;
  cin >> T;

  while (T--) {
    int n, m, t, s, g, h;
    cin >> n >> m >> t;
    cin >> s >> g >> h;

    // clear graph
    for (int i = 1; i <= n; ++i)
      adj[i].clear();
    candidates.clear();

    int gh_dist = 0; // distance between g - h

    for (int i = 0; i < m; ++i) {
      int a, b, d;
      cin >> a >> b >> d;
      adj[a].emplace_back(b, d);
      adj[b].emplace_back(a, d);

      // store the g-h edge weight
      if ((a == g && b == h) || (a == h && b == g)) {
        gh_dist = d;
      }
    }

    for (int i = 0; i < t; ++i) {
      int x;
      cin >> x;
      candidates.push_back(x);
    }

    // run Dijkstra from s, g, h
    dijkstra(s, dist_s); // starting from s
    dijkstra(g, dist_g); // starting from g
    dijkstra(h, dist_h); // starting from h

    vector<int> result;

    for (int dest : candidates) {
      int via_gh =
          dist_s[g] + gh_dist +
          dist_h[dest]; // Shortest path from s -> g + gh_dist + shortest path
                        // from h -> dest (s -> g -> h -> dest)
      int via_hg =
          dist_s[h] + gh_dist +
          dist_g[dest]; // Shortest path from s -> h + gh_dist + shortest path
                        // from g -> dest (s -> h -> g -> dest)

      if (dist_s[dest] == via_gh ||
          dist_s[dest] == via_hg) { // Shortest path must passed the road g - h
        result.push_back(dest);
      }
    }

    sort(result.begin(), result.end());
    for (int x : result)
      cout << x << ' ';
    cout << '\n';
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  solve();
}
