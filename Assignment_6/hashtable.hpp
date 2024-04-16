#include "hashtable.h"

namespace cop4530 {

// Constructor
template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size) : currentSize{0} {
    size_t capacity = prime_below(size);
    theLists.resize(capacity);
}

// Destructor
template <typename K, typename V>
HashTable<K, V>::~HashTable() {
    makeEmpty();
}

// Public interface

// Check if key k is in the hash table.
template <typename K, typename V>
bool HashTable<K, V>::contains(const K& k) const {
    size_t idx = myhash(k);
    for (const auto& entry : theLists[idx]) {
        if (entry.first == k)
            return true;
    }
    return false;
}

// Check if key-value pair is in the hash table.
template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V>& kv) const {
    size_t idx = myhash(kv.first);
    for (const auto& entry : theLists[idx]) {
        if (entry == kv)
            return true;
    }
    return false;
}

// Add the key-value pair kv into the hash table.
template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V>& kv) {
    size_t idx = myhash(kv.first);
    for (auto& entry : theLists[idx]) {
        if (entry.first == kv.first) {
            entry.second = kv.second;
            return false;
        }
    }
    theLists[idx].emplace_back(kv);
    ++currentSize;
    if (currentSize > theLists.size())
        rehash();
    return true;
}

// Move version of insert.
template <typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K, V>&& kv) {
    size_t idx = myhash(kv.first);
    for (auto& entry : theLists[idx]) {
        if (entry.first == kv.first) {
            entry.second = std::move(kv.second);
            return false;
        }
    }
    theLists[idx].emplace_back(std::move(kv));
    ++currentSize;
    if (currentSize > theLists.size())
        rehash();
    return true;
}

// Delete the key k and the corresponding value if it is in the hash table.
template <typename K, typename V>
bool HashTable<K, V>::remove(const K& k) {
    size_t idx = myhash(k);
    auto& list = theLists[idx];
    auto it = list.begin();
    while (it != list.end()) {
        if (it->first == k) {
            it = list.erase(it);
            --currentSize;
            return true;
        } else {
            ++it;
        }
    }
    return false;
}

// Delete all elements in the hash table.
template <typename K, typename V>
void HashTable<K, V>::clear() {
    makeEmpty();
    currentSize = 0;
}

// Load the content of the file with name filename into the hash table.
template <typename K, typename V>
bool HashTable<K, V>::load(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "** Error: Cannot open file " << filename << " for reading.\n";
        return false;
    }

    makeEmpty();
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        K key;
        V value;
        if (!(iss >> key >> value)) {
            std::cerr << "** Error: Invalid data format in file " << filename << ".\n";
            makeEmpty();
            file.close();
            return false;
        }
        insert({std::move(key), std::move(value)});
    }
    file.close();
    return true;
}

// Display all entries in the hash table.
template <typename K, typename V>
void HashTable<K, V>::dump() const {
    for (size_t i = 0; i < theLists.size(); ++i) {
        std::cout << "v[" << i << "]:";
        for (const auto& entry : theLists[i]) {
            std::cout << " (" << entry.first << ":" << entry.second << ")";
        }
        std::cout << std::endl;
    }
}

// Write all elements in the hash table into a file with name filename.
template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char* filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "** Error: Cannot open file " << filename << " for writing.\n";
        return false;
    }

    for (size_t i = 0; i < theLists.size(); ++i) {
        for (const auto& entry : theLists[i]) {
            file << entry.first << " " << entry.second << "\n";
        }
    }
    file.close();
    return true;
}

// Return the number of elements in the hash table
template <typename K, typename V>
size_t HashTable<K, V>::size() const {
    return currentSize;
}


// Private helper functions

// Delete all elements in the hash table.
template <typename K, typename V>
void HashTable<K, V>::makeEmpty() {
    for (auto& list : theLists)
        list.clear();
}

// Rehash function. Called when the number of elements in the hash table is greater than the size of the vector.
template <typename K, typename V>
void HashTable<K, V>::rehash() {
    std::vector<std::list<std::pair<K, V>>> oldLists = theLists;

    // Create new double-sized, empty table
    theLists.resize(prime_below(2 * theLists.size()));
    for (auto& list : theLists)
        list.clear();

    // Copy table over
    currentSize = 0;
    for (auto& list : oldLists) {
        for (auto& entry : list) {
            insert(std::move(entry));
        }
    }
}

// Return the index of the vector entry where k should be stored.
template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K& k) const {
    static std::hash<K> hf;
    return hf(k) % theLists.size();
}

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

} // namespace cop4530