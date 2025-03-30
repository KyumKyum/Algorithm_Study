#include <climits>
#include <cstring>
#include <iostream>

#define MAX_SIZE 10

using namespace std;

int paper[MAX_SIZE][MAX_SIZE] = {0};
int kind[5] = {5, 5, 5, 5, 5};
int ans = INT_MAX;

bool isValid(int px, int py) {
  return px >= 0 && px < MAX_SIZE && py >= 0 && py < MAX_SIZE;
}

bool place(pair<int, int> pos) {
  if (!isValid(pos.first, pos.second))
    return false; // Out of Bounds
  if (paper[pos.first][pos.second] == 1) {
    paper[pos.first][pos.second] = 0;
    return true;
  }
  return false;
}

bool placePaper(pair<int, int> pos, int size) {
  int cache[MAX_SIZE][MAX_SIZE];
  memcpy(cache, paper, sizeof(paper));

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (!place({pos.first + i, pos.second + j})) {
        memcpy(paper, cache, sizeof(paper));
        return false;
      }
    }
  }
  return true;
}

void backtrack(pair<int, int> next, int num) {

  int x = next.first;
  int y = next.second;

  bool flag = false;
  pair<int, int> found = {-1, -1};
  for (int row = x; row < MAX_SIZE; row++) {
    for (int col = (row == x ? y : 0); col < MAX_SIZE; col++) {
      if (paper[row][col] == 1) {
        // Found the place!
        found.first = row;
        found.second = col;
        flag = true;
        break;
      }
    }

    if (flag)
      break;
  }

  // 1. Base case - No more 1
  if (found.first == -1) {
    // second will also be -1.
    ans = min(num, ans);
    return;
  }

  int cache[MAX_SIZE][MAX_SIZE];
  // 2. Try all kinds of papers.
  for (int size = 1; size < 6; size++) {
    if (kind[size - 1] <= 0) {
      // No papers left for current size. Try another.
      continue;
    }

    memcpy(cache, paper, sizeof(paper));

    if (!placePaper(found, size)) {
      // Current paper doesn't fit. Bigger size also cannot be fit.
      memcpy(paper, cache, sizeof(paper));
      return;
    }

    kind[size - 1] -= 1;
    backtrack(found, num + 1);
    kind[size - 1] += 1;

    memcpy(paper, cache, sizeof(paper));
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  for (int i = 0; i < MAX_SIZE; i++) {
    for (int j = 0; j < MAX_SIZE; j++) {
      cin >> paper[i][j];
    }
  }

  backtrack({0, 0}, 0);

  if (ans == INT_MAX)
    cout << "-1\n";
  else
    cout << ans << "\n";

  return 0;
}
