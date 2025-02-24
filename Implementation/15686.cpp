#include <climits>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

short N, M = 0;
vector<pair<short, short>> housePos;
vector<pair<short, short>> chickenPos;
int houseNum = 0;
int chickenNum = 0;
int minRange = INT_MAX;
int dist[10000][20];
pair<short, short> selected[20];

// Precompute distances
void computeDistances() {
  for (int i = 0; i < houseNum; i++) {
    for (int j = 0; j < chickenNum; j++) {
      dist[i][j] = abs(housePos[i].first - chickenPos[j].first) +
                   abs(housePos[i].second - chickenPos[j].second);
    }
  }
}

// Calculate minimum chicken distance for current selection
void search() {
  int calculated = 0;

  for (int i = 0; i < houseNum; i++) {
    int curMinRange = INT_MAX;
    for (int j = 0; j < M; j++) {
      int chickenIdx = selected[j].second; // Store original chicken index
      curMinRange = min(curMinRange, dist[i][chickenIdx]);
    }

    calculated += curMinRange;
    if (calculated >= minRange)
      return; // Prune search early
  }

  minRange = min(minRange, calculated);
}

// Recursive selection of chicken stores
void select(short idx, short num) {
  if (num == M) {
    search();
    return;
  }
  for (int i = idx; i < chickenNum; i++) {
    selected[num] = {chickenPos[i].first, i}; // Store index for distance lookup
    select(i + 1, num + 1); // Ensure next selection starts from i+1
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> N >> M;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      short type;
      cin >> type;
      if (type == 1) {
        housePos.push_back({i, j});
      } else if (type == 2) {
        chickenPos.push_back({i, j});
      }
    }
  }

  houseNum = housePos.size();
  chickenNum = chickenPos.size();

  computeDistances();
  select(0, 0);

  cout << minRange << endl;
  return 0;
}
