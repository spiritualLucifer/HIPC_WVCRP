#include <bits/stdc++.h>  // For std::remove
using namespace std;

// Class representing a cache block
class CacheBlock {
public:
    int data;          // Data stored in the block
    int frequency;     // Access frequency
    int averageRd;     // Average reuse distance
    int lastCycle;     // Last cycle accessed

    // Constructor
    CacheBlock(int data, int cycle, int avgReuseDistance) {
        this->data = data;
        this->frequency = 1;
        this->averageRd = (avgReuseDistance != -1) ? avgReuseDistance : -1; // Initialize with reuse distance if provided
        this->lastCycle = cycle;
    }

    // Update the block's information on access
    void update(int cycle) {
        if (averageRd == -1) {
            averageRd = cycle - lastCycle; // First access
        } else {
            averageRd = (averageRd * (frequency - 1) + (cycle - lastCycle)) / frequency; // Update average reuse distance
        }
        frequency++;
        lastCycle = cycle; // Update last access cycle
    }
};

// Class representing the cache
class Cache {
private:
    int capacity; // Cache capacity
    int missCount; // Counter for cache misses
    unordered_map<int, CacheBlock*> cache; // Map to hold cache blocks
    unordered_map<int, pair<int, int>> evictedData; // Map to hold evicted block's last cycle and reuse distance
public:
    Cache(int capacity) : capacity(capacity), missCount(0) {}

    // Function to find the victim block based on the weighted policy
    int findVictim() {
         int block1 = -1;
        double minWeight = INT_MAX;
        int block2 = -1;
        int minCycle = INT_MAX;
        for (auto it : cache) {
            CacheBlock* node = it.second;
            int id = it.first;
            double weight = static_cast<double>(node->frequency) / node->averageRd;
            if (weight > 0 && weight < minWeight) {
                minWeight = weight;
                block1 = id;
            }
            if (minCycle > node->lastCycle) {
                minCycle = node->lastCycle;
                block2 = id;
            }
        }
        return (block1 == -1) ? block2 : block1;
    }

public:
    // Constructor

    // Function to access a block
    void accessBlock(int id) {
        static int cycle = 0;
        if (cache.find(id) == cache.end()) { // Cache miss
            missCount++; // Increment miss counter
            if (cache.size() >= capacity) {
                int victimBlock = findVictim();
                CacheBlock* evictedBlock = cache[victimBlock];
                
                // Store the last cycle and average reuse distance of the evicted block
                evictedData[victimBlock] = {evictedBlock->lastCycle, evictedBlock->averageRd};
                
                cache.erase(victimBlock);
                delete evictedBlock;
            }
            int avgReuseDistance = -1;
            int lastCycle = -1;

            // Check if there is any evicted block data to use
            if (evictedData.find(id) != evictedData.end()) {
                lastCycle = evictedData[id].first; // Get the last cycle of the evicted block
                avgReuseDistance = evictedData[id].second; // Get the stored reuse distance
            }
            CacheBlock* newBlock = new CacheBlock(id,cycle,-1);
            cache[id] = newBlock;
        } else { // Cache hit
            cache[id]->update(cycle);
        }

        cycle++; 
    }

    // Function to display the current state of the cache
    void displayCache() const {
        for (const auto& it : cache) {
            CacheBlock* node = it.second;
            cout << "Block ID: " << it.first 
                 << ", Frequency: " << node->frequency 
                 << ", Average Reuse Distance: " << node->averageRd 
                 << ", Last Cycle: " << node->lastCycle << endl;
        }
    }

    // Function to get the total number of cache misses
    int getMissCount() const {
        return missCount;
    }

    // Destructor to clean up memory
    ~Cache() {
        for (auto& it : cache) {
            delete it.second; // Delete each cache block
        }
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
    int size ;
    cout<<"Enter Cache Size : ";
    cin>>size;
    Cache myCache(size);
    for (int access : dummyAccesses) {
        myCache.accessBlock(access);
    }
    cout<<dummyAccesses.size()<<endl;

    cout << "Total Cache Misses: " << myCache.getMissCount() << endl;

    return 0;
}
