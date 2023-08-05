// Algorithm Study
// Backjoon: 선 긋기 (2170)
// https://www.acmicpc.net/problem/2170

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

//* Strategy: Sweeping Algorithm
//* Sort all input based on starting position.
//* If next start position smaller than prev end position, assume its starting position is same with the prev one.
//* If not, it means new line will start, so update both starting and end position.

priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > lines;
int N = 0;

long long draw_line(void){
    long long total_length = 0;
    long long line_length = 0;

    pair<int, int> line = lines.top();
    //* Get init info.
    int start = line.first;
    int end = line.second;
    line_length = (end - start); //* Get Length
    lines.pop();

    while(!lines.empty()){
        line = lines.top();

        if(line.first <= end){ //* Same Line.
            if(line.second <= end){ //* Included.
                lines.pop();
                continue; //* This line is a part of longer line.
            }
            end = line.second; //* Update end position only.
            line_length = (end - start);
        }else{ //* New Line
            //* Update start and end position.
            start = line.first;
            end = line.second;
            //* Add new line length.
            total_length += line_length; //* Sum prev line to the total length
            line_length = (end - start); //* Draw new line
        }

        lines.pop();
    }

    total_length += line_length;

    return total_length;

}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N;

    for(int i = 0; i < N; i++){
        pair<int, int> line;
        cin >> line.first >> line.second;

        lines.push(line);
    }

    cout << draw_line() << "\n";

    return 0;
}