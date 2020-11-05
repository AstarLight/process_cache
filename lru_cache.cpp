#include <iostream>
#include <queue>
#include <map>
#include <string>
#include <unordered_map>
#include <list>
#include <unistd.h>


template<typename key_t, typename value_t>
class lru_cache
{
public:
    typedef typename std::pair<key_t, value_t> key_value_pair_t;
    typedef typename std::list<key_value_pair_t>::iterator list_iterator_t;

    std::list<key_value_pair_t> lru_q;
    std::unordered_map<key_t, list_iterator_t>  lru_table;
    int cache_max_size;

    lru_cache(int size=100) : cache_max_size(size) {}
    int cache_size();
    value_t get_cache(const key_t& key);
    void set_cache(const key_t& key, const value_t& value);
    int has_key(const key_t& key);
}; 


template<typename key_t, typename value_t>
int lru_cache<key_t, value_t>::cache_size()
{
    return lru_q.size();
}


template<typename key_t, typename value_t>
int lru_cache<key_t, value_t>::has_key(const key_t& key)
{
    return lru_table.find(key) != lru_table.end();
}


template<typename key_t, typename value_t>
value_t lru_cache<key_t, value_t>::get_cache(const key_t& key)
{
    auto it = lru_table.find(key);
    if (it == lru_table.end())
    {

        throw std::range_error("There is no such key in cache"); // or read from db
    }
    else
    {
        lru_q.splice(lru_q.begin(), lru_q, it->second);
        return it->second->second;
    }
}

template<typename key_t, typename value_t>
void lru_cache<key_t, value_t>::set_cache(const key_t& key, const value_t& value) 
{
    auto it = lru_table.find(key);
    lru_q.push_front(key_value_pair_t(key, value));
    if (it != lru_table.end()) 
    {
        lru_q.erase(it->second);
        lru_table.erase(it);
    }
    lru_table[key] = lru_q.begin();
    
    if (lru_table.size() > cache_max_size) 
    {
        auto last = lru_q.end();
        last--;
        lru_table.erase(last->first);
        lru_q.pop_back();
    }
}



