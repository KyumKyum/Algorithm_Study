// Algorithm Study
// Backjoon: 구간 합 구하기 (2042)
// https://www.acmicpc.net/problem/2042

#include <iostream>
#include <vector>

using namespace std;

vector<long long> arr;
vector<long long> seg_tree;

long long make_seg_tree(int start, int end, int idx) {

    if(start == end){
        return seg_tree[idx] = arr[start];
    }

    //* Node index mgmt: node_left => idx*2, node_right => idx*2 + 1
    int mid = (start + end) / 2;

    return seg_tree[idx] = make_seg_tree(start, mid, idx*2) + make_seg_tree(mid+1, end, idx*2 + 1);
}

//* Searching range: start ~ end
//* Required range: from ~ to
//*  Out of bound: [from~to ... start...end] or [start...end...from~to]
//* Within range: [from...start...end...to]

long long query_sum(int start, int end, int from, int to, int idx){
    if ((to < start) || (end < from)) return 0; //* Out of bound

    if((from <= start) && (end <= to)) return seg_tree[idx]; //* Within the range

    int mid = (start + end) / 2;

    return query_sum(start, mid, from, to, idx * 2)
        + query_sum(mid+1, end, from, to, idx*2+1);
}

long long update(int tgt, long long val, int idx, int start, int end) {
    if((tgt < start) || (end < tgt)) return seg_tree[idx]; //* Return current value.

    if(start == end) return  seg_tree[idx] = val; //* Assign new value.

    int mid = (start + end) / 2;

    return seg_tree[idx] = update(tgt, val, idx*2, start, mid)
            + update(tgt, val, idx*2 + 1, mid+1, end);
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N = 0, M = 0, K = 0;
    long long element = 0;
    cin >> N >> M >> K;

    for(int i = 0; i < N; i++){
        cin >> element;
        arr.push_back(element);
    }

    int size = arr.size();
    seg_tree = vector<long long>(size * 4, -1) ; //* Size: 4 * N

    make_seg_tree(0, size-1, 1); //* Segment Tree index will be started in 1.

    while (K > 0){
        int a = 0;
        cin >> a;

        if(a==1){
            int b = 0;
            long long c = 0;
            cin >> b >> c;
            update(b-1, c, 1, 0, size - 1); //* Index - based on 0~n-1 range
        }else if(a == 2){
            int b = 0, c = 0;
            cin >> b >> c;
            //* Get Partial Sum
            cout << query_sum(0, size-1, b-1, c-1, 1) << "\n";//* Index - based on 0~n-1 range
            K--;
        }
    }
    return 0;
}
