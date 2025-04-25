#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>

using namespace std;

int city[26][26];
int district[26][26];

int N = 0;

int getLimit() { return (N % 2 == 0) ? N / 2 : (N / 2) + 1; }

int countAns() {
  int minNum = INT_MAX;
  int maxNum = INT_MIN;

  for (int idx = 1; idx <= 5; idx++) {
    int cnt = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (district[i][j] == idx) {
          cnt += city[i][j];
        }
      }
    }

    minNum = min(cnt, minNum);
    maxNum = max(cnt, maxNum);
  }

  return maxNum - minNum;
}

void divideDistrict(int r, int c, int d1, int d2) {
  // Mark boundary of district 5
  for (int i = 0; i <= d1; i++) {
    district[r + i][c - i] = 5;           // 1st line
    district[r + d2 + i][c + d2 - i] = 5; // 4th line
  }
  for (int i = 0; i <= d2; i++) {
    district[r + i][c + i] = 5;           // 2nd line
    district[r + d1 + i][c - d1 + i] = 5; // 3rd line
  }

  // Fill inside of district 5
  for (int i = r + 1; i < r + d1 + d2; i++) {
    bool inside = false;
    for (int j = 0; j < N; j++) {
      if (district[i][j] == 5)
        inside = !inside;
      if (inside)
        district[i][j] = 5;
    }
  }

  // Fill the district 1
  for (int i = 0; i < r + d1; i++) {
    for (int j = 0; j <= c; j++) {
      if (district[i][j] == 0) {
        district[i][j] = 1;
      }
    }
  }

  // Fill the district 2
  for (int i = 0; i <= r + d2; i++) {
    for (int j = c + 1; j < N; j++) {
      if (district[i][j] == 0) {
        district[i][j] = 2;
      }
    }
  }

  // Fill the district 3
  for (int i = r + d1; i < N; i++) {
    for (int j = 0; j < c - d1 + d2; j++) {
      if (district[i][j] == 0) {
        district[i][j] = 3;
      }
    }
  }

  // Fill the district 4
  for (int i = r + d2 + 1; i < N; i++) {
    for (int j = c - d1 + d2; j < N; j++) {
      if (district[i][j] == 0) {
        district[i][j] = 4;
      }
    }
  }
}

int getMinimumDiff(int lim) {
  int ans = INT_MAX;
  for (int d1 = 1; d1 < lim; d1++) {
    for (int d2 = 1; d2 < lim; d2++) {
      for (int r = 0; r + d1 + d2 < N; r++) {
        for (int c = d1; c + d2 < N; c++) {
          int temp[26][26] = {0};
          memcpy(temp, district, sizeof(district));
          divideDistrict(r, c, d1, d2);
          int val = countAns();
          ans = min(ans, val);
          memcpy(district, temp, sizeof(district));
        }
      }
    }
  }

  return ans;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cin >> N;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> city[i][j];
    }
  }
  memset(district, 0, sizeof(district));
  cout << getMinimumDiff(getLimit()) << "\n";
  return 0;
}
