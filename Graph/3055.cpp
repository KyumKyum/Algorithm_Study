#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

char board[51][51];
int waterDist[51][51]; // Stores when water will reach each cell
int hedgehogDist[51]
                [51]; // Stores the minimum time for hedgehog to reach each cell
int R, C;

// Direction arrays for movement
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

bool isValid(int x, int y) { return x >= 0 && x < R && y >= 0 && y < C; }

void bfs() {
  queue<pair<int, int>> waterQ;
  queue<pair<int, int>> hedgehogQ;
  pair<int, int> beaver;

  // Initialize distances
  memset(waterDist, -1, sizeof(waterDist));
  memset(hedgehogDist, -1, sizeof(hedgehogDist));

  // Find initial positions
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      if (board[i][j] == '*') {
        waterQ.push({i, j});
        waterDist[i][j] = 0;
      } else if (board[i][j] == 'S') {
        hedgehogQ.push({i, j});
        hedgehogDist[i][j] = 0;
      } else if (board[i][j] == 'D') {
        beaver = {i, j};
      }
    }
  }

  // BFS for water spreading
  while (!waterQ.empty()) {
    int x = waterQ.front().first;
    int y = waterQ.front().second;
    waterQ.pop();

    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];

      if (isValid(nx, ny) && waterDist[nx][ny] == -1 && board[nx][ny] != 'X' &&
          board[nx][ny] != 'D') {
        waterDist[nx][ny] = waterDist[x][y] + 1;
        waterQ.push({nx, ny});
      }
    }
  }

  // BFS for hedgehog movement
  while (!hedgehogQ.empty()) {
    int x = hedgehogQ.front().first;
    int y = hedgehogQ.front().second;
    hedgehogQ.pop();

    // Check if hedgehog reached beaver's den
    if (x == beaver.first && y == beaver.second) {
      cout << hedgehogDist[x][y] << endl;
      return;
    }

    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];

      if (isValid(nx, ny) && hedgehogDist[nx][ny] == -1 &&
          board[nx][ny] != 'X') {
        // Check if water won't be there before hedgehog arrives
        if (waterDist[nx][ny] == -1 ||
            waterDist[nx][ny] > hedgehogDist[x][y] + 1) {
          hedgehogDist[nx][ny] = hedgehogDist[x][y] + 1;
          hedgehogQ.push({nx, ny});
        }
      }
    }
  }

  // If we reach here, hedgehog couldn't reach beaver's den
  cout << "KAKTUS" << endl;
}

int main() {
  cin >> R >> C;

  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      cin >> board[i][j];
    }
  }

  bfs();

  return 0;
}
