// Algorithm Study
// Backjoon: 미세먼지 안녕! (17144)
// https://www.acmicpc.net/problem/17144

//* 6 <= R,C <= 50 (Worst: 2500)
//* 1 <= T <= 1,000 (Worst: 1000)
//* Worst Case: 2.5M Computation (Able to solve within 1 second.)

#include <iostream>
#include <cstring>

using namespace std;

struct Board{
    int dust_acc; //* Dust Accumulated
    int dust_new; //* Dust Newly Got
    bool isCleaner; //* Is Air cleaner
};

Board board[50][50];
int R,C,T = 0;

void diffusion(){
    int diffused_amount = 0;

    for(int r = 0; r < R; r++){
        for(int c = 0; c < C; c++){
            if(board[r][c].isCleaner or board[r][c].dust_acc <= 0) {
                if(!board[r][c].isCleaner and board[r][c].dust_new > 0){
                    board[r][c].dust_acc += board[r][c].dust_new;
                    board[r][c].dust_new = 0;
                }
                continue;
            }

            diffused_amount = (board[r][c].dust_acc / 5);
            if(r > 0 && !(board[r-1][c].isCleaner)){ //* Case #1: Diffuse to upper position
                //* Diffuse Only if there is a space and there is no air cleaner.
                //* Upper position: Already diffused. Calculate immediately at dust_acc.
                board[r-1][c].dust_acc += diffused_amount;
                board[r][c].dust_acc -= diffused_amount;
            }
            if(c > 0 && !(board[r][c-1].isCleaner)){ //* Case #2: Diffuse to left position
                //* Diffuse only if there is a space and there is no air cleaner.
                //* Left position: Already diffused. Calculate immediately at dust_acc.
                board[r][c-1].dust_acc += diffused_amount;
                board[r][c].dust_acc -= diffused_amount;
            }
            if(c < C - 1 && !(board[r][c+1].isCleaner)){ //* Case #3: Diffuse to right position
                //* Diffuse only if there is a space and there is no air cleaner.
                //* Right position: Have not been diffused. Save the diffused amount in dust_new, calculate after the diffusion of right position
                board[r][c+1].dust_new += diffused_amount;
                board[r][c].dust_acc -= diffused_amount;
            }
            if(r < R - 1 && !(board[r+1][c].isCleaner)){ //* Case #4: Diffuse to lower position
                //* Diffuse only if there is a space and there is no air cleaner.
                //* Lower position: Have not been diffused. Save the diffused amount in dust_new, calculate after the diffusion of lower position
                board[r+1][c].dust_new += diffused_amount;
                board[r][c].dust_acc -= diffused_amount;
            }
            //* If there is a dust in dust_new, calculate now
            board[r][c].dust_acc += board[r][c].dust_new;
            board[r][c].dust_new = 0;
        }
    }

    return;
}

void circulation(int upper, int lower){
    //* Circulation: upper part -> C-clockwise
        //* Will calculate in clockwise.
    //* lower part -> clockwise
        //* Will calculate in C-clockwise.
    //* If dust come close to cleaner, it disappears

    //* Upper
   for(int r = upper - 1; r > 0; r--){
       //* 1. ascending
       board[r][0].dust_acc = board[r-1][0].dust_acc;
   }
   for(int c = 0; c < C - 1; c++){
       //* 2. traverse
       board[0][c].dust_acc = board[0][c+1].dust_acc;
   }
   for(int r = 0; r < upper; r++){
       //* 3. descending
       board[r][C-1].dust_acc = board[r + 1][C-1].dust_acc;
   }
   for(int c = C-1; c > 0; c--){
       //4. traverse (reverse)
       board[upper][c].dust_acc = board[upper][c-1].dust_acc;
   }

    //* Lower
    for(int r = lower + 1; r < R - 1; r++){
        //* 1. descending
        board[r][0].dust_acc = board[r+1][0].dust_acc;
    }
    for(int c = 0; c < C - 1; c++){
        //* 2. traverse
        board[R-1][c].dust_acc = board[R-1][c+1].dust_acc;
    }
    for(int r = R-1; r > lower; r--){
        //* 3. ascending
        board[r][C-1].dust_acc = board[r - 1][C-1].dust_acc;
    }
    for(int c = C-1; c > 0; c--){
        //4. traverse (reverse)
        board[lower][c].dust_acc = board[lower][c-1].dust_acc;
    }

   board[upper][1].dust_acc = board[lower][1].dust_acc = 0;
}

int main(void){
    memset(board, 0, sizeof(board));
    cin >> R >> C >> T;
    int upperC, lowerC, total_dust = 0;

    for(int r = 0; r < R; r++){
        for(int c = 0; c < C; c++){
            cin >> board[r][c].dust_acc;
            if (board[r][c].dust_acc == -1){
                board[r][c].isCleaner = true;
                if(c == 0 and board[r-1][c].isCleaner){
                    //* Cleaner found
                    upperC = r - 1;
                    lowerC = r;
                }
            }
        }
    }

    for(int t = 0; t < T; t++){
        diffusion();
        circulation(upperC,lowerC);
    }

    for(int r = 0; r < R; r++){
        for(int c = 0; c < C; c++){
            if(board[r][c].isCleaner)
                continue;

            total_dust += board[r][c].dust_acc;
        }
    }

    cout << total_dust << "\n";
    return 0;
}
