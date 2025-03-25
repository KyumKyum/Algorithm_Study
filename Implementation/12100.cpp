
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

int N = 0;
int board[21][21] = {0};

int ans = -1;

// Mvmt will be applied as two-pointer
void moveRight() {
  for (int row = 0; row < N; row++) {
    int right = N - 1;
    int left = right - 1;

    while (left >= 0) {
      if (board[row][left] == 0) {
        left--;
        continue;
      }

      // The direction of the point is empty; simply move the element.
      if (board[row][right] == 0) {
        board[row][right] = board[row][left];
        board[row][left] = 0;
        left--;
        continue;
      }

      // Element exists.
      if (board[row][right] == board[row][left]) {
        board[row][right] *= 2;
        board[row][left] = 0;
      } else {
        // Diff
        int temp = board[row][left];
        board[row][left] = 0;
        board[row][right - 1] = temp;
      }
      right--;
      left--;
    }
  }
}

void moveLeft() {
  for (int row = 0; row < N; row++) {
    int left = 0;
    int right = left + 1;

    while (right < N) {
      if (board[row][right] == 0) {
        right++;
        continue;
      }

      if (board[row][left] == 0) {
        board[row][left] = board[row][right];
        board[row][right] = 0;
        right++;
        continue;
      }

      if (board[row][left] == board[row][right]) {
        board[row][left] *= 2;
        board[row][right] = 0;
      } else {
        int temp = board[row][right];
        board[row][right] = 0;
        board[row][left + 1] = temp;
      }
      right++;
      left++;
    }
  }
}

void moveDown() {
  for (int col = 0; col < N; col++) {
    int down = N - 1;
    int up = down - 1;
    while (up >= 0) {
      if (board[up][col] == 0) {
        up--;
        continue;
      }

      if (board[down][col] == 0) {
        board[down][col] = board[up][col];
        board[up][col] = 0;
        up--;
        continue;
      }

      if (board[down][col] == board[up][col]) {
        board[down][col] *= 2;
        board[up][col] = 0;
      } else {
        int temp = board[up][col];
        board[up][col] = 0;
        board[down - 1][col] = temp;
      }

      up--;
      down--;
    }
  }
}

void moveUp() {
  for (int col = 0; col < N; col++) {
    int up = 0;
    int down = up + 1;

    while (down < N) {
      if (board[down][col] == 0) {
        down++;
        continue;
      }

      if (board[up][col] == 0) {
        board[up][col] = board[down][col];
        board[down][col] = 0;
        down++;
        continue;
      }

      if (board[up][col] == board[down][col]) {
        board[up][col] *= 2;
        board[down][col] = 0;
      } else {
        int temp = board[down][col];
        board[down][col] = 0;
        board[up + 1][col] = temp;
      }

      up++;
      down++;
    }
  }
}

void checkMaximum() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (board[i][j] == 0)
        continue;
      ans = max(ans, board[i][j]);
    }
  }
}

void move(vector<int> command) {
  int size = command.size();
  for (int idx = 0; idx < size; idx++) {
    int option = command[idx];

    switch (option) {
    case 0:
      moveRight();
      break;
    case 1:
      moveLeft();
      break;
    case 2:
      moveUp();
      break;
    default: // case 3
      moveDown();
      break;
    }
  }

  checkMaximum();
}

void backtrack(vector<int> command) {
  if (command.size() >= 5) {
    int cache[21][21] = {0};
    memcpy(cache, board, sizeof(board));
    move(command);
    memcpy(board, cache, sizeof(board));
    return;
  }

  for (int option = 0; option < 5; option++) {
    command.push_back(option);
    backtrack(command);
    command.pop_back();
  }

  return;
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  cout.tie(nullptr);

  memset(board, 0, sizeof(board));

  cin >> N;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> board[i][j];
    }
  }

  vector<int> command;
  backtrack(command);

  cout << ans << endl;

  return 0;
}
