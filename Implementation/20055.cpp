#include <iostream>
#include <queue>
using namespace std;

int belt[2][101];
bool robot[101];
int N, K;
int rounds = 0;
queue<int> robotPos;

void turn() {
  // Save last robot state
  bool lastRobot = robot[N - 1];
  // Move robots with belt
  for (int i = N - 1; i > 0; i--) {
    robot[i] = robot[i - 1];
  }
  robot[0] = false; // No robot at loading position after turn

  // Move belt

  int goingUp = belt[1][0];
  int goingDown = belt[0][N - 1];
  for (int i = N - 1; i > 0; i--) {
    belt[0][i] = belt[0][i - 1];
  }
  for (int i = 0; i < N - 1; i++) {
    belt[1][i] = belt[1][i + 1];
  }
  belt[0][0] = goingUp;
  belt[1][N - 1] = goingDown;

  // Update robot positions in queue
  int size = robotPos.size();
  queue<int> newRobotPos;
  for (int i = 0; i < size; i++) {
    int pos = robotPos.front();
    robotPos.pop();
    pos++;
    if (pos < N - 1) { // If not at unloading position
      newRobotPos.push(pos);
    }
  }
  robotPos = newRobotPos;

  // Unload robot at N-1 if exists
  if (robot[N - 1]) {
    robot[N - 1] = false;
  }
}

bool checkStop() {
  int broken = 0;
  for (int i = 0; i < N; i++) {
    if (belt[0][i] <= 0)
      broken++;
    if (belt[1][i] <= 0)
      broken++;
  }
  return broken >= K;
}

void moveRobot() {
  int size = robotPos.size();
  queue<int> newRobotPos;

  for (int i = 0; i < size; i++) {
    int pos = robotPos.front();
    robotPos.pop();

    // Try to move robot
    if (pos + 1 < N && !robot[pos + 1] && belt[0][pos + 1] > 0) {
      robot[pos] = false;
      pos++;
      belt[0][pos]--;

      if (pos < N - 1) { // If not at unloading position
        robot[pos] = true;
        newRobotPos.push(pos);
      }
    } else if (pos < N - 1) { // Can't move but still on belt
      newRobotPos.push(pos);
    }
  }
  robotPos = newRobotPos;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> N >> K;

  // Input belt durability
  for (int i = 0; i < N; i++) {
    cin >> belt[0][i];
  }
  for (int i = N - 1; i >= 0; i--) {
    cin >> belt[1][i];
  }

  while (!checkStop()) {
    rounds++;

    // 1. Rotate belt and robots
    turn();

    // 2. Move robots if possible
    moveRobot();

    // 3. Add new robot if possible
    if (!robot[0] && belt[0][0] > 0) {
      robot[0] = true;
      robotPos.push(0);
      belt[0][0]--;
    }
  }

  cout << rounds << endl;
  return 0;
}
