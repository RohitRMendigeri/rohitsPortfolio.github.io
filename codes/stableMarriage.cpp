#include <iostream>
using namespace std;

const int N = 4;

// Preferences of men and women
int menPref[N][N] = {
    {0, 1, 2, 3},
    {2, 0, 1, 3},
    {1, 2, 3, 0},
    {0, 1, 2, 3}
};

int womenPref[N][N] = {
    {1, 0, 3, 2},
    {2, 3, 0, 1},
    {1, 2, 3, 0},
    {0, 1, 2, 3}
};

int womenRank[N][N];
int womanPartner[N];
bool manFree[N];

void stableMarriage() {
    // Initialize womanPartner to -1 (all women free)
    for (int i = 0; i < N; i++) {
        womanPartner[i] = -1;
    }

    // Initialize manFree to false (all men free)
    for (int i = 0; i < N; i++) {
        manFree[i] = false;
    }

    // Preprocess women's preferences for quick lookup
    for (int w = 0; w < N; w++) {
        for (int i = 0; i < N; i++) {
            womenRank[w][womenPref[w][i]] = i;
        }
    }

    int freeCount = N;

    while (freeCount > 0) {
        int m;
        // Find first free man
        for (m = 0; m < N; m++) {
            if (!manFree[m]) break;
        }

        // Go through man's preferences
        for (int i = 0; i < N && !manFree[m]; i++) {
            int w = menPref[m][i];

            if (womanPartner[w] == -1) {
                // Woman is free
                womanPartner[w] = m;
                manFree[m] = true;
                freeCount--;
            } else {
                int currentPartner = womanPartner[w];

                // Check if woman prefers new man
                if (womenRank[w][m] < womenRank[w][currentPartner]) {
                    womanPartner[w] = m;
                    manFree[m] = true;
                    manFree[currentPartner] = false;
                }
            }
        }
    }

    // Print matches
    cout << "Stable Marriages (Man -> Woman):\n";
    for (int w = 0; w < N; w++) {
        cout << "Man " << womanPartner[w] << " is paired to Woman " << w << "\n";
    }
}

int main() {
    stableMarriage();
    return 0;
}
