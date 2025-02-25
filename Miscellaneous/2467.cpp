#include <climits>
#include <cstdlib>
#include <iostream>

#define ll long long

using namespace std;

ll liquid[100001] = {0};
int N = 0;

int startIdx, endIdx = 0;
ll minMixed = LONG_LONG_MAX;

ll mix(int s, int e) { return liquid[s] + liquid[e]; }

pair<int, int> compare() {

  int s = startIdx;
  int e = endIdx;
  pair<int, int> ans = {s, e};

  while (s != e) {

    ll mixed = mix(s, e);
    if ((0 - abs(mixed)) >= (0 - abs(minMixed))) {
      minMixed = mixed;
      ans.first = s;
      ans.second = e;
    }

    if (mixed >= 0) {
      e -= 1;
    } else {
      s += 1;
    }
  }

  return ans;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> N;

  endIdx = N - 1;

  for (int i = 0; i < N; i++) {
    cin >> liquid[i];
  }

  pair<int, int> ret = compare();

  cout << liquid[ret.first] << " " << liquid[ret.second] << endl;
  return 0;
}
