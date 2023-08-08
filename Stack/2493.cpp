// Algorithm Study
// Backjoon: 탑 (2493)
// https://www.acmicpc.net/problem/2493

#include <iostream>
#include <stack>

using namespace std;

//* Idea: Stack
//* Generalization: Find big number in leftmost x.
//* Use structure; save its index and height.
//* Use stack for input.
//* Start from right-most tower, push to another stack (called right).
//* Compare right.top and input.top. If right.top is smaller, it founded its big number in leftmost index, save its index information.
//* Push current top into right, and repeat.

struct Tower{
    int height;
    int idx;
};

stack<Tower> towers;
stack<Tower> tracking;

int ans[500001];

int N = 0;

void recv_signal(){
    //* Init.
    tracking.push(towers.top());
    towers.pop();

    while(!towers.empty()){
        Tower cur = towers.top();

        while(!tracking.empty() && tracking.top().height <= cur.height){
            //* Record its index.
            ans[tracking.top().idx] = cur.idx;
            tracking.pop();
        }

        tracking.push(cur);
        towers.pop();
    }

    //* Rest of the element in tracking: Not availble to receive (0)
    while(!tracking.empty()){
        ans[tracking.top().idx] = 0;
        tracking.pop();
    }
}


int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    Tower tower;

    cin >> N;

    for(int i = 1; i <= N; i++){
        cin >> tower.height;
        tower.idx = i;
        towers.push(tower);
    }

    recv_signal();

    for(int i = 1; i <= N; i++){
        cout << ans[i] << " ";
    }

    cout << "\n";

    return 0;
}
