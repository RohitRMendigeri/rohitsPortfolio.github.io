#include <iostream>
using namespace std;

const int T = 3; // Minimum degree (every node has at least T-1 and at most 2T-1 keys)

// ------------------- BTreeNode Definition -------------------
class BTreeNode {
public:
    int keys[2 * T - 1];       // Array of keys
    BTreeNode* children[2 * T]; // Child pointers
    int numKeys;               // Current number of keys
    bool isLeaf;               // Is true when node is leaf

    BTreeNode(bool isLeaf);

    void traverse();               // Print the tree in-order
    BTreeNode* search(int k);      // Search a key in the subtree
    void insertNonFull(int k);     // Insert key into non-full node
    void splitChild(int i, BTreeNode* y); // Split child y of this node
};

// ------------------- BTree Definition -------------------
class BTree {
private:
    BTreeNode* root;

public:
    BTree() : root(nullptr) {}

    void traverse() {
        if (root != nullptr)
            root->traverse();
    }

    BTreeNode* search(int k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }

    void insert(int k);
};

// ------------------- BTreeNode Methods -------------------

BTreeNode::BTreeNode(bool leaf) {
    isLeaf = leaf;
    numKeys = 0;
    for (int i = 0; i < 2 * T; ++i)
        children[i] = nullptr;
}

void BTreeNode::traverse() {
    for (int i = 0; i < numKeys; ++i) {
        if (!isLeaf)
            children[i]->traverse();
        cout << " " << keys[i];
    }
    if (!isLeaf)
        children[numKeys]->traverse();
}

BTreeNode* BTreeNode::search(int k) {
    int i = 0;
    while (i < numKeys && k > keys[i])
        i++;
    if (i < numKeys && keys[i] == k)
        return this;
    return (isLeaf ? nullptr : children[i]->search(k));
}

void BTreeNode::insertNonFull(int k) {
    int i = numKeys - 1;

    if (isLeaf) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        numKeys++;
    } else {
        while (i >= 0 && keys[i] > k)
            i--;

        if (children[i + 1]->numKeys == 2 * T - 1) {
            splitChild(i + 1, children[i + 1]);

            if (k > keys[i + 1])
                i++;
        }
        children[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->isLeaf);
    z->numKeys = T - 1;

    for (int j = 0; j < T - 1; ++j)
        z->keys[j] = y->keys[j + T];

    if (!y->isLeaf) {
        for (int j = 0; j < T; ++j)
            z->children[j] = y->children[j + T];
    }

    y->numKeys = T - 1;

    for (int j = numKeys; j >= i + 1; --j)
        children[j + 1] = children[j];

    children[i + 1] = z;

    for (int j = numKeys - 1; j >= i; --j)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[T - 1];
    numKeys++;
}



void BTree::insert(int k) {
    if (root == nullptr) {
        root = new BTreeNode(true);
        root->keys[0] = k;
        root->numKeys = 1;
    } else {
        if (root->numKeys == 2 * T - 1) {
            BTreeNode* s = new BTreeNode(false);
            s->children[0] = root;
            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->children[i]->insertNonFull(k);

            root = s;
        } else {
            root->insertNonFull(k);
        }
    }
}



int main() {
    BTree tree;

    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    for (int k : keys)
        tree.insert(k);

    cout << "B-Tree contents (in-order): ";
    tree.traverse();
    cout << endl;

    int searchKey = 12;
    cout << "Searching for " << searchKey << ": ";
    auto node = tree.search(searchKey);
    cout << (node ? "Found " : "Not found ") << endl;

    return 0;
}

// the ouput  
/*
B-Tree contents (in-order):  5 6 7 10 12 17 20 30
Searching for 99: Not found

c:\Users\subha\Desktop\aps codes>cd "c:\Users\subha\Desktop\aps codes\" && g++ Btree.cpp -o Btree && "c:\Users\subha\Desktop\aps codes\"Btree
B-Tree contents (in-order):  5 6 7 10 12 17 20 30
Searching for 12: Found

*/
