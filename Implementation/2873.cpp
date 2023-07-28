// Algorithm Study
// Backjoon: 롤러코스터 (2873)
// https://www.acmicpc.net/problem/2873

#include <iostream>
#include <vector>
#include <cstring>
#include <limits.h>

using namespace std;

//* Strategy: Greedy & Implementation
//* Based on given width and height, try to span all cells.
//* Case 1: If height is odd number
    //* Span all cells by RRRDLLLDR....
//* Case 2: If height is even, but width is odd.
    //* Span all cells by DRURD...(end of edge)DLLLDRRR....
//* Case 3: If height and width are all even.
    //* Cannot span all the spaces.
    //* Possible cases to span elements except one cell.
        //* Blank in odd-numbered cell in even-numbered row.
        //* Blank in even-numbered cell in odd-numbered row.
        //* Find minimum value, spot as a blank.

vector<char> ans;

int coaster[1001][1001];
int R, C = 0;

void case_a(int r, int c, bool inverted){
    while(r != R-1 || c != C-1){
        if(!inverted){
            //* Right Direction
            if(c == C-1){
                r++;
                inverted = !inverted;
                ans.push_back('D');
            }else{
                c++;
                ans.push_back('R');
            }
        }else{
            //* Left Direction
            if(c == 0){
                r++;
                inverted = !inverted;
                ans.push_back('D');
            }else{
                c--;
                ans.push_back('L');
            }
        }
    }
    return;
}

void case_b(int r, int c){
    //* Firstly zig-zag first two rows, search all cells
    for(int itr = 0; itr < C; itr++){
        if(itr % 2 == 0){
            //* Go down
            ans.push_back('D');
        }else{
            //* Go Right, Up and Right.
            ans.push_back('R');
            ans.push_back('U');
            ans.push_back('R');
        }
    }
    if(R > 2){ //* If it has more than two rows, sweep all cells reversly in case a.
        ans.push_back('D');
        case_a(2,C-1, true);
    }
}

void case_c(int min_r, int min_c){
    //* Check blank for each two rows.
    //* If there is no blank in two rows, sweep like case 1.
    //* If blank exists, sweep like case 2.
    int line_before = (min_r % 2 == 0) ? min_r : min_r - 1;

    //* Go to the row before the blank.
    for(int r = 0; r < line_before; r++){
        for(int c = 0; c < C - 1; c++){
            if(r % 2 == 0){
                ans.push_back('R');
            }else {
                ans.push_back('L');
            }
        }
        ans.push_back('D');
    }

    //* based on the colum that blank locates, search all cells except blank.
    for(int c = 0; c < min_c; c++){
        if(c % 2 == 0){
            ans.push_back('D');
            ans.push_back('R');
        }else{
            ans.push_back('U');
            ans.push_back('R');
        }
    }

    for(int c = min_c; c < C - 1; c++){
        if(c % 2 == 0){
            ans.push_back('R');
            ans.push_back('D');
        }else {
            ans.push_back('R');
            ans.push_back('U');
        }
    }


    //* Travel rest of the cells.
    for(int r = line_before + 2; r < R; r++){
        ans.push_back('D');
        for(int c = 0; c < C - 1; c++){
            if(r % 2 == 0){
                ans.push_back('L');
            }else {
                ans.push_back('R');
            }
        }
    }

    return;
}

int construction(int min_r, int min_c){

    if(R % 2 == 1){
        //* Case 1: Row is odd; simply sweep & span all cells.
        case_a(0,0, false);
    }else if(R % 2 == 0 && C % 2 == 1){
        //* Case 2: Row is even and Column is odd: Zig-zag at the first time, and sweep & span all cells just like first case.
        case_b(0,0);
    }else{
        //* Case: Row and Column are all even: Sweep all area except one cell.
        case_c(min_r, min_c);
    }

    return ans.size();
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);
    memset(coaster, 0, sizeof(coaster));

    int happiness = 0;
    int min_happiness = INT_MAX;
    int min_r, min_c = 0;
    cin >> R >> C;

    for(int r = 0; r < R; r++){
        for(int c = 0; c < C; c++){
            cin >> happiness;
            if((r % 2 == 0 && c % 2 == 1)
                || (r % 2 == 1 && c % 2 == 0)){
                //* Possible Blank in even-numbered cell in odd-numbered row.
                //* Blank in odd-numbered cell in even-numbered row.
                if(min_happiness > happiness){
                    min_happiness = happiness;
                    min_r = r;
                    min_c = c;
                }
            }
            coaster[r][c] = happiness;
        }
    }

    int size = construction(min_r, min_c);

    for(int i = 0; i < size; i++){
        cout << ans[i];
    }
    cout << "\n";

    return 0;
}