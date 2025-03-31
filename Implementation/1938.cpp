#include <cstring>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct Log {
  pair<int, int> center; // Center point
  bool isHorizontal;     // true: horizontal, false: vertical
  int phase;
};

int N;
char forest[51][51];
bool visited[2][51][51]; // [orientation][row][col]

bool isValid(int r, int c) { return r >= 0 && r < N && c >= 0 && c < N; }

bool canMove(pair<int, int> center, bool isHorizontal, int dr, int dc) {
  int r = center.first;
  int c = center.second;
  if (isHorizontal) {
    return isValid(r + dr, c + dc - 1) && forest[r + dr][c + dc - 1] != '1' &&
           isValid(r + dr, c + dc) && forest[r + dr][c + dc] != '1' &&
           isValid(r + dr, c + dc + 1) && forest[r + dr][c + dc + 1] != '1';
  } else {
    return isValid(r + dr - 1, c + dc) && forest[r + dr - 1][c + dc] != '1' &&
           isValid(r + dr, c + dc) && forest[r + dr][c + dc] != '1' &&
           isValid(r + dr + 1, c + dc) && forest[r + dr + 1][c + dc] != '1';
  }
}

bool canTurn(pair<int, int> center) {
  int r = center.first;
  int c = center.second;
  for (int dr = -1; dr <= 1; ++dr) {
    for (int dc = -1; dc <= 1; ++dc) {
      if (!isValid(r + dr, c + dc) || forest[r + dr][c + dc] == '1') {
        return false;
      }
    }
  }
  return true;
}

bool isTarget(pair<int, int> center, bool isHorizontal) {
  int r = center.first;
  int c = center.second;
  if (isHorizontal) {
    return forest[r][c - 1] == 'E' && forest[r][c] == 'E' &&
           forest[r][c + 1] == 'E';
  } else {
    return forest[r - 1][c] == 'E' && forest[r][c] == 'E' &&
           forest[r + 1][c] == 'E';
  }
}

int bfs() {
  pair<int, int> start_center = {-1, -1};
  bool start_horizontal = false;

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (forest[i][j] == 'B') {
        if (j + 1 < N && forest[i][j + 1] == 'B' && j + 2 < N &&
            forest[i][j + 2] == 'B') {
          start_center = {i, j + 1};
          start_horizontal = true;
          break;
        } else if (i + 1 < N && forest[i + 1][j] == 'B' && i + 2 < N &&
                   forest[i + 2][j] == 'B') {
          start_center = {i + 1, j};
          start_horizontal = false;
          break;
        }
      }
    }
    if (start_center.first != -1)
      break;
  }

  if (start_center.first == -1)
    return 0;

  queue<Log> q;
  q.push({start_center, start_horizontal, 0});
  visited[start_horizontal ? 0 : 1][start_center.first][start_center.second] =
      true;

  while (!q.empty()) {
    Log current = q.front();
    q.pop();

    if (isTarget(current.center, current.isHorizontal)) {
      return current.phase;
    }

    int r = current.center.first;
    int c = current.center.second;
    int phase = current.phase;
    bool horizontal = current.isHorizontal;
    int visited_index = horizontal ? 0 : 1;

    // Move Left
    if (canMove(current.center, horizontal, 0, -1) &&
        !visited[visited_index][r][c - 1]) {
      visited[visited_index][r][c - 1] = true;
      q.push({{r, c - 1}, horizontal, phase + 1});
    }
    // Move Right
    if (canMove(current.center, horizontal, 0, 1) &&
        !visited[visited_index][r][c + 1]) {
      visited[visited_index][r][c + 1] = true;
      q.push({{r, c + 1}, horizontal, phase + 1});
    }
    // Move Up
    if (canMove(current.center, horizontal, -1, 0) &&
        !visited[visited_index][r - 1][c]) {
      visited[visited_index][r - 1][c] = true;
      q.push({{r - 1, c}, horizontal, phase + 1});
    }
    // Move Down
    if (canMove(current.center, horizontal, 1, 0) &&
        !visited[visited_index][r + 1][c]) {
      visited[visited_index][r + 1][c] = true;
      q.push({{r + 1, c}, horizontal, phase + 1});
    }
    // Turn
    if (canTurn(current.center) && !visited[1 - visited_index][r][c]) {
      visited[1 - visited_index][r][c] = true;
      q.push({{r, c}, !horizontal, phase + 1});
    }
  }

  return 0;
}

int main() {
  cin >> N;
  for (int i = 0; i < N; ++i) {
    string row;
    cin >> row;
    for (int j = 0; j < N; ++j) {
      forest[i][j] = row[j];
    }
  }

  cout << bfs() << endl;

  return 0;
}
