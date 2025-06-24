#include <iostream>
using namespace std;
struct Node {
    int data;
    Node *left, *right;
    Node(int value) {
        data = value;
        left = right = NULL;
    }
};
class BinarySearchTree {
private:
    Node *root;
    Node* insertRecursive(Node* root, int value) {
        if (root == NULL) {
            return new Node(value);
        }
        if (value < root->data) {
            root->left = insertRecursive(root->left, value);
        } else {
            root->right = insertRecursive(root->right, value);
        }
        return root;
    }
void inorderRecursive(Node* root) {
        if (root != NULL) {
            inorderRecursive(root->left);
            cout << root->data << " ";
            inorderRecursive(root->right);
        }
    }
    Node* searchRecursive(Node* root, int value) {
        if (root == NULL || root->data == value) {
            return root;
        }
        if (value < root->data) {
            return searchRecursive(root->left, value);
        }
        return searchRecursive(root->right, value);
    }
    Node* findMin(Node* root) {
        while (root->left != NULL) {
            root = root->left;
        }
        return root;
    }
    Node* deleteRecursive(Node* root, int value) {
        if (root == NULL) {
            return root;
        }
        if (value < root->data) {
            root->left = deleteRecursive(root->left, value);
        } else if (value > root->data) {
            root->right = deleteRecursive(root->right, value);
        } else {
            if (root->left == NULL) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == NULL) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteRecursive(root->right, temp->data);
        }
        return root;
    }
    int heightRecursive(Node* root) {
        if (root == NULL) {
            return -1;
        }
        int leftHeight = heightRecursive(root->left);
        int rightHeight = heightRecursive(root->right);
        return 1 + max(leftHeight, rightHeight);
    }
public:
    BinarySearchTree() {
        root = NULL;
    }
    void insert(int value) {
        root = insertRecursive(root, value);
    }
    void inorderTraversal() {
        inorderRecursive(root);
        cout << endl;
    }
    bool search(int value) {
        Node* result = searchRecursive(root, value);
        return (result != nullptr);
    }
    void deleteNode(int value) {
        root = deleteRecursive(root, value);
    }
    int height() {
        return heightRecursive(root);
    }
};
int main() {
    BinarySearchTree bst;
    int choice, value;
    while (true) {
        cout << "\n1. Insert\n2. Delete\n3. Search\n4. Inorder Traversal\n5. Height\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                bst.insert(value);
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                bst.deleteNode(value);
                break;
            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                if (bst.search(value)) {
                    cout << "Value found in the tree.\n";
                } else {
                    cout << "Value not found in the tree.\n";
                }
                break;
            case 4:
                cout << "Inorder Traversal: ";
                bst.inorderTraversal();
                break;
            case 5:
                cout << "Height of the tree: " << bst.height() << endl;
                break;
            case 6:
                cout << "Exiting...\n";
                exit(0);
            default:
                cout << "Invalid choice. Please enter a valid choice.\n";
        }
    }
    return 0;
}
