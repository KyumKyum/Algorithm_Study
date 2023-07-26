// Algorithm Study
// Backjoon: 파일 합치기 3 (13975)
// https://www.acmicpc.net/problem/1715

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

//* Strategy: Greedy
//* Add first two smaller file. Repeat until there is only one file in there.
//* Use Priority Queue to do this.


vector<long long> ans;

long long merge_file(priority_queue<long long, vector<long long>, greater<long long> > file){
    long long cmp = 0;
    long long file_a, file_b, added = 0;
    while(file.size() > 1){ //* Do until there is only one pile left
        file_a = file.top();
        file.pop();
        file_b = file.top();
        file.pop();

        added = file_a + file_b;
        cmp += added;

        file.push(added);
    }

    file.pop();
    return cmp;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int TC = 0;
    long long K, file_size = 0;

    cin >> TC;

    for(int tc = 0; tc < TC; tc++){
        priority_queue<long long, vector<long long>, greater<long long> > file;
        cin >> K;
        for(long long i = 0; i < K; i++){
            cin >> file_size;
            file.push(file_size);
        }

        ans.push_back(merge_file(file));
    }

    for(int tc = 0; tc < TC; tc++){
        cout << ans[tc] <<"\n";
    }

    return 0;
}