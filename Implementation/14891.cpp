#include <cmath>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

short gear[4][8] = {0};
int K = 0;
short way = 0;
bool moved[4] = {false};

queue<pair<short, short>> q;

void turnCounterClockwise(int num) {
  short first = gear[num][0];

  for (int i = 0; i < 7; i++) {
    gear[num][i] = gear[num][i + 1];
  }

  gear[num][7] = first;
}

void turnClockwise(int num) {
  short last = gear[num][7];

  for (int i = 6; i >= 0; i--) {
    gear[num][i + 1] = gear[num][i];
  }

  gear[num][0] = last;
}

void turn(short num, short dir) {
  if (dir == 1) {
    turnClockwise(num);
  } else { // -1
    turnCounterClockwise(num);
  }
}

void iterate() {

  while (!q.empty()) {
    pair<short, short> tgt = q.front();
    q.pop();

    // Check if countering gear has same polarity
    // Check right (index 2 - index 6) and left (index 6 - index 2)
    short left = tgt.first - 1;
    short right = tgt.first + 1;

    if (left >= 0 && !moved[left] && (gear[left][2] != gear[tgt.first][6])) {
      q.push({left, -(tgt.second)});
      moved[left] = true;
    }

    if (right < 4 && !moved[right] && (gear[tgt.first][2] != gear[right][6])) {
      q.push({right, -(tgt.second)});
      moved[right] = true;
    }
    turn(tgt.first, tgt.second);
    // cout << endl;
    /*for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 8; j++) {
        cout << gear[i][j];
      }
      cout << endl;
    }*/
  }
}

int main(void) {

  string line;
  for (int i = 0; i < 4; i++) {
    cin >> line;
    for (int j = 0; j < 8; j++) {
      gear[i][j] = line[j] - '0';
    }
  }

  cin >> K;

  for (int i = 0; i < K; i++) {
    memset(moved, false, sizeof(moved));
    pair<int, int> tgt;
    cin >> tgt.first >> tgt.second;

    // 0-base
    tgt.first -= 1;
    moved[tgt.first] = true;

    q.push(tgt);
    iterate();
  }

  // Check

  int score = 0;
  int weight = 1;

  for (int i = 0; i < 4; i++) {
    if (gear[i][0] == 1) {
      score += weight;
    }
    weight *= 2;
  }

  cout << score << endl;
}
