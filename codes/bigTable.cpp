#include<bits/stdc++.h>

using namespace std;

const int BLOOM_SIZE = 1024;  


bitset<BLOOM_SIZE> bloomBits;  // Bitmap for Bloom Filter

// Simple hash functions for Bloom Filter
unsigned long hash1(const string& key) {
    unsigned long hash = 0;
    for (char c : key) {
        hash = hash * 131 + c; 
    }
    return hash % BLOOM_SIZE;
}

unsigned long hash2(const string& key) {
    unsigned long hash = 0;
    for (char c : key) {
        hash = hash * 137 + c;  //  simple hashing 
    }
    return hash % BLOOM_SIZE;
}

// Add a key to Bloom Filter
void bloomAdd(const string& key) {
    bloomBits.set(hash1(key));
    bloomBits.set(hash2(key));
}

// Check if Bloom Filter might contain the key
bool bloomCheck(const string& key) {
    return bloomBits.test(hash1(key)) && bloomBits.test(hash2(key));
}



vector<pair<string, string>> writeAheadLog;

// Add to WAL (in-memory)
void writeToWAL(const string& key, const string& value) {
    writeAheadLog.push_back(make_pair(key, value));
}


map<string, string> memtable;


void putToMemtable(const string& key, const string& value) {
    memtable[key] = value;
}

// Get value from MemTable, empty string if not found
string getFromMemtable(const string& key) {
    auto it = memtable.find(key);
    if (it != memtable.end()) {
        return it->second;
    }
    return "";
}

// Flush MemTable to SSTable (another map)
map<string, string> sstable;

// Flush MemTable to SSTable and clear MemTable
void flushMemtable() {
    for (auto& kv : memtable) {
        sstable[kv.first] = kv.second;
    }
    memtable.clear();
}

// Read from SSTable
string readFromSSTable(const string& key) {
    auto it = sstable.find(key);
    if (it != sstable.end()) {
        return it->second;
    }
    return "";
}

// --- Main Program ---
int main() {
    string key = "01fe22bcs226";
    string value = "Rohit";

    cout << "[WRITE] Key: " << key << ", Value: " << value << endl;

    // Write: Log, MemTable, Bloom Filter
    writeToWAL(key, value);
    putToMemtable(key, value);
    bloomAdd(key);

    // Read from MemTable
    string memVal = getFromMemtable(key);
    cout << "[READ] From MemTable: " << memVal << endl;

    // Flush MemTable to SSTable
    flushMemtable();

    // Read from SSTable if Bloom Filter says key might exist
    if (bloomCheck(key)) {
        string sstVal = readFromSSTable(key);
        cout << "[READ] From SSTable: " << sstVal << endl;
    } else {
        cout << "[READ] Key not found in Bloom Filter." << endl;
    }

    return 0;
}
