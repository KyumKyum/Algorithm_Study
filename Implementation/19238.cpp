#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int dx[4] = {0, -1, 0, 1}; // Directions for movement
int dy[4] = {-1, 0, 1, 0};

struct Passenger {
  int id;
  pair<int, int> dest;
};

struct Taxi {
  pair<int, int> pos;
  int moved;
};

int board[21][21] = {0};
Passenger passenger[21][21];
pair<int, int> taxi;
int N, M, gas = 0;

bool isValid(int nx, int ny) { return nx > 0 && nx <= N && ny > 0 && ny <= N; }

// Modified findPassenger function to handle tie-breaking rules
int findPassenger() {
  bool visited[21][21];
  memset(visited, false, sizeof(visited));
  queue<Taxi> q;

  // Initialize queue with current taxi position
  Taxi init = {taxi, 0};
  visited[taxi.first][taxi.second] = true;
  q.push(init);

  int minDist = -1;
  vector<pair<pair<int, int>, int>> candidates; // To store candidate passengers

  while (!q.empty()) {
    Taxi cur = q.front();
    q.pop();
    int x = cur.pos.first;
    int y = cur.pos.second;
    int dist = cur.moved;

    // If we already found passengers at a closer distance, no need to check
    // further
    if (minDist != -1 && dist > minDist) {
      break;
    }

    // If there's a passenger here, add to candidates
    if (passenger[x][y].id != -1) {
      if (minDist == -1 || dist <= minDist) {
        minDist = dist;
        candidates.push_back({{x, y}, dist});
      }
    }

    // If gas is depleted, stop BFS
    if (dist >= gas) {
      continue;
    }

    // BFS exploration
    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      if (isValid(nx, ny) && board[nx][ny] != 1 && !visited[nx][ny]) {
        visited[nx][ny] = true;
        q.push({{nx, ny}, dist + 1});
      }
    }
  }

  // No passengers found or unreachable
  if (minDist == -1 || candidates.empty()) {
    return -1;
  }

  // Find the passenger with the smallest row, then column
  pair<int, int> chosen = {N + 1, N + 1};
  for (auto &candidate : candidates) {
    int cx = candidate.first.first;
    int cy = candidate.first.second;

    if (cx < chosen.first || (cx == chosen.first && cy < chosen.second)) {
      chosen = {cx, cy};
    }
  }

  // Update taxi position and return distance
  taxi = chosen;
  return minDist;
}

int findDestination(int fx, int fy) {
  bool visited[21][21];
  memset(visited, false, sizeof(visited));
  queue<Taxi> q;
  Taxi init = {taxi, 0};
  visited[taxi.first][taxi.second] = true;
  q.push(init);

  while (!q.empty()) {
    Taxi cur = q.front();
    q.pop();
    int x = cur.pos.first;
    int y = cur.pos.second;
    int dist = cur.moved;

    if (x == fx && y == fy) {
      // Destination found!
      taxi = {x, y}; // Update taxi position
      return dist;
    }

    // Check for gas
    if (dist >= gas) {
      continue;
    }

    // BFS
    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      if (isValid(nx, ny) && board[nx][ny] != 1 && !visited[nx][ny]) {
        visited[nx][ny] = true;
        q.push({{nx, ny}, dist + 1});
      }
    }
  }

  // Unreachable or gas depleted
  return -1;
}

void taxiMvmt() {
  for (int i = 0; i < M; i++) {
    // Find the next passenger
    int gasForPassenger = findPassenger();
    if (gasForPassenger == -1) {
      // Unreachable to passenger
      gas = -1;
      return;
    }

    gas -= gasForPassenger;

    // Store passenger info and clear the position
    Passenger p = passenger[taxi.first][taxi.second];
    passenger[taxi.first][taxi.second] = {-1, {-1, -1}}; // Remove passenger

    // Go to destination
    int gasForDestination = findDestination(p.dest.first, p.dest.second);
    if (gasForDestination == -1) {
      // Unreachable to destination
      gas = -1;
      return;
    }

    gas -= gasForDestination;
    gas += gasForDestination * 2; // Refill
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  memset(board, 0, sizeof(board));
  cin >> N >> M >> gas;

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      cin >> board[i][j];
      passenger[i][j] = {-1,
                         {-1, -1}}; // Initialize all cells with no passengers
    }
  }

  cin >> taxi.first >> taxi.second;

  for (int i = 1; i <= M; i++) {
    int px, py, fx, fy;
    cin >> px >> py >> fx >> fy;
    passenger[px][py] = {i, {fx, fy}};
  }

  taxiMvmt();
  cout << gas << endl;

  return 0;
}
