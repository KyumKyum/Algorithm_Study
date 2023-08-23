// Algorithm Study
// Backjoon: 최솟값과 최댓값 (2357)
// https://www.acmicpc.net/problem/2357

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//* Idea: Segment Tree; Range Minimum Query & Range Maximum Query
//* Node: <minimum, maximum>

vector<long long> arr;
vector< pair<long long, long long> > RMQ;
vector< pair<long long, long long> > ans;

pair<long long, long long> make_RMQ(int start, int end, int node){
    if(start == end) return RMQ[node] = pair<long long, long long>(arr[start], arr[start]); //* Found leaf node

    int mid = (start + end) / 2;

    pair<long long, long long> left = make_RMQ(start, mid, node*2);
    pair<long long, long long> right = make_RMQ(mid+1, end, node*2+1);

    return RMQ[node] = pair<long long, long long> (
            min(left.first, right.first),
            max(left.second, right.second)
            );
}

pair<long long, long long> query(int start, int end, int from, int to, int node){
    if((to < start) || (end < from)) return pair<long long, long long>(-1, -1); //* Out of bound

    if((from <= start) && (end <= to)) return RMQ[node]; //* Found a range.

    int mid = (start + end) / 2;
    pair<long long, long long> left = query(start, mid, from, to, node * 2);
    pair<long long, long long> right = query(mid + 1, end, from, to, node * 2 + 1);

    //* If one of the range returns -1, skip for that result.
    if(left.first == -1 || left.second == -1) return right;
    else if(right.first == -1 || right.second == -1) return left;
    else return pair<long long, long long>( //* Return the minimum / maximum value.
                min(left.first, right.first),
                max(left.second, right.second)
            );
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N, M;
    cin >> N >> M;

    for(int i = 0; i < N; i++){
        long long input;
        cin >> input;
        arr.push_back(input);
    }

    int size = arr.size();

    RMQ = vector< pair<long long, long long> >(size*4, pair<long long, long long>(0, 0));
    make_RMQ(0, size-1, 1);

    for(int i = 0; i < M; i++){
        int a = 0, b = 0;
        cin >> a >> b;
        ans.push_back(query(0, size-1, a-1, b-1, 1));
    }

    int ans_size = ans.size();

    for(int i = 0; i < ans_size; i++){
        cout << ans[i].first << " " << ans[i].second << "\n";
    }

    return 0;
}