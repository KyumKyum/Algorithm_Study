#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

int R, C = 0;

char board[1001][1001] = {'.'};
int firePos[1001][1001] = {0};
int jihoonPos[1001][1001] = {0};

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

bool isValid(int nx, int ny) { return nx >= 0 && nx < R && ny >= 0 && ny < C; }

bool isEscaped(int nx, int ny) {
  return (nx == 0 || nx == R - 1 || ny == 0 || ny == C - 1) &&
         (board[nx][ny] == '.' || board[nx][ny] == 'J');
}

void bfs() {
  queue<pair<int, int>> fireQ;
  queue<pair<int, int>> jihoonQ;

  memset(firePos, -1, sizeof(firePos));
  memset(jihoonPos, -1, sizeof(jihoonPos));

  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      if (board[i][j] == 'F') {
        firePos[i][j] = 0;
        fireQ.push({i, j});
      } else if (board[i][j] == 'J') {
        jihoonPos[i][j] = 0;
        jihoonQ.push({i, j});
      }
    }
  }

  // Fire spreads
  while (!fireQ.empty()) {
    int x = fireQ.front().first;
    int y = fireQ.front().second;
    fireQ.pop();

    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];

      if (isValid(nx, ny) && firePos[nx][ny] == -1 && board[nx][ny] != '#') {
        // Is valid, not visited place, not a wall
        firePos[nx][ny] = firePos[x][y] + 1; // Moved
        fireQ.push({nx, ny});
      }
    }
  }

  // Jihoon runs
  while (!jihoonQ.empty()) {
    int x = jihoonQ.front().first;
    int y = jihoonQ.front().second;
    jihoonQ.pop();

    if (isEscaped(x, y)) {
      // Jihoon will escape in next iteration
      cout << jihoonPos[x][y] + 1 << endl;
      return;
    }

    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];

      if (isValid(nx, ny) && jihoonPos[nx][ny] == -1 && board[nx][ny] != '#' &&
          (firePos[nx][ny] > jihoonPos[x][y] + 1 || firePos[nx][ny] == -1)) {
        // Is valid, not visited place, not a wall, not an iteration that fire,
        // fire cannot reach will caught
        jihoonPos[nx][ny] = jihoonPos[x][y] + 1; // Moved
        jihoonQ.push({nx, ny});
      }
    }
  }

  // Jihoon cannot escape
  cout << "IMPOSSIBLE" << endl;
  return;
}

int main(void) {
  cin.tie(0);

  cin >> R >> C;

  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      cin >> board[i][j];
    }
  }

  bfs();

  return 0;
}
