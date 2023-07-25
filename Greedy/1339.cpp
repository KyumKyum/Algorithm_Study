// Algorithm Study
// Backjoon: 단어수학 (1339)
// https://www.acmicpc.net/problem/1339

#include <iostream>
#include <math.h>
#include <iterator>
#include <vector>
#include <algorithm>

#define TO_INT 65
#define LETTERS 26

//* Strategy: Greedy
//* Get weight value based on its index. (apply digit)
//* multiply bigger value for bigger digit.

using namespace std;

short number[26];
pair<int, int> weight[26];
vector<string> words;

bool cmp(const pair<int, int> &a, const pair<int,int> &b){
    //* Custom compare function - compare second first.
    if(a.second == b.second){
        return a.first > b.first;
    }
    return a.second > b.second;
}

void setUp(){
    fill(begin(number), end(number), 0);
    for(int i = 0; i < LETTERS; i++){
        weight[i].first = i;
    }

    return;
}

long long word_math(int N){
    long long sum = 0;
    int idx = 0;
    int val = 9;

    string word;
    //* sort based on weight.
    sort(&weight[0], &weight[LETTERS], cmp);

    while(weight[idx].second > 0 && val > 0){
        sum += (val * weight[idx].second);
        idx++;
        val--;
    }

    return sum;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    string input;
    int N, size, max_weight = 0;
    short idx = 0;

    setUp();

    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> input;
        words.push_back(input);

        size = input.length();
        max_weight =  pow(10, size);
        for(int j = 0; j < size; j++){
            idx = short(input[j]) - TO_INT;
            weight[idx].second += (max_weight /= 10);
        }
    }

    cout << word_math(N) << endl;
    return 0;
}