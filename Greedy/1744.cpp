#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/*
* Strategy: Greedy
* Separate the value; Negative (signed) and Positive (unsigned), 0 and 1.
* For each group, multiply two value and add until its maximum / minimum value
is left.
* If 0 exists and negative-minimum value exists, drop the minimum value
(multiplied by 0.)
* Add all the summation and leftovers.


* Example
* -4, 0, 1, -3, 4, 2 -> (-4, -3), 0, 1, (2, 4) = 12 + 1 + 8 = 21
* 1, 3, 0 -5 -> (-5, 0), 1, 3 = 4
*/
int N = 0;

priority_queue<int> pq_positive;
priority_queue<int, vector<int>, greater<int>> pq_negative;

int permutation[51] = {0};

int group() {
  bool zeroExists = false;
  int oneNum = 0; // In case that multiple 1 exists. (1 is the case that
                  // addition results greater value than multiplication.)

  for (int i = 0; i < N; i++) {
    if (permutation[i] == 0)
      zeroExists = true;
    else if (permutation[i] == 1)
      oneNum++;
    else if (permutation[i] < 0)
      pq_negative.push(permutation[i]);
    else
      pq_positive.push(permutation[i]);
  }

  int sum = 0;
  int positiveLeftover = 0;
  int negativeLeftover = 0;
  while (pq_negative.size() > 1) {
    int i = pq_negative.top();
    pq_negative.pop();
    int j = pq_negative.top();
    pq_negative.pop();
    sum += i * j;
  }

  if (pq_negative.size() == 1 &&
      !zeroExists) { // If zero exists, this value will be grouped with 0 ->
                     // became 0.
    negativeLeftover = pq_negative.top();
    pq_negative.pop();
  }

  while (pq_positive.size() > 1) {
    int i = pq_positive.top();
    pq_positive.pop();
    int j = pq_positive.top();
    pq_positive.pop();
    sum += i * j;
  }

  if (pq_positive.size() == 1) {
    positiveLeftover = pq_positive.top();
    pq_positive.pop();
  }

  // Add all 1
  for (int i = 0; i < oneNum; i++) {
    sum++;
  }

  return negativeLeftover + positiveLeftover + sum;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> permutation[i];
  }

  cout << group() << endl;

  return 0;
}
