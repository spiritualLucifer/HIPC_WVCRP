#include <bits/stdc++.h>
using namespace std;

// Class representing a cache block
class CacheBlock {
public:
    int data;

    CacheBlock() : data(0) {} // Default constructor
    CacheBlock(int data) : data(data) {}
};

// Class representing the FIFO Cache
class FIFOCache {
private:
    int capacity;                        // Cache capacity
    int missCount;                       // Counter for cache misses
    deque<int> cacheQueue;               // Deque to maintain FIFO order
    unordered_map<int, CacheBlock> cacheMap; // Map to store cache blocks

public:
    // Constructor
    FIFOCache(int capacity) : capacity(capacity), missCount(0) {}

    // Function to access a block
    void accessBlock(int id) {
        auto it = cacheMap.find(id);
        if (it == cacheMap.end()) { // Cache miss
            missCount++; // Increment miss counter
            if (cacheQueue.size() >= capacity) {
                // Evict the first element from the deque (FIFO)
                int evictedBlock = cacheQueue.front();
                cacheQueue.pop_front();
                cacheMap.erase(evictedBlock);
            }
            // Insert the new block into the cache
            cacheQueue.push_back(id);
            cacheMap[id] = CacheBlock(id);
        }
        // No action required for cache hits in FIFO
    }

    // Function to display the current state of the cache
    void displayCache() const {
        cout << "Current Cache State: ";
        for (int blockID : cacheQueue) {
            cout << blockID << " ";
        }
        cout << endl;
    }

    // Function to get the total number of cache misses
    int getMissCount() const {
        return missCount;
    }
};

// Function to read array from a text file and populate the vector
void readArrayFromFile(const string& fileName, vector<int>& dummyAccesses) {
    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Unable to open file: " << fileName << endl;
        return;
    }
    string line;
    getline(inFile, line);

    // Remove brackets and parse numbers
    line.erase(remove(line.begin(), line.end(), '['), line.end());
    line.erase(remove(line.begin(), line.end(), ']'), line.end());

    stringstream ss(line);
    string temp;
    while (getline(ss, temp, ',')) {
        dummyAccesses.push_back(stoi(temp));
    }
    inFile.close();
}

int main() {
    vector<int> dummyAccesses;
    readArrayFromFile("../numGen/random_numbers.txt", dummyAccesses);

    if (dummyAccesses.empty()) {
        cerr << "No data found in the input file!" << endl;
        return 1;
    }

    int cacheSize;
    cout << "Enter Cache Size: ";
    cin >> cacheSize;

    if (cacheSize <= 0) {
        cerr << "Cache size must be greater than 0!" << endl;
        return 1;
    }

    FIFOCache myCache(cacheSize);

    for (int access : dummyAccesses) {
        myCache.accessBlock(access);
    }

    cout << "\nTotal Cache Misses: " << myCache.getMissCount() << endl;

    // Uncomment to display the final state of the cache
    // myCache.displayCache();

    return 0;
}
