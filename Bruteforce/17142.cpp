#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

short lab[51][51] = {0};
short N, M = 0;

vector<pair<int, int>> virusPos;

int seconds = INT_MAX;

short dx[4] = {-1, 0, 1, 0};
short dy[4] = {0, 1, 0, -1};

bool isValid(int px, int py) { return px >= 0 && px < N && py >= 0 & py < N; }

void propagate(vector<pair<int, int>> v) {
  int visited[51][51] = {-1};
  memset(visited, -1, sizeof(visited));
  int sec = 0;
  queue<pair<int, int>> q;
  for (int i = 0; i < v.size(); i++) {
    q.push(v[i]);
    visited[v[i].first][v[i].second] = 0; // Init time
  }

  while (!q.empty()) {
    pair<int, int> pos = q.front();
    q.pop();

    int x = pos.first;
    int y = pos.second;

    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];

      if (isValid(nx, ny) && visited[nx][ny] == -1 && lab[nx][ny] != 1) {
        // Propagate!
        visited[nx][ny] = visited[x][y] + 1;
        if (lab[nx][ny] == 0) {
          // Update time if the virus spreaded in vacant area
          sec = max(sec, visited[nx][ny]);
        }
        q.push({nx, ny});
      }
    }
  }

  // Check if all contaminated
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (visited[i][j] == -1 && lab[i][j] == 0) {
        // Unvisited area while the area is vacant. This is not the possible
        // case.
        return;
      }
    }
  }

  // All contaminated
  seconds = min(seconds, sec);
  return;
}

void activate(int cnt, int init, vector<pair<int, int>> v) {
  if (cnt >= M) {
    // Selected viruses to activate, propagate them
    propagate(v);
  } else {
    for (int i = init; i < virusPos.size(); i++) {
      v.push_back(virusPos[i]);
      activate(cnt + 1, i + 1, v);
      v.pop_back();
    }
  }
}

int main(void) {
  cin.tie(0);

  cin >> N >> M;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> lab[i][j];

      if (lab[i][j] == 2) {
        // Virus
        virusPos.push_back({i, j});
      }
    }
  }

  vector<pair<int, int>> v;

  activate(0, 0, v);

  if (seconds == INT_MAX)
    cout << -1 << endl;
  else
    cout << seconds << endl;
  return 0;
}
