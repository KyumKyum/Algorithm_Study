#include <iostream>

using namespace std;

int dice[6] = {0};

/*
   1
 3 0 2
   4
   5

DOWN -  0 4 5 1 -> 4 5 1 0
UP -    0 4 5 1 -> 1 0 4 5
RIGHT - 0 2 5 3 -> 2 5 3 0
LEFT -  0 2 5 3 -> 3 0 2 5

*/
int board[21][21] = {0};
short command[1001] = {0};

int N, M, K = 0;
int x, y = 0;

bool isValid(pair<short, short> pos) {
  return pos.first >= 0 && pos.first < N && pos.second >= 0 && pos.second < M;
}

void process(int cx, int cy, int side) {
  if (board[cx][cy] == 0) {
    // Copy the side to board
    board[cx][cy] = dice[side];
  } else {
    // Copy the board to side
    dice[side] = board[cx][cy];
    board[cx][cy] = 0;
  }
}

pair<short, short> rollDown(pair<short, short> pos) {
  if (!isValid({pos.first + 1, pos.second}))
    return pos; // Ignore

  int cx = pos.first + 1;
  int cy = pos.second;

  process(cx, cy, 4);

  // Rearrange
  int temp = dice[0];
  dice[0] = dice[4];
  dice[4] = dice[5];
  dice[5] = dice[1];
  dice[1] = temp;

  return {cx, cy};
}

pair<short, short> rollUp(pair<short, short> pos) {
  if (!isValid({pos.first - 1, pos.second}))
    return pos; // Ignore

  int cx = pos.first - 1;
  int cy = pos.second;

  process(cx, cy, 1);

  // Rearrange
  int temp = dice[5];
  dice[5] = dice[4];
  dice[4] = dice[0];
  dice[0] = dice[1];
  dice[1] = temp;

  return {cx, cy};
}

pair<short, short> rollRight(pair<short, short> pos) {
  if (!isValid({pos.first, pos.second + 1}))
    return pos; // Ignore

  int cx = pos.first;
  int cy = pos.second + 1;

  process(cx, cy, 2);

  int temp = dice[2];
  dice[2] = dice[5];
  dice[5] = dice[3];
  dice[3] = dice[0];
  dice[0] = temp;

  return {cx, cy};
}

pair<short, short> rollLeft(pair<short, short> pos) {
  if (!isValid({pos.first, pos.second - 1}))
    return pos; // Ignore

  int cx = pos.first;
  int cy = pos.second - 1;

  process(cx, cy, 3);

  int temp = dice[3];
  dice[3] = dice[5];
  dice[5] = dice[2];
  dice[2] = dice[0];
  dice[0] = temp;

  return {cx, cy};
}

pair<short, short> rollDice(pair<short, short> pos, short dir) {
  pair<short, short> curPos;
  switch (dir) {
  case 1: // E
    curPos = rollRight(pos);
    if (pos.second != curPos.second) {
      cout << dice[5] << endl;
    }
    break;

  case 2: // W
    curPos = rollLeft(pos);
    if (pos.second != curPos.second) {
      cout << dice[5] << endl;
    }
    break;

  case 3: // N
    curPos = rollUp(pos);
    if (pos.first != curPos.first) {
      cout << dice[5] << endl;
    }
    break;

  case 4: // S
    curPos = rollDown(pos);
    if (pos.first != curPos.first) {
      cout << dice[5] << endl;
    }
    break;
  }

  return curPos;
}

int main(void) {
  cin.tie(0);

  cin >> N >> M >> x >> y >> K;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> board[i][j];
    }
  }

  pair<short, short> pos = {x, y};

  for (int i = 0; i < K; i++) {
    cin >> command[i];
  }

  for (int i = 0; i < K; i++) {
    pos = rollDice(pos, command[i]);
  }

  return 0;
}
