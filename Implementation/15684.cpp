#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

bool ladder[31][11] = {false}; // Indicated way to b <-> b+1
int N, M, H;

bool goDown(int start) {
  int col = start;
  for (int row = 0; row < H; row++) {
    if (ladder[row][col]) {
      col++; // Move right
    } else if (col - 1 >= 0 && ladder[row][col - 1]) {
      col--; // Move left
    }
  }
  return col == start;
}

bool checkAll() {
  for (int i = 0; i < N; i++) {
    if (!goDown(i))
      return false;
  }
  return true;
}

int solve(int count, int limit, int r, int c) {
  if (count >= limit)
    return checkAll() ? count : -1;

  int result = -1;
  for (int i = r; i < H; i++) {
    for (int j = (i == r ? c : 0); j < N - 1; j++) {
      if (!ladder[i][j] && (j == 0 || !ladder[i][j - 1]) && !ladder[i][j + 1]) {
        ladder[i][j] = true;
        int res = solve(count + 1, limit, i, j);
        if (res != -1) {
          if (result == -1 || res < result)
            result = res;
        }
        ladder[i][j] = false; // Backtrack
      }
    }
  }
  return result;
}

int playLadder() {
  for (int i = 0; i <= 3; i++) {
    int res = solve(0, i, 0, 0);
    if (res != -1)
      return res;
  }
  return -1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  memset(ladder, false, sizeof(ladder));

  cin >> N >> M >> H;
  for (int i = 0; i < M; i++) {
    int r, c;
    cin >> r >> c;
    ladder[r - 1][c - 1] = true;
  }

  cout << playLadder() << endl;
  return 0;
}
