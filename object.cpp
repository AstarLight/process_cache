// read object data from cache or file or db

#include "lru_cache.cpp"
#include "persist_method.cpp"
#include "x2struct/x2struct.hpp" 

template<typename key_t, typename value_t>
class object
{
public:
    typedef typename std::pair<key_t, value_t> key_value_pair_t;
    typedef typename std::list<key_value_pair_t>::iterator list_iterator_t;

	object(int cache_size=1000, const string& save_path="")
	{
		cache = new lru_cache<key_t, value_t>;
		persist = new disk_persist<key_t, value_t>;
		cache->cache_max_size = cache_size;
		persist->file_path = save_path;
	}

	lru_cache<key_t, value_t>* cache;
	disk_persist<key_t, value_t>* persist;
	int visit_cnt;
	int hit_cnt;

	int is_in_memory(const key_t& key);
	value_t get_object(const key_t& key);
	void set_object(const key_t& key, const value_t& data);
	float get_cache_hitrate();
};




template<typename key_t, typename value_t>
int object<key_t, value_t>::is_in_memory(const key_t& key)
{
	return cache->has_key(key);
}

template<typename key_t, typename value_t>
float object<key_t, value_t>::get_cache_hitrate()
{
	return (float)hit_cnt/visit_cnt;
}

template<typename key_t, typename value_t>
value_t object<key_t, value_t>::get_object(const key_t& key)
{
	value_t obj;
	visit_cnt++;
	if (is_in_memory(key))
	{
		obj = cache->get_cache(key);
		hit_cnt++;
	}
	else
	{
		obj = persist->get_from_disk(key);
		cache->set_cache(key, obj);
	}
	return obj;
}

template<typename key_t, typename value_t>
void object<key_t, value_t>::set_object(const key_t& key, const value_t& data)
{
	persist->save_disk(key, data);
}



