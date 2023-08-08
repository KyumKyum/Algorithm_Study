
// Algorithm Study
// Backjoon: 좀비 떼가 기관총 진지에도 오다니 (19644)
// https://www.acmicpc.net/problem/19644
#include <iostream>
#include <queue>
#include <vector>
#include <deque>

using namespace std;

//* Strategy: Queue, Prefix Sum (and Implementation)

queue<int> zombies;
vector<long long> damage;
int L, ML, MK, C = 0;

bool survive(void){
    bool survived = true;
    int idx = 0; //* Will indicate the damage zombie takes.

    //* Calculate Damage via prefix sum
    damage.push_back(0);

    for(int i = 1; i <= L; i++){
        int cur_damage = damage[i-1] - damage[max(0, i - ML)]; //* Prefix sum based on limit.

        if(zombies.front() <= cur_damage + MK){
            //* If zombie is available to kill with machine gun.
            damage.push_back(damage[i-1] + MK); //* Update aggregated damage.
            zombies.pop();
            continue;
        }else{
            //* Not available to kill.
            if(C > 0){
                C--;
                damage.push_back(damage[i-1]); //* Not update damage.
                zombies.pop();
            }else{
                //* Dies!
                survived = false;
                break;
            }
        }
    }

    return survived;

}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int Z = 0;

    cin >> L;
    cin >> ML >> MK;

    //* Prefix Sum
    //* Record damage by shoot.
        //* zombie at ith m will get MK * ith damage.

    cin >> C;

    for(int i = 0; i < L; i++){
        cin >> Z;
        zombies.push(Z);
    }

    if(survive()){
        cout << "YES\n";
    }else{
        cout << "NO\n";
    }

    return 0;
}