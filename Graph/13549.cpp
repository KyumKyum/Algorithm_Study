// Algorithm Study
// Backjoon: 숨바꼭질 3 (13549)
// https://www.acmicpc.net/problem/13549

#include <iostream>
#include <deque>
#include <algorithm>
#include <iterator>

using namespace std;

//* Idea: 0-1 BFS (Deque)
//* Move: Move to vertex X+1 / X-1 with edge weight 1.
//* Teleport: Move to vertex 2*X with edge weight 0.
//* If current vertex is more than equal than destination. Check below the checklist.
    //* Vertex == dest, return with calculated weight.
    //* Vertex == dest + 1, return with calculated weight + 1.
    //* Vertex > dest, stop searching with current vertex. This case cannot be done.

deque< pair<int, int> > zero_one_BFS;
int start = 0, dest = 0;
bool visited[200100]; //* Corner Cases: 50001 -> 50002 -> ... -> 100000 is slower than 50001 -> 100002 -> 100001 -> 100000

int hide_N_seek(){

    while(!zero_one_BFS.empty()) {
        pair<int, int> cur = zero_one_BFS.front();
        zero_one_BFS.pop_front();

        //* Check if current vertex requires more searching.
        if (cur.first == dest) return cur.second;

        //* 3 cases.
        if (cur.first > 0 && cur.first * 2 < dest * 2 && !visited[cur.first * 2]) { //* Limit: dest * 2
            visited[cur.first * 2] = true;
            zero_one_BFS.push_front(pair<int, int>(cur.first * 2, cur.second));
        } //* Teleport
        if (cur.first > 1 && !visited[cur.first - 1]) {
            visited[cur.first - 1] = true;
            zero_one_BFS.push_back(pair<int, int>(cur.first - 1, cur.second + 1)); //* Move back}
        }
        if (!visited[cur.first + 1]) {
            visited[cur.first + 1] = true;
            zero_one_BFS.push_back(pair<int, int>(cur.first + 1, cur.second + 1)); //* Move front
        }

    }

    return 0;

}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    fill(begin(visited),end(visited), false);

    cin >> start >> dest;

    zero_one_BFS.push_front(pair<int, int>(start, 0));
    visited[start] = true;

    if(start > dest) cout << start - dest << "\n"; //* Only way Subin can get its brother is going back.
    else cout << hide_N_seek() << "\n";

    return 0;
}