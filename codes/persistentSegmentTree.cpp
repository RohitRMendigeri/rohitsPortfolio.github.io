#include "bits/stdc++.h"
using namespace std;

#define MAXN 100

struct node {
    int val;
    node* left, *right;
    node() {}
    node(node* l, node* r, int v) {
        left = l;
        right = r;
        val = v;
    }
};

int arr[MAXN];
node* version[MAXN];

void build(node* n, int low, int high) {
    if (low == high) {
        n->val = arr[low];
        return;
    }
    int mid = (low + high) / 2;
    n->left = new node(NULL, NULL, 0);
    n->right = new node(NULL, NULL, 0);
    build(n->left, low, mid);
    build(n->right, mid + 1, high);
    n->val = n->left->val + n->right->val;
}

void upgrade(node* prev, node* cur, int low, int high, int idx, int value) {
    if (idx < low || idx > high || low > high) return;
    if (low == high) {
        cur->val = value;
        return;
    }
    int mid = (low + high) / 2;
    if (idx <= mid) {
        cur->right = prev->right;
        cur->left = new node(NULL, NULL, 0);
        upgrade(prev->left, cur->left, low, mid, idx, value);
    } else {
        cur->left = prev->left;
        cur->right = new node(NULL, NULL, 0);
        upgrade(prev->right, cur->right, mid + 1, high, idx, value);
    }
    cur->val = cur->left->val + cur->right->val;
}

int query(node* n, int low, int high, int l, int r) {
    if (r < low || l > high || low > high) return 0;
    if (l <= low && high <= r) return n->val;
    int mid = (low + high) / 2;
    int leftSum = query(n->left, low, mid, l, r);
    int rightSum = query(n->right, mid + 1, high, l, r);
    return leftSum + rightSum;
}

int main() {
    int A[] = {7, 1, 3, 8, 6};
    int n = 5;

    for (int i = 0; i < n; i++) 
        arr[i] = A[i];

    node* root = new node(NULL, NULL, 0);
    build(root, 0, n - 1);
    version[0] = root;

    version[1] = new node(NULL, NULL, 0);
    upgrade(version[0], version[1], 0, n - 1, 3, 2);

    version[2] = new node(NULL, NULL, 0);
    upgrade(version[1], version[2], 0, n - 1, 1, 5);

    cout << "Version 1, query(1,4): " << query(version[1], 0, n - 1, 1, 4) << endl;
    cout << "Version 2, query(0,2): " << query(version[2], 0, n - 1, 0, 2) << endl;
    cout << "Version 0, query(2,4): " << query(version[0], 0, n - 1, 2, 4) << endl;

    return 0;
}
