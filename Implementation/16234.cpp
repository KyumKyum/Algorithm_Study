#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int N, L, R;
int map[51][51];
bool visited[51][51];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// Check if position is within bounds
bool isValid(int x, int y) { return x >= 0 && x < N && y >= 0 && y < N; }

// Check if two countries can open their border
bool checkOpen(int x1, int y1, int x2, int y2) {
  int diff = abs(map[x1][y1] - map[x2][y2]);
  return diff >= L && diff <= R;
}

// Find union using BFS and update population
bool search(int startX, int startY) {
  vector<pair<int, int>> unions;
  queue<pair<int, int>> q;
  int total = 0;

  q.push({startX, startY});
  visited[startX][startY] = true;
  unions.push_back({startX, startY});
  total += map[startX][startY];

  while (!q.empty()) {
    int x = q.front().first;
    int y = q.front().second;
    q.pop();

    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];

      if (isValid(nx, ny) && !visited[nx][ny] && checkOpen(x, y, nx, ny)) {
        visited[nx][ny] = true;
        q.push({nx, ny});
        unions.push_back({nx, ny});
        total += map[nx][ny];
      }
    }
  }

  // If union has more than one country, update population
  if (unions.size() > 1) {
    int newPop = total / unions.size();
    for (pair<int, int> country : unions) {
      map[country.first][country.second] = newPop;
    }
    return true;
  }
  return false;
}

// Simulate one day of population movement
bool simulateOneDay() {
  memset(visited, false, sizeof(visited));

  bool moved = false;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (!visited[i][j]) {
        if (search(i, j)) {
          moved = true;
        }
      }
    }
  }
  return moved;
}

int main() {
  // Input
  cin >> N >> L >> R;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> map[i][j];
    }
  }

  // Simulate days until no movement occurs
  int days = 0;
  while (simulateOneDay()) {
    days++;
  }

  cout << days << endl;
  return 0;
}
