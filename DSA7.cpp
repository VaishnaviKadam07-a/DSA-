#include <iostream>
#include <climits>
using namespace std;

class tree {
    int a[20][20], visited[20], v, e;
public:
    void input();
    void display();
    void minimum();
};

void tree::input() {
    int l, u, w;
    cout << "Enter the number of branches (vertices): ";
    cin >> v;
    //MATRIX LOOP
    for (int i = 0; i < v; i++) {
        visited[i] = 0;
        for (int j = 0; j < v; j++) {
            a[i][j] = INT_MAX;  // Use INT_MAX as infinity
        }
    }

    cout << "Enter the number of connections (edges): ";
    cin >> e;

    for (int i = 0; i < e; i++) {
        cout << "Enter the end branches of connection (1-based index): ";
        cin >> l >> u;
        cout << "Enter the phone company charges for this connection: ";
        cin >> w;
        a[l - 1][u - 1] = a[u - 1][l - 1] = w;
    }
}

void tree::display() {
    cout << "\nAdjacency Matrix (INF = No connection):" << endl;
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            if (a[i][j] == INT_MAX)
                cout << "INF\t";
            else
                cout << a[i][j] << "\t";
        }
        cout << endl;
    }
}

void tree::minimum() {
    int total = 0;
    visited[0] = 1; // Start with node 0

    cout << "\nMinimum Spanning Tree using Prim's Algorithm:\n";

    for (int count = 0; count < v - 1; count++) {
        int min = INT_MAX, p = -1, q = -1;

        for (int i = 0; i < v; i++) {
            if (visited[i]) {
                for (int j = 0; j < v; j++) {
                    if (!visited[j] && a[i][j] < min) {
                        min = a[i][j];
                        p = i;
                        q = j;
                    }
                }
            }
        }

        if (p == -1 || q == -1) {
            cout << "\nThe graph is not connected. MST cannot be formed completely.\n";
            return;
        }

        visited[q] = 1;
        cout << "Connection: " << (p + 1) << " -> " << (q + 1) << " with cost: " << min << endl;
        total += min;
    }

    cout << "\nTotal minimum cost of all connections: " << total << endl;
}

int main() {
    int ch;
    tree t;

    do {
        cout << "\n========== PRIM'S ALGORITHM MENU ==========" << endl;
        cout << "1. Input Graph\n2. Display Matrix\n3. Find Minimum Spanning Tree\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
        case 1:
            cout << "\n--- Input Values ---\n";
            t.input();
            break;
        case 2:
            cout << "\n--- Display Matrix ---\n";
            t.display();
            break;
        case 3:
            cout << "\n--- Minimum Spanning Tree ---\n";
            t.minimum();
            break;
        case 4:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please enter 1-4.\n";
        }
    } while (ch != 4);

    return 0;
}