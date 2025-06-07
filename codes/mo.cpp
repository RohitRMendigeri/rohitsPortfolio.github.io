#include <bits/stdc++.h>
using namespace std;

const int MAXVAL = 1e6 + 5;
int blockSize;

struct Query {
    int l, r, idx;
    bool operator<(const Query& other) const {
        int block_a = l / blockSize;
        int block_b = other.l / blockSize;
        if (block_a != block_b) return block_a < block_b;
        return (block_a & 1) ? (r > other.r) : (r < other.r);
    }
};

vector<int> arr = {1, 2, 1, 3, 4}; 
vector<Query> queries = {
    {0, 2, 0},  // Query 0: [0, 2]
    {1, 4, 1},  // Query 1: [1, 4]
    {2, 4, 2}   // Query 2: [2, 4]
};

vector<int> freq(MAXVAL, 0);
int currentAnswer = 0;

void add(int x) {
    if (++freq[x] == 1)
        currentAnswer++;
}

void remove(int x) {
    if (--freq[x] == 0)
        currentAnswer--;
}

int main() {
    int n = arr.size();
    int q = queries.size();
    blockSize = static_cast<int>(sqrt(n));

    vector<int> answers(q);
    sort(queries.begin(), queries.end());

    int currL = 0, currR = -1;

    for (const auto& q : queries) {
        while (currL > q.l)
         add(arr[--currL]);
        while (currR < q.r)
         add(arr[++currR]);
        while (currL < q.l)
         remove(arr[currL++]);
        while (currR > q.r) 
        remove(arr[currR--]);

        answers[q.idx] = currentAnswer;
    }

    for (int i = 0; i < q; ++i) {
        cout << "Query " << i << " : " << answers[i] << " distinct elements\n";
    }

    return 0;
}
