#include <algorithm>
#include <cstring>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int n, k;
string str;

string makeBig() {
  vector<char> tokens(str.begin(), str.end());
  stack<char> s;
  int removed = 0;
  for (int idx = 0; idx < n; idx++) {
    // Remove token if bigger number appears
    if (s.empty()) {
      s.push(tokens[idx]);
    } else {
      while (removed < k && !s.empty() && s.top() - '0' < tokens[idx] - '0') {
        // Remove if removed number is under k, stack is not empty, and the top
        // element is smaller than current index
        removed++;
        s.pop();
      }
      s.push(tokens[idx]);
    }
  }

  while (removed < k) {
    removed++;
    s.pop();
  }

  vector<char> bigger;
  while (!s.empty()) {
    bigger.push_back(s.top());
    s.pop();
  }

  reverse(bigger.begin(), bigger.end());
  string ans(bigger.begin(), bigger.end());
  return ans;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cin >> n >> k;
  cin >> str;

  cout << makeBig() << "\n";
  return 0;
}
