// Algorithm Study
// Backjoon: 보석 도둑 (1202)
// https://www.acmicpc.net/problem/1202

#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

//* Strategy: Greedy
//* By using priority queue, sort packages and gems by its weight
//* Pop all the gems which is affordable to the package. (candidates)
//* Find the maximum value, add its value to sum, pop the package
//* Add new candidates as package limits grows.


struct cmp {
    bool operator()(const pair<int, int> &a, const pair<int,int> &b){
        //* Custom compare function - compare second first.
        if(a.second == b.second){
            return a.first < b.first;
        }
        return a.second < b.second;
    }
};

priority_queue< pair<int, int> , vector< pair<int, int> >, greater< pair<int, int> > > gems;
priority_queue<int, vector<int>, greater<int> > packages;
priority_queue< pair<int, int> , vector< pair<int, int> >, cmp> candidates;

long long rob(void){
    long long robbed = 0;
    int C = 0;

    while(!packages.empty()){
        C = packages.top();
        //* Get all the candidates
        while(gems.top().first <= C && !gems.empty()){
            pair<int, int> gem = gems.top();
            candidates.push(gem);
            gems.pop();
        }

        int size = candidates.size();

        if(size > 0){
            //* Rob the maximum value; add the maximum value to robbed, and push rest of them in priority queue.
            robbed += candidates.top().second;
            candidates.pop();
        }


        packages.pop();
    }

    return robbed;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, K, C= 0;
    pair<int, int> gem;

    cin >> N >> K;

    for(int i = 0; i < N; i++){
        cin >> gem.first >> gem.second;
        gems.push(gem);
    }

    for(int i = 0; i < K; i++){
        cin >> C;
        packages.push(C);
    }

    cout << rob() << "\n";

    return 0;
}
