#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string keyword, meaning;
    Node* left;
    Node* right;
    int height;
    Node(string k, string m) {
        keyword = k;
        meaning = m;
        left = right = nullptr;
        height = 1;
    }
};

class AVL {
    Node* root;

    int height(Node* n) {
        return n ? n->height : 0;
    }

    int getBalance(Node* n) {
        return n ? height(n->left) - height(n->right) : 0;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T = x->right;
        x->right = y;
        y->left = T;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T = y->left;
        y->left = x;
        x->right = T;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    Node* insert(Node* node, string key, string mean) {
        if (!node) return new Node(key, mean);

        if (key < node->keyword)
            node->left = insert(node->left, key, mean);
        else if (key > node->keyword)
            node->right = insert(node->right, key, mean);
        else {
            node->meaning = mean; // Update meaning
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        // Balancing
        if (balance > 1 && key < node->left->keyword)
            return rotateRight(node);
        if (balance < -1 && key > node->right->keyword)
            return rotateLeft(node);
        if (balance > 1 && key > node->left->keyword) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && key < node->right->keyword) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    Node* minValue(Node* n) {
        while (n->left) n = n->left;
        return n;
    }

    Node* deleteNode(Node* root, string key) {
        if (!root) return root;
        if (key < root->keyword)
            root->left = deleteNode(root->left, key);
        else if (key > root->keyword)
            root->right = deleteNode(root->right, key);
        else {
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                delete root;
                return temp;
            }
            Node* temp = minValue(root->right);
            root->keyword = temp->keyword;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->keyword);
        }

        root->height = 1 + max(height(root->left), height(root->right));
        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rotateRight(root);
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0)
            return rotateLeft(root);
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
        return root;
    }

    void inorder(Node* r) {
        if (r) {
            inorder(r->left);
            cout << r->keyword << " : " << r->meaning << endl;
            inorder(r->right);
        }
    }

    void reverseOrder(Node* r) {
        if (r) {
            reverseOrder(r->right);
            cout << r->keyword << " : " << r->meaning << endl;
            reverseOrder(r->left);
        }
    }

    bool search(Node* node, string key, int& comparisons) {
        if (!node) return false;
        comparisons++;
        if (key == node->keyword) return true;
        if (key < node->keyword)
            return search(node->left, key, comparisons);
        else
            return search(node->right, key, comparisons);
    }

public:
    AVL() { root = nullptr; }

    void add(string key, string meaning) {
        root = insert(root, key, meaning);
    }

    void remove(string key) {
        root = deleteNode(root, key);
    }

    void displayAsc() {
        cout << "\nDictionary in Ascending Order:\n";
        inorder(root);
    }

    void displayDesc() {
        cout << "\nDictionary in Descending Order:\n";
        reverseOrder(root);
    }

    void searchKey(string key) {
        int comparisons = 0;
        if (search(root, key, comparisons))
            cout << "Keyword found with " << comparisons << " comparisons.\n";
        else
            cout << "Keyword not found after " << comparisons << " comparisons.\n";
    }

    void maxComparisons() {
        cout << "Maximum comparisons needed: " << height(root) << endl;
    }
};

// Main
int main() {
    AVL dict;
    int choice;
    string key, meaning;

    do {
        cout << "\n1. Add/Update Keyword\n2. Delete Keyword\n3. Display Ascending\n4. Display Descending\n5. Search Keyword\n6. Max Comparisons\n7. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter keyword: ";
            cin >> key;
            cout << "Enter meaning: ";
            cin.ignore();
            getline(cin, meaning);
            dict.add(key, meaning);
            break;
        case 2:
            cout << "Enter keyword to delete: ";
            cin >> key;
            dict.remove(key);
            break;
        case 3:
            dict.displayAsc();
            break;
        case 4:
            dict.displayDesc();
            break;
        case 5:
            cout << "Enter keyword to search: ";
            cin >> key;
            dict.searchKey(key);
            break;
        case 6:
            dict.maxComparisons();
            break;
        case 7:
            break;
        default:
            cout << "Invalid choice!";
        }

    } while (choice != 7);

    return 0;
}