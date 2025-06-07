#include<bits/stdc++.h>
using namespace std;

class SlidingWindowMax {
private:
    int k;
    deque<pair<int, int>> dq; // pair: <value, index>
    int index = 0;

public:
    SlidingWindowMax(int windowSize) : k(windowSize) {}

    // Process a new incoming element from the stream
    int add(int value) {
        // Remove elements that are out of this window
        while (!dq.empty() && dq.front().second <= index - k)
            dq.pop_front();

        // Remove all elements smaller than the incoming value from the back
        while (!dq.empty() && dq.back().first < value)
            dq.pop_back();

        dq.emplace_back(value, index++);
        
        // Return current max if window is full
        if (index >= k)
            return dq.front().first;

        // Otherwise, return sentinel value 
        return -1;
    }
};

int main() {
    vector<int> dataStream = {10, 5, 2, 7, 8, 7};
    int windowSize = 3;

    SlidingWindowMax stream(windowSize);

    cout << "Streaming sliding window max: ";
    for (int value : dataStream) {
        int maxInWindow = stream.add(value);
        if (maxInWindow != -1)
            cout << maxInWindow << " ";
    }
    cout << endl;

    return 0;
}
