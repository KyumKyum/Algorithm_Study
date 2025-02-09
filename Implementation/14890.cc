#include <iostream>

int road[101][101] = {0};
bool occupied[101][101] = {false};

int n, l, ans = 0;

bool checkRow(int x) {
  int curElev = road[x][0];

  for (int next = 1; next < n; next++) {
    int nextElev = road[x][next];
    if (nextElev == curElev) {
      continue;
    } else if (nextElev == curElev + 1) { // Going Up

      for (int back = next - 1; back >= next - l; back--) {
        if (back < 0) {
          return false;
        }
        if (occupied[x][back]) {
          return false; //* No enough space
        }
        if (road[x][back] != curElev) {
          return false; //* No enough space
        }
        occupied[x][back] = true;
      }
    } else if (nextElev == curElev - 1) {
      for (int forward = next; forward < next + l; forward++) {
        if (forward >= n) {
          return false;
        }
        if (occupied[x][forward]) {
          return false; //* No enough space
        }
        if (road[x][forward] != nextElev) {
          return false; //* No enoguh space
        }
        occupied[x][forward] = true;
      }
    } else {
      return false;
    }
    curElev = nextElev;
  }

  return true;
}

bool checkCol(int y) {
  int curElev = road[0][y];

  for (int next = 1; next < n; next++) {
    int nextElev = road[next][y];
    if (nextElev == curElev) {
      continue;
    } else if (nextElev == curElev + 1) { // Going Up

      for (int back = next - 1; back >= next - l; back--) {
        if (back < 0) {
          return false;
        }
        if (occupied[back][y]) {
          return false; //* No enough space
        }
        if (road[back][y] != curElev) {
          return false; //* No enough space
        }
        occupied[back][y] = true;
      }
    } else if (nextElev == curElev - 1) {
      for (int forward = next; forward < next + l; forward++) {
        if (forward >= n) {
          return false;
        }
        if (occupied[forward][y]) {
          return false; //* No enough space
        }
        if (road[forward][y] != nextElev) {
          return false; //* No enoguh space
        }
        occupied[forward][y] = true;
      }
    } else {
      return false;
    }
    curElev = nextElev;
  }

  return true;
}

int main(void) {

  std::cin >> n >> l;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> road[i][j];
      occupied[i][j] = false;
    }
  }

  for (int i = 0; i < n; i++) {
    if (checkRow(i)) {
      ans++;
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      occupied[i][j] = false;
    }
  }

  for (int i = 0; i < n; i++) {
    if (checkCol(i)) {
      ans++;
    }
  }

  std::cout << ans << std::endl;

  return 0;
}
