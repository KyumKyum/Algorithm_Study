#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>

using namespace std;

struct Camera {
  pair<short, short> pos;
  short kind;
};

short office[10][10] = {0};
bool surv[10][10] = {false};
Camera camera[10] = {{{0, 0}, 0}};
short cameraNum = 0;
short N, M = 0;
int ans = INT_MAX;

void checkLeft(int x, int y) {
  for (int left = y; left >= 0; left--) {
    if (office[x][left] == 6) {
      break; // Camera cannot see through the wall
    }
    surv[x][left] = true;
  }
}

void checkUp(int x, int y) {
  for (int up = x; up >= 0; up--) {
    if (office[up][y] == 6) {
      break;
    }
    surv[up][y] = true;
  }
}

void checkRight(int x, int y) {
  for (int right = y; right < M; right++) {
    if (office[x][right] == 6) {
      break; // Camera cannot see through the wall
    }
    surv[x][right] = true;
  }
}

void checkDown(int x, int y) {
  for (int down = x; down < N; down++) {
    if (office[down][y] == 6) {
      break;
    }
    surv[down][y] = true;
  }
}

void checkBlindpoint() {
  int blindPoint = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (!surv[i][j]) {
        blindPoint++;
      }
    }
  }

  ans = min(ans, blindPoint);
}

void monitorArea(int x, int y, int dir) {
  switch (dir) {
  case 0: // Up
    checkUp(x, y);
    break;
  case 1: // Right
    checkRight(x, y);
    break;
  case 2: // Down
    checkDown(x, y);
    break;
  case 3: // Left
    checkLeft(x, y);
    break;
  }
}

void checkCCTV(short idx) {
  if (idx == cameraNum) {
    // Finish to check all cctv
    checkBlindpoint();
    return;
  }

  // Cache
  bool cache[10][10];
  memcpy(cache, surv, sizeof(surv)); // Cache the current progres.
  short cx = camera[idx].pos.first;
  short cy = camera[idx].pos.second;
  short kind = camera[idx].kind;

  switch (kind) {
  case 1: // Single Direction
    for (int dir = 0; dir < 4; dir++) {
      monitorArea(cx, cy, dir);
      checkCCTV(idx + 1);
      memcpy(surv, cache, sizeof(cache)); // Rollback
    }
    break;

  case 2: // Bi-Direction
    for (int dir = 0; dir < 2; dir++) {
      monitorArea(cx, cy, dir);
      monitorArea(cx, cy, (dir + 2) % 4); // The oposite direction
      checkCCTV(idx + 1);
      memcpy(surv, cache, sizeof(cache));
    }
    break;

  case 3: // Perpendicular direction
    for (int dir = 0; dir < 4; dir++) {
      monitorArea(cx, cy, dir);
      monitorArea(cx, cy, (dir + 1) % 4);
      checkCCTV(idx + 1);
      memcpy(surv, cache, sizeof(cache));
    }
    break;

  case 4: // Three-Directions
    for (int dir = 0; dir < 4; dir++) {
      monitorArea(cx, cy, dir);
      monitorArea(cx, cy, (dir + 1) % 4);
      monitorArea(cx, cy, (dir + 2) % 4);
      checkCCTV(idx + 1);
      memcpy(surv, cache, sizeof(cache));
    }
    break;

  case 5: // Four-Directions
    monitorArea(cx, cy, 0);
    monitorArea(cx, cy, 1);
    monitorArea(cx, cy, 2);
    monitorArea(cx, cy, 3);
    checkCCTV(idx + 1);
    memcpy(surv, cache, sizeof(cache));
  }
}

void setUpCameraPosition() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (office[i][j] == 6) {
        surv[i][j] = true; // This is a wall. This will be assumed as
                           // 'surveilable'. It won't be counted as blindpoint.
      } else if (office[i][j] > 0 && office[i][j] < 6) {
        camera[cameraNum] = {{i, j}, office[i][j]};
        cameraNum++;
      }
    }
  }
}

int main(void) {
  cin.tie(0);

  memset(surv, false, sizeof(surv));
  cin >> N >> M;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> office[i][j];
    }
  }

  setUpCameraPosition();
  checkCCTV(0);

  cout << ans << endl;

  return 0;
}
