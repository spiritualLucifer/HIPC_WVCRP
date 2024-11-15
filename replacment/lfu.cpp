#include <bits/stdc++.h>
using namespace std;

// Class representing a cache block
class CacheBlock {
public:
    int data;          // Data stored in the block
    int frequency;     // Frequency of access

    // Constructor
    CacheBlock(int data) : data(data), frequency(1) {}
};

// Class representing the LFU Cache
class LFUCache {
private:
    int capacity; // Cache capacity
    int missCount; // Counter for cache misses
    unordered_map<int, list<pair<int, CacheBlock>>::iterator> cacheMap; // Map to store cache block positions in the list
    list<pair<int, CacheBlock>> cacheList; // List to maintain LFU order

public:
    // Constructor
    LFUCache(int capacity) : capacity(capacity), missCount(0) {}

    // Function to access a block
    void accessBlock(int id) {
        static int cycle = 0;
        auto it = cacheMap.find(id);

        if (it == cacheMap.end()) { // Cache miss
            missCount++; // Increment miss counter

            if (cacheList.size() >= capacity) { // If cache is full
                // Find and remove the least frequently used block
                auto lfuBlock = min_element(cacheList.begin(), cacheList.end(),
                    [](const pair<int, CacheBlock>& a, const pair<int, CacheBlock>& b) {
                        return a.second.frequency < b.second.frequency;
                    });

                cacheMap.erase(lfuBlock->first);
                cacheList.erase(lfuBlock);
            }

            // Insert the new block into the cache
            CacheBlock newBlock(id);
            cacheList.push_front({id, newBlock});
            cacheMap[id] = cacheList.begin();
        } else { // Cache hit
            // Move the accessed block to the front (most recently used)
            cacheList.splice(cacheList.begin(), cacheList, it->second);
            it->second->second.frequency++; // Increase access frequency
        }

        cycle++;
    }

    // Function to display the current state of the cache
    void displayCache() const {
        for (const auto& it : cacheList) {
            cout << "Block ID: " << it.first << ", Frequency: " << it.second.frequency << endl;
        }
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
    getline(inFile, line);  // Read the entire line

    // Remove the brackets and commas, then parse the numbers
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
    int cacheSize;
    cout << "Enter Cache Size: ";
    cin >> cacheSize;
    LFUCache myCache(cacheSize); // Initialize cache with a capacity of cacheSize

    for (int access : dummyAccesses) {
        myCache.accessBlock(access); // Access blocks and handle evictions
    }

    cout << "\nTotal Cache Misses: " << myCache.getMissCount() << endl;

    // Uncomment to display the final state of the cache
    // cout << "\nFinal Cache State:\n";
    // myCache.displayCache();

    return 0;
}
