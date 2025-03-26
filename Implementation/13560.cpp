#include <iostream>
#include <queue>

using namespace std;

struct Status {
  pair<int, int> red;
  pair<int, int> blue;
  int phase;
};

int N, M = 0;

char board[11][11] = {'.'};

int tiltRight(Status &status) {
  int bx = status.blue.first;
  int by = status.blue.second;
  int rx = status.red.first;
  int ry = status.red.second;

  // First move blue ball
  while (board[bx][by + 1] != '#') {
    by++;
    if (board[bx][by] == 'O')
      return -1; // Blue falls in first -> Failure
  }

  // Then move red ball
  while (board[rx][ry + 1] != '#') {
    ry++;
    if (board[rx][ry] == 'O')
      return 1; // Red falls in first -> Success
  }

  // Handle overlap (If they stop at the same position)
  if (rx == bx && ry == by) {
    if (status.red.second > status.blue.second) {
      // Red was to the right of blue initially
      by--;
    } else {
      // Blue was to the right of red initially
      ry--;
    }
  }

  status.red = {rx, ry};
  status.blue = {bx, by};
  return 0; // Continue game
}

int tiltLeft(Status &status) {
  int bx = status.blue.first;
  int by = status.blue.second;
  int rx = status.red.first;
  int ry = status.red.second;

  // Move blue first
  while (board[bx][by - 1] != '#') {
    by--;
    if (board[bx][by] == 'O')
      return -1; // Blue falls in first -> Failure
  }

  // Move red
  while (board[rx][ry - 1] != '#') {
    ry--;
    if (board[rx][ry] == 'O')
      return 1; // Red falls in first -> Success
  }

  // Handle overlap
  if (rx == bx && ry == by) {
    if (status.red.second < status.blue.second) {
      // Red was to the left of blue initially
      by++;
    } else {
      // Blue was to the left of red initially
      ry++;
    }
  }

  status.red = {rx, ry};
  status.blue = {bx, by};
  return 0; // Continue game
}

int tiltUp(Status &status) {
  int bx = status.blue.first;
  int by = status.blue.second;
  int rx = status.red.first;
  int ry = status.red.second;

  // Move blue first
  while (board[bx - 1][by] != '#') {
    bx--;
    if (board[bx][by] == 'O')
      return -1; // Blue falls in first -> Failure
  }

  // Move red
  while (board[rx - 1][ry] != '#') {
    rx--;
    if (board[rx][ry] == 'O')
      return 1; // Red falls in first -> Success
  }

  // Handle overlap
  if (rx == bx && ry == by) {
    if (status.red.first < status.blue.first) {
      // Red was above blue initially
      bx++;
    } else {
      // Blue was above red initially
      rx++;
    }
  }

  status.red = {rx, ry};
  status.blue = {bx, by};
  return 0; // Continue game
}

int tiltDown(Status &status) {
  int bx = status.blue.first;
  int by = status.blue.second;
  int rx = status.red.first;
  int ry = status.red.second;

  // Move blue first
  while (board[bx + 1][by] != '#') {
    bx++;
    if (board[bx][by] == 'O')
      return -1; // Blue falls in first -> Failure
  }

  // Move red
  while (board[rx + 1][ry] != '#') {
    rx++;
    if (board[rx][ry] == 'O')
      return 1; // Red falls in first -> Success
  }

  // Handle overlap
  if (rx == bx && ry == by) {
    if (status.red.first > status.blue.first) {
      // Red was below blue initially
      bx--;
    } else {
      // Blue was below red initially
      rx--;
    }
  }

  status.red = {rx, ry};
  status.blue = {bx, by};
  return 0; // Continue game
}

int tilt(int opt, Status &status) {
  switch (opt) {
  case 0:
    return tiltLeft(status);
    break;

  case 1:
    return tiltRight(status);
    break;

  case 2:
    return tiltUp(status);
    break;

  default: // case 3
    return tiltDown(status);
    break;
  }
}

int bfs() {
  Status status;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (board[i][j] == 'R') {
        status.red = {i, j};
      }
      if (board[i][j] == 'B') {
        status.blue = {i, j};
      }
    }
  }

  status.phase = 0;
  queue<Status> q;
  q.push(status);

  while (!q.empty()) {
    Status curState = q.front();
    q.pop();

    if (curState.phase >= 10) {
      break; // over 10 phases
    }

    for (int opt = 0; opt < 4; opt++) {
      Status mvState = curState;
      mvState.phase += 1;
      int res = tilt(opt, mvState);

      if (res == 1) {
        return mvState.phase; // Finished!
      } else if (res == 0) {
        // continue
        q.push(mvState);
      }

      // Ignore thr failure case. No need for further search.
    }
  }

  return -1;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> N >> M;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> board[i][j];
    }
  }

  cout << bfs() << endl;

  return 0;
}
