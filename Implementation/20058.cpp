#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <queue>
#include <utility>

using namespace std;

int ice[65][65];
bool visited[65][65];
int N, Q = 0;
int iceSize = 0;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int getLev(int lev) { return (int)pow(2, lev); }

bool isValid(int nx, int ny) {
  return nx >= 0 && nx < iceSize && ny >= 0 && ny < iceSize;
}

pair<int, int> findNonVisited() {
  for (int i = 0; i < iceSize; i++) {
    for (int j = 0; j < iceSize; j++) {
      if (!visited[i][j] && ice[i][j] > 0) {
        return {i, j};
      }
    }
  }
  return {-1, -1}; // All viisted;
}

pair<int, int> getAns() {
  memset(visited, false, sizeof(visited));
  int maxSize = 0;
  int total = 0;

  while (true) {
    pair<int, int> notVisited = findNonVisited();
    if (notVisited.first == -1)
      break;

    queue<pair<int, int>> q;
    q.push(notVisited);
    visited[notVisited.first][notVisited.second] = true;

    int size = 1;
    total += ice[notVisited.first][notVisited.second];

    while (!q.empty()) {
      pair<int, int> cur = q.front();
      q.pop();
      for (int i = 0; i < 4; i++) {
        int nx = cur.first + dx[i];
        int ny = cur.second + dy[i];
        if (isValid(nx, ny) && !visited[nx][ny] && ice[nx][ny] > 0) {
          visited[nx][ny] = true;
          size++;
          total += ice[nx][ny];
          q.push({nx, ny});
        }
      }
    }

    maxSize = max(maxSize, size);
  }

  return {total, maxSize};
}

void meltdown() {
  int temp[65][65];
  memcpy(temp, ice,
         sizeof(ice)); // Copy original, meltdown based on the original ice.

  for (int i = 0; i < iceSize; i++) {
    for (int j = 0; j < iceSize; j++) {
      int adj = 0;
      for (int k = 0; k < 4; k++) {
        int nx = i + dx[k];
        int ny = j + dy[k];
        if (isValid(nx, ny) && temp[nx][ny] > 0) {
          adj++;
        }
      }

      if (adj < 3 && temp[i][j] > 0) {
        ice[i][j]--; // melt
      }
    }
  }
}

void firestorm(pair<int, int> pos, int size) {
  int sx = pos.first;
  int sy = pos.second;

  // 1. transpose
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      swap(ice[sx + i][sy + j], ice[sx + j][sy + i]);
    }
  }

  // 2. Reverse row
  for (int i = 0; i < size; i++) {
    int left = 0;
    int right = size - 1;

    while (left < right) {
      swap(ice[sx + i][sy + left], ice[sx + i][sy + right]);
      left++;
      right--;
    }
  }
}

void castSpell(int lev, int size) {
  int stormLev = getLev(lev);
  for (int i = 0; i < size; i += stormLev) {
    for (int j = 0; j < size; j += stormLev) {
      firestorm({i, j}, stormLev);
    }
  }

  meltdown();
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cin >> N >> Q;
  int size = getLev(N);
  iceSize = size;

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      cin >> ice[i][j];
    }
  }

  for (int i = 0; i < Q; i++) {
    int castLev = 0;
    cin >> castLev;
    castSpell(castLev, size);
  }

  pair<int, int> ans = getAns();

  cout << ans.first << "\n";
  cout << ans.second << "\n";
  return 0;
}
