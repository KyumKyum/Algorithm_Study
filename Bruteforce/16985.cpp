#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

short maze[5][5][5] = {0};
int ans = INT_MAX;
short dx[2] = {-1, 1};
short dy[4] = {-1, 0, 1, 0};
short dz[4] = {0, 1, 0, -1};

struct Pos {
  int x;
  int y;
  int z;
};

// Start, End
pair<Pos, Pos> init[8] = {
    {{0, 0, 0}, {4, 4, 4}}, {{0, 0, 4}, {4, 4, 0}}, {{0, 4, 0}, {4, 0, 4}},
    {{0, 4, 4}, {4, 0, 0}}, {{4, 4, 4}, {0, 0, 0}}, {{4, 4, 0}, {0, 0, 4}},
    {{4, 0, 4}, {0, 4, 0}}, {{4, 0, 0}, {0, 4, 4}},
};

bool isValid(int px, int py, int pz) {
  return px >= 0 && px < 5 && py >= 0 && py < 5 && pz >= 0 && pz < 5;
}

void solve() {
  // Try all 8 possible cases
  for (int idx = 0; idx < 8; idx++) {
    int visited[5][5][5];
    memset(visited, -1, sizeof(visited));
    queue<Pos> q;

    Pos start = init[idx].first;
    Pos end = init[idx].second;

    // Skip if start or end positions aren't passable
    if (maze[start.x][start.y][start.z] != 1 ||
        maze[end.x][end.y][end.z] != 1) {
      continue;
    }

    q.push(start);
    visited[start.x][start.y][start.z] = 0;

    bool found = false;
    while (!q.empty() && !found) {
      Pos pos = q.front();
      q.pop();
      int x = pos.x;
      int y = pos.y;
      int z = pos.z;

      // Found path to end
      if (x == end.x && y == end.y && z == end.z) {
        ans = min(ans, visited[x][y][z]);
        found = true;
        break; // Exit
      }

      // Check NESW directions
      for (int i = 0; i < 4; i++) {
        int ny = y + dy[i];
        int nz = z + dz[i];
        if (isValid(x, ny, nz) && visited[x][ny][nz] == -1 &&
            maze[x][ny][nz] == 1) {
          visited[x][ny][nz] = visited[x][y][z] + 1;
          q.push({x, ny, nz});
        }
      }

      // Check Up and Down
      for (int i = 0; i < 2; i++) {
        int nx = x + dx[i];
        if (isValid(nx, y, z) && visited[nx][y][z] == -1 &&
            maze[nx][y][z] == 1) {
          visited[nx][y][z] = visited[x][y][z] + 1;
          q.push({nx, y, z});
        }
      }
    }
  }
}

void rotate(int lev) {
  // Rotate clockwise in 90 degree.
  // 1. Transpose
  for (int i = 0; i < 5; i++) {
    for (int j = i + 1; j < 5; j++) {
      swap(maze[lev][i][j], maze[lev][j][i]);
    }
  }
  // 2. Reverse each row
  for (int i = 0; i < 5; i++) {
    int left = 0;
    int right = 4;
    while (left < right) {
      swap(maze[lev][i][left], maze[lev][i][right]);
      left++;
      right--;
    }
  }
}

string hashValue(int lev) {
  string res = "";

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      res += to_string(maze[lev][i][j]);
    }
  }

  return res;
}

void rotateMaze(int lev) {
  if (lev >= 5) {
    // Solve the maze!
    solve();
    return;
  }

  // Save original state
  short temp[5][5];
  memcpy(temp, maze[lev], sizeof(temp));

  // Add vector to save rotated value as hash
  vector<string> v;

  // Try all 4 rotations
  for (int i = 0; i < 4; i++) {
    if (v.empty()) {
      // Push inital hash
      v.push_back(hashValue(lev));
    } else {
      // Check if the rotated version is duplicate.
      string hashed = hashValue(lev);
      bool found = false;
      for (string saved : v) {
        if (saved == hashed) {
          found = true;
          break; // Skip this rotation.
        }
      }

      if (found)
        continue;
    }
    rotateMaze(lev + 1);
    rotate(lev); // Rotate current level
  }

  // Restore original state
  memcpy(maze[lev], temp, sizeof(temp));
}

void stackMaze(int lev) {
  if (lev >= 4) {
    rotateMaze(0);
    return;
  }

  // Try all possible arrangements of remaining layers
  for (int i = lev; i < 5; i++) {
    // Swap current level with level i
    swap(maze[lev], maze[i]);
    stackMaze(lev + 1);
    // Restore
    swap(maze[lev], maze[i]);
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  // Input the maze
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      for (int k = 0; k < 5; k++) {
        cin >> maze[i][j][k];
      }
    }
  }

  // Try all configurations
  stackMaze(0);

  // Output result
  if (ans == INT_MAX)
    cout << -1 << endl;
  else
    cout << ans << endl;

  return 0;
}
