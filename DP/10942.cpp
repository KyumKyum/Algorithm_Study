#include <iostream>
#include <vector>

using namespace std;

int str[2001] = {0};
short dp[2001][2001] = {0};
int N, M = 0;

void calculatePalindrome() {
  // Case 1. Single letter - It is palindrome in all cases
  for (int i = 0; i < N; i++) {
    dp[i][i] = 1;
  }

  // Case 2. Two letters - It is palindrome if it is identical with front
  // letter.
  for (int i = 1; i < N; i++) {
    if (str[i - 1] == str[i]) {
      dp[i - 1][i] = 1;
    }
  }

  // Case 3. Longer cases - 2 condition need to be met
  // The first and last character is identical
  // The substring inside need to be palindrome.

  for (int len = 2; len < N; len++) {
    for (int start = 0; start < N - len; start++) {
      int end = start + len;
      if (str[start] == str[end] && dp[start + 1][end - 1] == 1) {
        // It is palindrome
        // cout << str[start] << " / " << str[end] << endl;
        dp[start][end] = 1;
      }
    }
  }
  return;
}

int main(void) {

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> str[i];
  }

  calculatePalindrome();

  cin >> M;
  vector<int> v;

  for (int i = 0; i < M; i++) {
    int s, e = 0;
    cin >> s >> e;
    cout << dp[s - 1][e - 1] << "\n";
  }

  return 0;
}
