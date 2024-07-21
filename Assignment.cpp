#include <iostream>
#include <string>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
public:
    Node* root;

    BST() : root(nullptr) {}

    void insert(int data) {
        root = insert(root, data);
    }

    bool search(int data) {
        return search(root, data) != nullptr;
    }

    void remove(int data) {
        root = remove(root, data);
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }

    void preorder() {
        preorder(root);
        cout << endl;
    }

    void postorder() {
        postorder(root);
        cout << endl;
    }

private:
    Node* insert(Node* node, int data) {
        if (node == nullptr) {
            return new Node(data);
        }

        if (data < node->data) {
            node->left = insert(node->left, data);
        } else {
            node->right = insert(node->right, data);
        }

        return node;
    }

    Node* search(Node* node, int data) {
        if (node == nullptr || node->data == data) {
            return node;
        }

        if (data < node->data) {
            return search(node->left, data);
        } else {
            return search(node->right, data);
        }
    }

    Node* remove(Node* node, int data) {
        if (node == nullptr) return node;

        if (data < node->data) {
            node->left = remove(node->left, data);
        } else if (data > node->data) {
            node->right = remove(node->right, data);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

    void preorder(Node* node) {
        if (node != nullptr) {
            cout << node->data << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(Node* node) {
        if (node != nullptr) {
            postorder(node->left);
            postorder(node->right);
            cout << node->data << " ";
        }
    }
};

string base64Decode(const string &encoded) {
    static const string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                       "abcdefghijklmnopqrstuvwxyz"
                                       "0123456789+/";

    auto is_base64 = [](unsigned char c) -> bool {
        return (isalnum(c) || (c == '+') || (c == '/'));
    };

    string ret;
    int in_len = encoded.size();
    int i = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];

    while (in_len-- && (encoded[in_] != '=') && is_base64(encoded[in_])) {
        char_array_4[i++] = encoded[in_]; in_++;
        if (i == 4) {
            for (i = 0; i < 4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }

    if (i) {
        for (int j = i; j < 4; j++)
            char_array_4[j] = 0;

        for (int j = 0; j < 4; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (int j = 0; (j < i - 1); j++) ret += char_array_3[j];
    }

    return ret;
}

void printWelcomeMessage() {
    const string encoded_message = "KioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKgogICogICAgICAgICAgICAgICAgICogCiAgKipXZWxjb21lIHRvIENpcGhlciBTY2hvb2xzIEFzc2lnbm1lbnQgICoKICogICAgICAgICBvZiBEU0EgQ1BQIFN1bW1lciBUcmFpbmluZyAgICoKICogICAgICAgICAgICAgICAgICAqCiAgKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKioqKg==";
    cout << base64Decode(encoded_message) << endl;
}

int main() {
    printWelcomeMessage();

    BST bst;
    int n, value;

    cout << "Enter the number of elements to insert into the BST: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cout << "Enter value " << i + 1 << ": ";
        cin >> value;
        bst.insert(value);
    }

    cout << "\n1. Inorder traversal: ";
    bst.inorder();

    cout << "\n2. Preorder traversal: ";
    bst.preorder();

    cout << "\n3. Postorder traversal: ";
    bst.postorder();

    cout << "\nEnter a value to search: ";
    cin >> value;
    cout << "4. Search " << value << ": " << (bst.search(value) ? "Found" : "Not Found") << endl;

    cout << "\nEnter a value to delete: ";
    cin >> value;
    cout << "5. Deleting " << value << endl;
    bst.remove(value);
    cout << "   Inorder traversal after deleting " << value << ": ";
    bst.inorder();

    return 0;
}
