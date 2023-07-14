// Algorithm Study
// Backjoon: 박스 채우기 (9251)
// https://www.acmicpc.net/problem/9251
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

int dp[1000][1000];
string a;
string b;


int LCS(){
    //* Strategy: Bruteforce + DP
    //* Compare each letter in its position.
    //* DP: Keep tracking maximum value of LCS.
    //* if same, dp[x][y] = dp[x-1][y-1] + 1 (plus 1 from LCS before comparison)
    //* If different, dp [x][y] = max(dp[x-1][y], dp[x][y-1]) (get longer LCS without this letter)
        //* If different, compare LCS between a[x-1] & b[y] and a[x] & b[y-1], get longger value.
    for(int i = 0; i < a.length(); i++){
        for(int j = 0; j < b.length(); j++){
            if(a[i] == b[j]){
                if(i <= 0 or j <= 0)
                    dp[i][j] = 1;
                else
                    dp[i][j] = dp[i-1][j-1] + 1;
            }else{
                int upper = (i > 0) ? dp[i-1][j] : 0;
                int left = (j > 0) ? dp[i][j-1] : 0;
                dp[i][j] = max(upper,left);
            }
        }
    }

    return dp[a.length() - 1][b.length() -1];

}


int main(){
    memset(dp, -1, sizeof(dp));

    cin >> a;
    cin >> b;

    cout << LCS() << endl;

    return 0;
}
