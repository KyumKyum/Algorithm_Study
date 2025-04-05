#include <iostream>
#include <map>
#include <queue>

using namespace std;

struct Shark {
  int id; // -1: empty
  int vel;
  int dir;
  int size;
  pair<int, int> loc;
};

Shark sea[101][101];
queue<Shark> q;

int R, C, M = 0;

Shark calculateNewPosition(Shark curShark) {
  pair<int, int> curLoc = curShark.loc;
  int r = curLoc.first;   // current row
  int c = curLoc.second;  // current column
  int dir = curShark.dir; // current direction
  int vel = curShark.vel; // velocity

  // Direction: 1=up, 2=down, 3=right, 4=left
  if (dir == 1 || dir == 2) { // vertical movement
    int cycle = 2 * (R - 1);
    int move = vel % cycle; // Calcualte the acutal movement occurs

    for (int i = 0; i < move; i++) {
      if (dir == 1) { // Moving up
        if (r == 1) {
          dir = 2; // Change direction to down
          r++;
        } else {
          r--;
        }
      } else { // Moving down
        if (r == R) {
          dir = 1; // Change direction to up
          r--;
        } else {
          r++;
        }
      }
    }
  } else { // horizontal movement
    int cycle = 2 * (C - 1);
    int move = vel % cycle;

    for (int i = 0; i < move; i++) {
      if (dir == 3) { // Moving right
        if (c == C) {
          dir = 4; // Change direction to left
          c--;
        } else {
          c++;
        }
      } else { // Moving left
        if (c == 1) {
          dir = 3; // Change direction to right
          c++;
        } else {
          c--;
        }
      }
    }
  }

  return {curShark.id, curShark.vel, dir, curShark.size, {r, c}};
}

void sharkMove(int catchedId) {
  int size = q.size();
  for (int i = 0; i < size; i++) {
    Shark curShark = q.front();
    q.pop();

    sea[curShark.loc.first][curShark.loc.second] = {
        -1, 0, 0, 0, {-1, -1}}; // Current space is empty space.
    // Check if current shark is the catched one
    if (catchedId == curShark.id) {
      continue;
    }

    Shark newShark = calculateNewPosition(curShark);

    q.push(newShark);
  }

  // Check if sharks exists in the same position. If so, remove such shart
  // (being eaten)
  map<pair<int, int>, Shark> posMap;
  while (!q.empty()) {
    // Check all the sharks
    Shark curShark = q.front();
    q.pop();

    pair<int, int> pos = curShark.loc;
    if (posMap.find(pos) != posMap.end()) {
      // There is a shark already in the position.
      Shark existingShark = posMap[pos];
      if (curShark.size > existingShark.size) {
        // existing shark being eaten.
        posMap[pos] = curShark;
      }
    } else {
      // No shark
      posMap[pos] = curShark;
    }
  }

  for (auto pair : posMap) {
    Shark shark = pair.second;
    sea[shark.loc.first][shark.loc.second] = shark;
    q.push(shark);
  }
}

int fishing() {
  int sum = 0;
  for (int c = 1; c <= C; c++) {
    int catched = -1;
    // Fisherman moves

    // 1. Fisherman catches
    for (int r = 1; r <= R; r++) {
      if (sea[r][c].id != -1) {
        // Catched a shark!
        sum += sea[r][c].size;
        catched = sea[r][c].id;
        break;
      }
    }

    // 2. Shark moves
    sharkMove(catched);
  }
  return sum;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> R >> C >> M;

  // Init
  for (int i = 1; i <= R; i++) {
    for (int j = 1; j <= C; j++) {
      sea[i][j] = {-1, 0, 0, 0, {-1, -1}};
    }
  }

  for (int i = 0; i < M; i++) {
    int r, c, s, d, z;
    cin >> r >> c >> s >> d >> z;
    Shark shark = {i + 1, s, d, z, {r, c}};
    sea[r][c] = shark;
    q.push(shark);
  }

  cout << fishing() << endl;

  return 0;
}
