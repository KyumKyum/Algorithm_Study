#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

#define ll long long

using namespace std;

int N, S = 0;

vector<ll> v;
vector<ll> sum;

int ans = INT_MAX;

void subsquences() {
  int start = 1;
  int end = N;

  while (start > 0 && end <= N) {
    ll prefixSum = sum[end] - sum[start - 1];
    if (prefixSum >= S) {
      // Found!
      int subsq = end - start + 1;
      ans = min(ans, subsq);
    }

    // If bigger, reduce end.
    if (prefixSum > S) {
      end -= 1;
    } else {
      // If small or equal, increse start and end (rollback)
      start += 1;
      end += 1;
    }
  }

  return;
}

int main(void) {
  cin.tie(0);
  cin >> N >> S;

  v.push_back(0);
  sum.push_back(0);
  for (int i = 1; i <= N; i++) {
    ll temp = 0;
    cin >> temp;
    v.push_back(temp);
  }

  for (int i = 1; i <= N; i++) {
    sum.push_back(sum[i - 1] + v[i]);
  }

  subsquences();

  if (ans == INT_MAX) {
    cout << 0 << endl;
  } else {
    cout << ans << endl;
  }

  return 0;
}
