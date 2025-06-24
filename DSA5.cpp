#include <iostream>
#include <stack>
using namespace std;
struct Node {
    char data;
    Node* left;
    Node* right;
    Node(char val) {
        data = val;
        left = right = NULL;
    }
};
bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}
// creating tree
Node* buildTree(string prefix) {
    stack<Node*> st;
    for (int i = prefix.length() - 1; i >= 0; i--) {
        char ch = prefix[i];
        Node* newNode = new Node(ch);

        if (isOperator(ch)) {
            newNode->left = st.top(); st.pop();
            newNode->right = st.top(); st.pop();
        }

        st.push(newNode);
    }
    return st.top();
}

// Non-recursive postorder traversal
void postorder(Node* root) {
    if (root == NULL) return;

    stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        Node* curr = s1.top(); s1.pop();
        s2.push(curr);

        if (curr->left) s1.push(curr->left);
        if (curr->right) s1.push(curr->right);
    }

    cout << "Postorder: ";
    while (!s2.empty()) {
        cout << s2.top()->data;
        s2.pop();
    }
    cout << endl;
}

//delelting the tree
void deleteTree(Node* root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    string prefix = "+--a*bc/def";

    Node* root = buildTree(prefix);
    postorder(root);
    deleteTree(root);

    cout << "Tree deleted!" << endl;
    return 0;
}
