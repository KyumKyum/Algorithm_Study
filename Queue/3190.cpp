// Algorithm Study
// Backjoon: 뱀 (3190)
// https://www.acmicpc.net/problem/3190

#include <iostream>
#include <queue>
#include <map>
#include <cstring>
#include <algorithm>

using namespace std;

//* Idea: Queue
//* Save snake information in queue.

bool apple[101][101];
bool board[101][101];
queue< pair<int, int> > snake;
queue< pair<int, char> > mvmt;
int N, K, L = 0;

map<char, char> D_move;
map<char, char> L_move;

void determine_dir(char cmd, char& move){
    if(cmd == 'D'){
        move = D_move.find(move)->second;
    }else{
        move = L_move.find(move)->second;
    }
    return;
}

void move_snake(char move, pair<int,int> &body){
    if(move == 'R'){
        body.second += 1;
    }else if(move == 'L'){
       body.second -= 1;
    }else if(move == 'U'){
        body.first -= 1;
    }else{
        body.first += 1;
    }
    return;
}

int dummy(void){
    int sec = 1;
    char move = 'R';//* init mvmt = Right.
    //* Move right = right, positive (1)
    //* Move under = right, negative (-1)
    //* Move up = left, positive (1)
    //* Move left = left, negative (-1)

    while(true){
        //* Get head location
        pair<int, int> head = snake.front();
        //* Move
        move_snake(move, head);

        //* Check collision 1: Collide with wall
        if(head.first > N || head.second > N || head.first <= 0 || head.second <= 0){
            break; //* Collision happens.
        }

        //* Check collision 2: Collide with its body
        if(board[head.first][head.second]){
            break;
        }

        //* Check apple.
        if(apple[head.first][head.second]){
            //* it grows.
            apple[head.first][head.second] = false;
            board[head.first][head.second] = true; //* Snake moves
            int size = snake.size();
            snake.push(head);
            for(int i = 0; i < size; i++){
                pair<int, int> tail = snake.front(); snake.pop();
                snake.push(tail);
            }
        }else{
            //* it moves.
            board[head.first][head.second] = true; //* Snake moves
            int size = snake.size();
            snake.push(head);
            for(int i = 0; i < size-1; i++){
                pair<int, int> tail = snake.front(); snake.pop();
                //*Check Collision
                snake.push(tail);
            }
            pair<int, int> remove = snake.front(); snake.pop(); //* Remove last tail
            board[remove.first][remove.second] = false;
        }

        //* Check next movement.
        if(mvmt.front().first == sec){
            char cmd = mvmt.front().second;
            determine_dir(cmd, move);
            mvmt.pop();
        }
        //* Second increases.
        sec++;
    }

    return sec;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);
    memset(apple, false, sizeof(apple));
    memset(board, false, sizeof(board));

    //* Init Move
    D_move.insert(pair<char, char>('R', 'D')); D_move.insert(pair<char, char>('D', 'L')); D_move.insert(pair<char, char>('L', 'U')); D_move.insert(pair<char, char>('U', 'R'));
    L_move.insert(pair<char,char>('R', 'U')); L_move.insert(pair<char,char>('U', 'L')); L_move.insert(pair<char,char>('L', 'D')); L_move.insert(pair<char,char>('D', 'R'));

    cin >> N; //* Board Size;
    cin >> K; //* Apple Num

    for(int i = 0; i < K; i++){
        pair<int, int> pos;
        cin >> pos.first >> pos.second;
        apple[pos.first][pos.second] = true; //* Apple located
    }

    cin >> L; //* Total Movement;

    for(int i = 0; i < L; i++){
        pair<int, char> move;
        cin >> move.first >> move.second;
        mvmt.push(move);
    }

    pair<int, int> init(1,1); //* Starting position of snake.
    board[1][1] = true;
    snake.push(init);

    cout << dummy() << "\n";

    return 0;
}

