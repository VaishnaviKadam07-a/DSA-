#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n, mark;
    vector<int> marks;

    cout << "Enter number of students: ";
    cin >> n;

    cout << "Enter marks of " << n << " students:\n";
    for (int i = 0; i < n; i++) {
        cin >> mark;
        marks.push_back(mark);
    }

    // Max Heap for maximum marks
    priority_queue<int> maxHeap(marks.begin(), marks.end());

    // Min Heap for minimum marks
    priority_queue<int, vector<int>, greater<int>> minHeap(marks.begin(), marks.end());

    cout << "\nMaximum Marks: " << maxHeap.top();
    cout << "\nMinimum Marks: " << minHeap.top() << endl;

    return 0;
}

