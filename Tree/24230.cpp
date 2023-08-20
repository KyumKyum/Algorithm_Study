// Algorithm Study
// Backjoon: 트리 색칠하기 (24230)
// https://www.acmicpc.net/problem/24230

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//* Idea:
//* Traverse all trees (pre-order), if diff found, color itself and all of its children.
    //* Will NOT color in real node, pass the current color, and if different happens, add more trial to color.

struct Node {
    int value;
    int color;
    vector<int> children;

    Node(int value){
        this->value = value;
        this->color = 0;
    }
};

vector<Node> tree;
vector<int> expected_color;
int N = 0;
int num_to_color = 0;

void treeInit(int node_num){
    for(int i = 0; i <= node_num; i++){
        //* node number 0 will be not in use.
        Node node(i);
        tree.push_back(node);
    }
}

void traverse_and_color(Node cur_node, int cur_color){
    //* Traverse in pre-order.

    int color = cur_color;

    if(expected_color[cur_node.value] != cur_color){
        //* Diff color.
        num_to_color++;
        color = expected_color[cur_node.value];
    }
    int children_num = cur_node.children.size();

    for(int i = 0; i < children_num; i++){
        traverse_and_color(tree[cur_node.children[i]], color);
    }

    return;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int color = 0;

    cin >> N;

    treeInit(N);

    expected_color.push_back(-1); //* This value will be not used.

    for(int i = 0; i < N; i++){
        cin >> color;
        expected_color.push_back(color);
    }

    for(int i = 0; i < N-1; i++){
        int parent = 0, child = 0;
        cin >> parent >> child;
        if(parent > child) swap(parent, child); //* Parent will be smaller value.
        tree[parent].children.push_back(child);
    }

    traverse_and_color(tree[1], tree[1].color);
    cout << num_to_color << "\n";

    return 0;
}