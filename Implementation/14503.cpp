#include <iostream>
#include <queue>
using namespace std;

short room[51][51] = {0};
short N, M = 0;
short r, c, d = 0;
short dx[4] = {-1, 0, 1, 0};
short dy[4] = {0, -1, 0, 1};

struct Movement {
  pair<short, short> pos;
  short dir;
};

queue<Movement> q;
int ans = 0;

bool isValid(int x, int y) { return x >= 0 && x < N && y >= 0 && y < M; }

void clean() {
  while (!q.empty()) {
    Movement mvmt = q.front();
    q.pop();

    // Step 1: Clean current position if needed
    if (room[mvmt.pos.first][mvmt.pos.second] == 0) {
      room[mvmt.pos.first][mvmt.pos.second] = 2; // Mark as cleaned
      ans++;
    }

    // Step 2: Check if any direction is cleanable
    bool hasCleanable = false;
    for (int d = 0; d < 4; d++) {
      short nx = mvmt.pos.first + dx[d];
      short ny = mvmt.pos.second + dy[d];
      if (isValid(nx, ny) && room[nx][ny] == 0) {
        hasCleanable = true;
        break;
      }
    }

    if (hasCleanable) {
      // Rotate counter-clockwise until finding cleanable space
      short nextDir = mvmt.dir;
      short nx, ny;
      do {
        nextDir = (nextDir + 1) % 4;
        nx = mvmt.pos.first + dx[nextDir];
        ny = mvmt.pos.second + dy[nextDir];
      } while (!(isValid(nx, ny) && room[nx][ny] == 0));

      // Move to the cleanable space
      q.push({{nx, ny}, nextDir});
    } else {
      // Try moving backward
      short backDir = (mvmt.dir + 2) % 4;
      short bx = mvmt.pos.first + dx[backDir];
      short by = mvmt.pos.second + dy[backDir];

      if (isValid(bx, by) && room[bx][by] != 1) {
        q.push({{bx, by}, mvmt.dir}); // Keep same direction
      }
      // If can't move backward, robot stops
    }
  }
}

int main(void) {
  cin.tie(0);
  cin >> N >> M;
  cin >> r >> c >> d;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> room[i][j];
    }
  }

  // Same direction conversion as Python
  d = (4 - d) % 4;

  q.push({{r, c}, d});
  clean();
  cout << ans << endl;

  return 0;
}
