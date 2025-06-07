#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
using namespace std;

const int MAX_LEVEL = 6; // Maximum levels allowed
const float P = 0.5;     // Probability for increasing level

// Node structure
class Node {
public:
    int value;
    Node** forward;

    Node(int val, int level) {
        value = val;
        forward = new Node*[level + 1];
        for (int i = 0; i <= level; i++)
            forward[i] = nullptr;
    }

    ~Node() {
        delete[] forward;
    }
};

// SkipList class
class SkipList {
private:
    int level;
    Node* header;

    int randomLevel() {
        int lvl = 0;
        while ((float)rand() / RAND_MAX < P && lvl < MAX_LEVEL)
            lvl++;
        return lvl;
    }

public:
    SkipList() {
        level = 0;
        header = new Node(-1, MAX_LEVEL); // Sentinel head node
        srand(time(0)); // Seed the random generator
    }

    void insert(int value) {
        Node* current = header;
        Node* update[MAX_LEVEL + 1];

        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < value)
                current = current->forward[i];
            update[i] = current;
        }

        current = current->forward[0];

        if (current == nullptr || current->value != value) {
            int newLevel = randomLevel();

            if (newLevel > level) {
                for (int i = level + 1; i <= newLevel; i++)
                    update[i] = header;
                level = newLevel;
            }

            Node* newNode = new Node(value, newLevel);
            for (int i = 0; i <= newLevel; i++) {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }

            cout << "Inserted: " << value << " at level " << newLevel << endl;
        } else {
            cout << "Value already exists: " << value << endl;
        }
    }

    bool search(int value) {
        Node* current = header;
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->value < value)
                current = current->forward[i];
        }

        current = current->forward[0];

        if (current && current->value == value) {
            cout << "Found: " << value << endl;
            return true;
        } else {
            cout << "Not found: " << value << endl;
            return false;
        }
    }

    void remove(int value) {
        Node* current = header;
        Node* update[MAX_LEVEL + 1];

        for (int i = level; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->value < value)
                current = current->forward[i];
            update[i] = current;
        }

        current = current->forward[0];

        if (current && current->value == value) {
            for (int i = 0; i <= level; i++) {
                if (update[i]->forward[i] != current)
                    break;
                update[i]->forward[i] = current->forward[i];
            }

            delete current;

            while (level > 0 && header->forward[level] == nullptr)
                level--;

            cout << "Deleted: " << value << endl;
        } else {
            cout << "Value not found for deletion: " << value << endl;
        }
    }

    void print() {
        cout << "\nSkip List Structure:\n";
        for (int i = level; i >= 0; i--) {
            Node* node = header->forward[i];
            cout << "Level " << i << ": ";
            while (node != nullptr) {
                cout << node->value << " ";
                node = node->forward[i];
            }
            cout << endl;
        }
    }

    ~SkipList() {
        Node* current = header;
        while (current != nullptr) {
            Node* next = current->forward[0];
            delete current;
            current = next;
        }
    }
};

// Driver code
int main() {
    SkipList list;

    list.insert(3);
    list.insert(6);
    list.insert(7);
    list.insert(9);
    list.insert(12);
    list.insert(19);
    list.insert(17);

    list.print();

    list.search(6);
    list.search(15);

    list.remove(6);
    list.remove(20);

    list.print();

    return 0;
}
