// Algorithm Study
// Backjoon: 가희와 은행 (22234)
// https://www.acmicpc.net/problem/22234

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct Customer{
    int id;
    int time_taken;
    int arrived;
};

struct Waiting{ //* Memory Prob.
    int id;
    int time_taken;
};

struct cmp{
    bool operator()(Customer &c1, Customer &c2){
        return c1.arrived > c2.arrived;
    }
};

priority_queue<Customer, vector<Customer>, cmp> list;
queue<Waiting> pending;
int N, T, W, M = 0;

void start_work(void){
    int tick = 0;

    while(tick < W){
        Waiting cur = pending.front();
        pending.pop();
        int time_req = min(T, cur.time_taken);
        for(int i = 0; i < time_req; i++){
            cout << cur.id << "\n";
            cur.time_taken--;
            tick++;

            if(tick >= W) return;
        }

        while(!list.empty() && list.top().arrived <= tick){
            Waiting next = {list.top().id, list.top().time_taken};
            pending.push(next);
            list.pop();
        }

        if(cur.time_taken > 0){
            pending.push(cur);
        }
    }
    return;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> T >> W;

    //* Get first customer
    Waiting first;

    cin >> first.id >> first.time_taken;//* First customer

    //* Put into a queue.
    pending.push(first);

    //* Get more customer arrived after 1 second.

    cin >> M;

    for(int i = 0; i < M; i++){
        Customer cus;
        cin >> cus.id >> cus.time_taken >> cus.arrived;
        list.push(cus);
    }

    start_work();

    return 0;
}

