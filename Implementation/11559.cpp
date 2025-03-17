#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

char board[12][6];
bool visited[12][6];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

bool isValid(int px, int py) { return px >= 0 && px < 12 && py >= 0 && py < 6; }

void drop() {
  for (int j = 0; j < 6; j++) {
    int dest = 11;
    for (int i = 11; i >= 0; i--) {
      if (board[i][j] != '.') {
        char temp = board[i][j];
        board[i][j] = '.';
        board[dest][j] = temp;
        dest--;
      }
    }
  }
}

int bfs(int px, int py, char color, bool popIt) {
  memset(visited, false, sizeof(visited));
  queue<pair<int, int>> q;
  vector<pair<int, int>> group;

  q.push({px, py});
  visited[px][py] = true;
  group.push_back({px, py});

  while (!q.empty()) {
    int x = q.front().first;
    int y = q.front().second;
    q.pop();

    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      if (isValid(nx, ny) && !visited[nx][ny] && board[nx][ny] == color) {
        visited[nx][ny] = true;
        q.push({nx, ny});
        group.push_back({nx, ny});
      }
    }
  }

  if (group.size() >= 4 && popIt) {
    for (auto pos : group) {
      board[pos.first][pos.second] = '.';
    }
    return 1;
  }

  return 0;
}

int game() {
  int chain = 0;
  bool popped;

  do {
    popped = false;
    memset(visited, false, sizeof(visited));

    // Find all groups that can pop
    vector<pair<int, int>> popGroups;
    for (int i = 0; i < 12; i++) {
      for (int j = 0; j < 6; j++) {
        if (board[i][j] != '.' && !visited[i][j]) {
          char color = board[i][j];
          memset(visited, false, sizeof(visited));
          queue<pair<int, int>> q;
          vector<pair<int, int>> group;

          q.push({i, j});
          visited[i][j] = true;
          group.push_back({i, j});

          while (!q.empty()) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();

            for (int d = 0; d < 4; d++) {
              int nx = x + dx[d];
              int ny = y + dy[d];
              if (isValid(nx, ny) && !visited[nx][ny] &&
                  board[nx][ny] == color) {
                visited[nx][ny] = true;
                q.push({nx, ny});
                group.push_back({nx, ny});
              }
            }
          }

          if (group.size() >= 4) {
            popGroups.push_back({i, j});
          }
        }
      }
    }

    // Pop all groups simultaneously
    if (!popGroups.empty()) {
      for (auto pos : popGroups) {
        bfs(pos.first, pos.second, board[pos.first][pos.second], true);
      }
      popped = true;
      chain++;
      drop();
    }

  } while (popped);

  return chain;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 6; j++) {
      cin >> board[i][j];
    }
  }

  cout << game() << endl;

  return 0;
}
