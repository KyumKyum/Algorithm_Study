#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/*
    Strategy: Using stack
    - Level change occurs
        1. If the level is higher, it is a start of new building. Push into
   stack.
        2. If the level is lesser, it is a end of the recently pushed building.
   Pop the stack and add the answer
        3. If the level is the same (after pop), ignore it (continuation of the
   building)
*/

int n, x, y = 0;
stack<int> s;
vector<pair<int, int>> v;

int ans = 0;

void skyline() {
  for (int i = 0; i < v.size(); i++) {
    int now = v[i].second;
    if (s.empty()) {
      if (now > 0) {
        s.push(now);
      } // Start of the building.
      continue;
    }

    if (s.top() < now) {
      // New building starts.
      s.push(now);
    } else {
      // New building ends.
      while (!s.empty() && s.top() > now) {
        // Pop until the top is lesser than current building, or the stack is
        // empty
        s.pop();
        ans++;
      }

      if (s.empty() || s.top() < now) {
        // New building starts again
        if (now > 0) {
          s.push(now);
        }
      }
    }
  }

  return;
}

int main(void) {
  cin.tie(0);
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> x >> y;
    v.push_back({x, y});
  }

  skyline();

  // Flush the stack. Count the rest of the buildings
  while (!s.empty()) {
    s.pop();
    ans++;
  }

  cout << ans << endl;
  return 0;
}
