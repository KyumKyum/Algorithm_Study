// Algorithm Study
// Backjoon: 카드 정렬하기 (1715)
// https://www.acmicpc.net/problem/1715

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

//* Strategy: Greedy
//* Add first two smaller pile. Repeat until there is only one pile in there.
//* Use Priority Queue to do this.

priority_queue<int, vector<int>, greater<int> > pile;

int pile_sum(){
    int cmp = 0;
    int pile_a, pile_b, added = 0;
    while(pile.size() > 1){ //* Do until there is only one pile left
        pile_a = pile.top();
        pile.pop();
        pile_b = pile.top();
        pile.pop();

        added = pile_a + pile_b;
        cmp += added;

        pile.push(added);
    }

    return cmp;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, cards = 0;
    cin >> N;

    for(int i = 0 ; i < N; i++){
        cin >> cards;
        pile.push(cards);
    }

    cout << pile_sum() << "\n";

    return 0;
}