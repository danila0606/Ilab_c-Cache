#pragma once

#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <functional>
//LFU

/*template <typename Key>
struct set_comp {
    bool operator () (const std::pair<Key, int>& l, const std::pair<Key, int>& r) const {
        return l.second < r.second;
    }
};*/

template <typename Key, typename  Value>
class Cache {
    using pairKV = std::pair<Key,Value>;


public:
    Cache(int n):
    N(n), hit(0) {};

    void PutValue(const pairKV& pkv);
    Value GetValue(const Key& key);
    void printHash() {
        for (const auto& i:hashTable) {
            std::cout<<i.first<<" ";
        }
        std::cout<<std::endl;
    }
    size_t GetHit() const {return hit;};
    const size_t Size() { return N;};
private:
    size_t N; // size of cache
    size_t hit;

    std::unordered_map<Key, std::pair<Value,
        typename std::multimap<int, Key>::iterator>> hashTable;

    std::multimap <int, Key> Queue;
   // std::unordered_map<Key, typename std::multimap<int, Key>::iterator> KeySearch;
};

template <typename Key, typename Value>
void Cache<Key, Value>::PutValue (const pairKV& pkv) {
    auto iter = hashTable.find(pkv.first);

    if (iter == hashTable.end()) {

        if (hashTable.size() >= N) {
            Key del_key = Queue.begin()->second;
            Queue.erase(Queue.begin());

            hashTable.erase(del_key);
        }

        hashTable[pkv.first] = std::make_pair
                (pkv.second,Queue.insert({1,pkv.first}));
        //std::cout<<hashTable.size()<<" ";
    }
    else {
        hit++;
        int old_count = iter->second.second->first;
        Queue.erase(iter->second.second);
        iter->second.second = Queue.insert({++old_count, pkv.first});

        iter->second.first = pkv.second;
    }
}


template <typename Key, typename Value>
Value Cache<Key, Value>::GetValue(const Key& key){
    auto iter = hashTable.find(key);

    if (iter == hashTable.end()) {
        throw std::invalid_argument("Expression : last key not found in cache\n");
    }

    int old_count = iter->second.second->first;
    Queue.erase(iter->second.second);
    iter->second.second = Queue.insert({++old_count, key});

    //PlusCount(iter->second.second, key);

    return iter->second.first;
}

//template<typename Key, typename Value>
/*void Cache<Key, Value>::PlusCount(typename std::multimap<int, Key>::iterator it, const Key &key) {
    int old_count = it->first;
    Queue.erase(it);
    it = Queue.insert({old_count++, key});
}*/
