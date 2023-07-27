// Algorithm Study
// Backjoon: 멀티탭 스케쥴링 (1700)
// https://www.acmicpc.net/problem/1700
#include <iostream>
#include <iterator>
#include <algorithm>

//* Strategy: Greedy -> Inspired by OS job scheduling algorithm
//* OS Job scheduling algorithm -> Optimized Scheduling
//* If all job queue is full, replace the job which happens "most later"

using namespace std;

bool used[110];
int plug[110];
int scheduling_queue[110];
int N, K = 0;
//* N: Plug num K: Job Num

int choose_victim(int start){
    int victim = 0;
    int v_idx = -1;
    bool isInPlace = false;
    int idx = 0;

    for(int i = 0; i < N; i++){
        for(int j = start; j < K; j++){
            idx = j;
            isInPlace = false;
            if(plug[i] == scheduling_queue[j]){
                isInPlace = true;
                break; //* Found
            }
        }

        if(!isInPlace){
            victim = i;
            break;
        }

        if(v_idx < idx){
            //* new victim!
            victim = i;
            v_idx = idx;
        }
    }

    return victim; //* Return victim index
}

int scheduling(void){
    int plugged = 0;
    int replace = 0;

    for(int idx = 0; idx < K; idx++){
        int cur = scheduling_queue[idx];

        if(!used[cur]){
            //* This item need to be plugged.
            if(plugged < N){
                //* There are space remaining in the plug. plug it.
                plug[plugged++] = cur;
                used[cur] = true;
            }else{
                //* There is no place.
                //* Choose victim. A job called most later.
                int vidx = choose_victim(idx + 1); //* Receive victim index
                used[plug[vidx]] = false;
                plug[vidx] = cur;
                used[cur] = true;
                replace++;
            }
        }
    }

    return replace;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    fill(begin(used), end(used), false);
    fill(begin(plug), end(plug), 0);
    fill(begin(scheduling_queue), end(scheduling_queue), 0);


    int item = 0;
    cin >> N >> K;

    for(int i = 0; i < K; i++){
        cin >> item;
        scheduling_queue[i] = item;
    }

    cout << scheduling() << "\n";

    return 0;
}


