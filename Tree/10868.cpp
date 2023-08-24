// Algorithm Study
// Backjoon: 최솟값 (10868)
// https://www.acmicpc.net/problem/10868

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

vector<long long> arr;
vector<long long> RMQ;
vector<long long> ans;

long long make_RMQ(int start, int end, int node){
    if(start == end) return RMQ[node] = arr[start];
    int mid = (start + end) / 2;
    return RMQ[node] = min(make_RMQ(start, mid, node*2), make_RMQ(mid + 1, end, node*2+1));
}

long long query_minimum(int start, int end, int from, int to, int node){
    if((to < start) || (end < from)) return LONG_LONG_MAX; //* Out of bound
    if((from <= start) && (end <= to)) return RMQ[node];

    int mid = (start + end) / 2;
    return min(query_minimum(start, mid, from, to, node*2) , query_minimum(mid+1, end, from,to, node*2+1));
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N, M = 0;
    cin >> N >> M;

    for(int i = 0; i < N; i++){
        long long input;
        cin >> input;
        arr.push_back(input);
    }

    //* SetUp
    int size = arr.size();
    RMQ = vector<long long>(size*4, 0);
    make_RMQ(0, size-1, 1);

    for(int i = 0; i < M; i++){
        int a = 0, b = 0;
        cin >> a >> b;

        ans.push_back(query_minimum(0, size-1, a-1, b-1, 1));
    }

    int ans_size = ans.size();
    for(int i = 0; i < ans_size; i++){
        cout << ans[i] << "\n";
    }

    return 0;
}