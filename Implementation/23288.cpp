#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

/*
     1
  3  0  2
     4
     5
*/
int dice[6] = {0};
int N, M, K = 0;
int board[21][21];

void rollRight() {
  // 0 2 5 3 -> 2 5 3 0
  int temp = dice[0];
  dice[0] = dice[2];
  dice[2] = dice[5];
  dice[5] = dice[3];
  dice[3] = temp;
}

void rollLeft() {
  // 0 2 5 3 -> 3 0 2 5
  int temp = dice[0];
  dice[0] = dice[3];
  dice[3] = dice[5];
  dice[5] = dice[2];
  dice[2] = temp;
}

void rollDown() {
  // 0 4 5 1 -> 4 5 1 0
  int temp = dice[0];
  dice[0] = dice[4];
  dice[4] = dice[5];
  dice[5] = dice[1];
  dice[1] = temp;
}

void rollUp() {
  // 0 4 5 1 -> 1 0 4 5
  int temp = dice[0];
  dice[0] = dice[1];
  dice[1] = dice[5];
  dice[5] = dice[4];
  dice[4] = temp;
}

void roll(int opt, pair<int, int> &pos) {
  switch (opt) {
  case 0:
    rollRight();
    pos.second += 1;
    break;
  case 1:
    rollDown();
    pos.first += 1;
    break;
  case 2:
    rollLeft();
    pos.second -= 1;
    break;
  default: // case 3
    rollUp();
    pos.first -= 1;
  }
}

int checkDirection(int opt, pair<int, int> pos) {
  switch (opt) {
  case 0:
    if (pos.second + 1 >= M) {
      // Return the oposite position.
      return 2;
    }
    break;

  case 1:
    if (pos.first + 1 >= N) {
      return 3;
    }
    break;

  case 2:
    if (pos.second - 1 < 0) {
      return 0;
    }
    break;

  default:
    if (pos.first - 1 < 0) {
      return 1;
    }
  }

  return opt; // No problem!
}

bool isValid(int nx, int ny) { return nx >= 0 && nx < N && ny >= 0 && ny < M; }

int countTile(pair<int, int> pos, int b) {
  bool visited[21][21];
  int dx[4] = {-1, 0, 1, 0};
  int dy[4] = {0, 1, 0, -1};
  int count = 0;
  memset(visited, false, sizeof(visited));
  queue<pair<int, int>> q;
  visited[pos.first][pos.second] = true;
  q.push(pos);

  while (!q.empty()) {
    pair<int, int> cur = q.front();
    q.pop();

    int x = cur.first;
    int y = cur.second;

    count++; // The score must be matched,

    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];

      if (isValid(nx, ny) && !visited[nx][ny] && board[nx][ny] == b) {
        visited[nx][ny] = true;
        q.push({nx, ny});
      }
    }
  }

  return count;
}

int game(int K) {
  int opt = 0;                 // First movement = East (0)
  pair<int, int> pos = {0, 0}; // initial position
  int total = 0;
  for (int round = 0; round < K; round++) {
    opt = checkDirection(opt, pos);
    roll(opt, pos); // Roll a dice
    int b = board[pos.first][pos.second];
    int c = countTile(pos, b);

    total += (b * c);

    // Check direction
    if (dice[0] > b) {
      opt = (opt + 1) % 4; // Turn right
    } else if (dice[0] < b) {
      opt = (opt + 3) % 4; // Turn left (equivalent to subtracting 1)
    }
  }

  return total;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  // Dice setup;
  /*
       1
    3  0  2
       4
       5

       2
    3  1  4
       5
       6
  */

  // Correct dice setup: (Match problem statement)
  dice[0] = 6; // Bottom
  dice[1] = 2; // Top
  dice[2] = 3; // Right
  dice[3] = 4; // Left
  dice[4] = 5; // Front
  dice[5] = 1; // Back
  // Now, the top is 1 while east is 3.

  // dice[0] is always the bottom.

  cin >> N >> M >> K;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> board[i][j];
    }
  }

  cout << game(K) << endl;

  return 0;
}
