// Algorithm Study
// Backjoon: 강의실 배정 (11000)
// https://www.acmicpc.net/problem/11000

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

//* Strategy: Scheduling with Greedy.
//* Sort all the schedule in by ascending order with starting time.
//* Put all elements in the priority queue
//* Need to track minimum end time
//* If the starting time more than end time, it is affordable.
//* Else, it is not affordable, increase required room.
//* Track minimum end time by priority queue.

priority_queue< pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > schedule;
priority_queue<int, vector<int> ,greater<int> > shortest_end_time;

int get_required_classroom_num(){
    int required_classroom = 1;
    int end = 0;
    pair<int, int> p;

    while(!schedule.empty()){
        p = schedule.top();
        if(p.first < end){
            //* Not Affordable
            required_classroom ++;
            shortest_end_time.push(p.second);

            if(end > shortest_end_time.top()){
                shortest_end_time.push(end);
                end = shortest_end_time.top();
                shortest_end_time.pop();
            }
        }else{
            //* Affordable.
            shortest_end_time.push(p.second);
            end = shortest_end_time.top();
            shortest_end_time.pop();
        }
        schedule.pop();
    }


    return required_classroom;
}

int main(void){
    int N, S, T = 0;
    pair<int, int> p;

    cin >> N;

    for(int i = 0; i < N; i++){
        cin >> S >> T;
        p.first = S;
        p.second = T;

        schedule.push(p);
    }

    cout << get_required_classroom_num() << "\n";

    return 0;
}