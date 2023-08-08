// Algorithm Study
// Backjoon: 좋은 친구 (3078)
// https://www.acmicpc.net/problem/3078

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//* Idea: Queue + Sliding Window
//* Sliding Window: only care about effective range.
//* Queue: Sort all those name in different queue by its name
//* Eliminate all students having same or higher rank than current student (removing not necessary one)
//* ==> This is because the student's name could be a same.
//* Rest of the element will be a good friend to current student!

struct Student{
    string name;
    int rank;
};

queue<Student> sorted[21]; //* Save student's name by its lenght.
vector<Student> students;

int N, K = 0;

void sort_by_name(Student student){
    sorted[student.name.length()].push(student);
    return;
}

long long good_friend(void){
    long long match = 0;
    int size = students.size();

    for(int i = 0; i <= min(K, size - 1); i++){
        sort_by_name(students[i]);
    }

    //* Iterate all student.

    for(int i = 0; i < size; i++){
        Student cur = students[i];

        if(!sorted[cur.name.length()].empty()) {
            while(!sorted[cur.name.length()].empty() && sorted[cur.name.length()].front().rank <= i){
                //* Pop outdated one.
                sorted[cur.name.length()].pop();
            }

            //* Rest of them will be a good friend.
            match += sorted[cur.name.length()].size();

            //* Push new student.
            if(K + i + 1 < size){
                sort_by_name(students[K + i + 1]);
            }
        }
    }

    return match;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    string name;
    cin >> N >> K;

    for(int i = 0; i < N; i++){
        cin >> name;
        Student student = {name, i};
        students.push_back(student);
    }

    cout << good_friend() << "\n";
    return 0;
}
