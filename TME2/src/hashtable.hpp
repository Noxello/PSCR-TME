#include <utility>
#include <list>
#include <vector>
#include <cstring>

using namespace std;

template <typename K, typename V>
class HashTable{
    vector<list<pair<K,V>>> buckets;
    size_t nb_elems;
    public:
        HashTable(size_t size = 30000):buckets(size), nb_elems(0){
        }

        V* get(const K& key){
            size_t indice = std::hash<K>()(key) % buckets.size();
            auto &list = buckets[indice];
            for (auto &p : list){
                if(p.first == key)
                    return &(p.second);
            }
            return nullptr;
        }

        bool put (const K& key, const V &value){
            size_t indice = std::hash<K>()(key) % buckets.size();
            auto &list = buckets[indice];
            bool valuePresent = false;
            for (auto &p : list){
                if(p.first == key){
                    valuePresent = true;
                    p.second = value;
                    break;
                }
            }
            if (!valuePresent){
                list.push_back(std::make_pair(key,value));
                nb_elems++;
            }
            return valuePresent;

        }
        size_t size() const{
            return nb_elems;
        }
        vector<list<pair<K,V>>> *getBuckets(){
            return &buckets;
        }
};