// Algorithm Study
// Backjoon: 트리의 순회 (2263)
// https://www.acmicpc.net/problem/2263

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//* Idea:
//* Pre-order => root will always come first place.
//* In-order => root will always in between left and right sub-tree
//* Post-order => root will be printed after all left -> right trees are printed.

int N = 0;
vector<int> postOrder;
vector<int> inOrder;

//* Solved via index: need to solve within O(n) of memory complexity.
void printPreOrder(int i_start, int i_end, int p_start, int p_end){
    //* If pre-order is empty, return.

    if(i_start > i_end) return;

    //* The last element if preorder is root of the current tree.
    int root = postOrder[p_end];

    //* Print Current Root.
    cout << root << " ";

    //* Find current value in inorder.
    int rootIdx = find(inOrder.begin(), inOrder.end(), root) - inOrder.begin();
    //* Based on this root idx, left array will be left sub tree, and right array wil be right subtree.
    //* Inorder: 0 ~ rootIdx - 1  / rootIdx + 1 ~ inOrder.size()-1.
    //* PostOrder: 0 ~ rootIdx - 1 / rootIdx ~ postOrder.size()-2.

    // Tree Size
    int leftTreeSize = rootIdx - i_start;
    int rightTreeSize = i_end - rootIdx;

    //* Print left subtree first.
    //printPreOrder(vecSlice(inOrder, 0, rootIdx), vecSlice(postOrder, 0, rootIdx));

    printPreOrder(i_start, i_start + leftTreeSize - 1,
                  p_start, p_start + leftTreeSize - 1);

    printPreOrder(rootIdx + 1, (rootIdx + 1) + rightTreeSize - 1,
                  p_start + leftTreeSize, (p_start + leftTreeSize) + rightTreeSize - 1);

    //* Then right.
    //printPreOrder(vecSlice(inOrder, rootIdx+1, inOrder.size()), vecSlice(postOrder, rootIdx, postOrder.size()-1));

    return;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int input;
    cin >> N;


    for(int i = 0; i < N; i++){
        cin >> input;
        inOrder.push_back(input);
    }

    for(int i = 0; i < N; i++){
        cin >> input;
        postOrder.push_back(input);
    }

    printPreOrder(0, inOrder.size()-1, 0, postOrder.size()-1);
    cout << "\n";

    return 0;
}