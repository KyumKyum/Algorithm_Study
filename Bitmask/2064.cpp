// Algorithm Study
// Backjoon: IP 주소 (2064)
// https://www.acmicpc.net/problem/2064

#include <iostream>
#include <bitset>
#include <string>
#include <iterator>
#include <sstream>
#include <vector>

using namespace std;

int ip[1000];
int mask = 0;
int N = 0;

//* Bit-mask
//* Mask: Before difference, fill with 1. Fill with 0 after difference.
//* Address: AND operation with any address given. (That is what mask for!)

void get_mask(void){
    int fill = 0;
    bool cont = true;
    //* Get mask; Apply and operation to all digit (Find the difference.)
    //* If difference found, apply 1 before difference, and 0 to after difference.
    for(int i = 31; i >= 0 ; i--){
        fill = i;
        int digit = (1 << i);
        for(int j = 0; j < N-1; j++){
            //* Compare digit
            if((ip[j] & digit) != (ip[j+1] & digit)){
                cont = false;
                break;
            }
        }
        if(!cont){
            break;
        }
        mask |= digit;
    }
    return;
}

void print_addr(void){
    vector<unsigned long> address;
    bitset<32> addr =  bitset<32>(ip[0] & mask);
    for(int i = 0; i < 4; i++){
        address.push_back(bitset<8>(addr.to_ulong()).to_ulong());
        addr = addr >> 8;
    }

    for(int i = 3; i > 0; i--){
        cout << address[i] << ".";
    }
    cout << address[0] << "\n";

}

void print_mask(void){
    vector<unsigned long> address;
    bitset<32> addr =  bitset<32> (mask);
    for(int i = 0; i < 4; i++){
        address.push_back(bitset<8>(addr.to_ulong()).to_ulong());
        addr = addr >> 8;
    }

    for(int i = 3; i > 0; i--){
        cout << address[i] << ".";
    }
    cout << address[0] << "\n";

}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);


    fill(begin(ip), end(ip), 0);
    string addr, buf;

    cin >> N;

    for(int i = 0; i < N; i++){
        cin >> addr;
        istringstream ss(addr);
        while(getline(ss, buf, '.')){
            ip[i] = (ip[i] << 8); //* Shift
            ip[i] |= stoi(buf);
        }
    }

    get_mask();
    print_addr();
    print_mask();

    return 0;
}