#include <climits>
#include <cstring>
#include <iostream>

using namespace std;

char board[21][21];
bool alphabet[30] = {false};
int R, C = 0;

short dx[4] = {-1, 0, 1, 0};
short dy[4] = {0, 1, 0, -1};

int ans = INT_MIN;

bool isValid(int x, int y) { return x >= 0 && x < R && y >= 0 && y < C; }

void find(int x, int y, int cur) {
  bool temp[30] = {false};

  int idx = board[x][y] - 65; // A: 0, B: 1, ... Z: 27
  alphabet[idx] = true;

  memcpy(temp, alphabet, sizeof(alphabet)); // Cache

  bool isFinal = true;

  for (int i = 0; i < 4; i++) {
    int nx = x + dx[i];
    int ny = y + dy[i];
    if (isValid(nx, ny)) {
      char letter = board[nx][ny];
      if (!alphabet[letter - 65]) {
        //* Alphabet Not In Use
        isFinal = false;
        find(nx, ny, cur + 1);
        memcpy(alphabet, temp, sizeof(alphabet)); // Rollback
      }
    }
  }

  if (isFinal) {
    // This is a final letter
    ans = max(cur, ans);
  }

  return;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);

  memset(alphabet, false, sizeof(alphabet));

  cin >> R >> C;

  for (int i = 0; i < R; i++) {
    string temp = "";
    cin >> temp;
    for (int j = 0; j < C; j++) {
      board[i][j] = temp.at(j);
    }
  }

  find(0, 0, 1); // Including current character

  cout << ans << endl;
  return 0;
}
