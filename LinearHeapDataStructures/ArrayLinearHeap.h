#include<assert.h>
#include<string.h>
#include<iostream>
using namespace std;
class ArrayLinearHeap {
private:
unsigned n; // total number of possible distinct elements
unsigned key_cap; // maximum allowed key value
unsigned max_key; // upper bound of the current maximum key value
unsigned min_key; // lower bound of the current minimum key value
unsigned *keys; // key values of elements
unsigned *heads; // start position of elements with a specific key
unsigned *ids; // element ids
unsigned *rids; // reverse of ids, i.e., rids[ids[i]] = i
public:
ArrayLinearHeap(unsigned _n, unsigned _key_cap):n(_n),key_cap(_key_cap),min_key(_key_cap),
                            max_key(0),heads(nullptr),keys(nullptr),ids(nullptr),rids(nullptr){}
~ArrayLinearHeap() ;
void init(unsigned _n, unsigned _key_cap, unsigned *_ids, unsigned *_keys) ;
unsigned get_n() { return n; }
unsigned get_key_cap() { return key_cap; }
unsigned get_key(unsigned element) { return keys[element]; }
unsigned increment(unsigned element) ;
unsigned decrement(unsigned element) ;
bool get_max(unsigned &element, unsigned &key) ;
bool pop_max(unsigned &element, unsigned &key) ;
bool get_min(unsigned &element, unsigned &key) ;
bool pop_min(unsigned &element, unsigned &key) ;

bool empty() {
		while(min_key <= max_key&&heads[min_key] >= heads[min_key+1]) ++ min_key;
		while(min_key <= max_key&&heads[max_key] >= heads[max_key+1]) -- max_key;

		return min_key > max_key;
	}
};

inline void ArrayLinearHeap::init(unsigned _n, unsigned _key_cap, unsigned *_ids, unsigned *_keys) {
  if(keys == nullptr) keys = new unsigned[n];
	if(ids == nullptr) ids = new unsigned[n];
	if(rids == nullptr) rids = new unsigned[n];
	if(heads == nullptr) heads = new unsigned[key_cap + 2];

  max_key = 0; min_key = _key_cap;
  unsigned *cnt = heads;
  memset(cnt,0,sizeof(unsigned)*(_key_cap + 1));
  for(unsigned i = 0;i < _n; ++i) {
			unsigned key = _keys[i];
			keys[_ids[i]] = key;
			assert(key <= _key_cap);
			++ cnt[key];

			if(key > max_key) max_key = key;
			if(key < min_key) min_key = key;
	}

  for(unsigned i = 1; i <= max_key; ++i) cnt[i] += cnt[i-1];
	for(unsigned i = 0; i < _n; ++i) rids[_ids[i]] = -- cnt[keys[i]];
	for(unsigned i = 0; i < _n; ++i) ids[rids[_ids[i]]] = _ids[i];

	for(unsigned i = 0, j = 0; i <= max_key + 1; ++i) {
			while(j < _n&&keys[ids[j]] < i) ++j;
			heads[i] = j;
	}
}

	// get the (id,key) pair with the maximum key value; return true if success, return false otherwise
	inline bool ArrayLinearHeap::get_max(unsigned &id, unsigned &key) {
		if(empty()) return false;

		id = ids[heads[max_key+1] - 1];
		key = max_key;
		assert(keys[id] == key);

		return true;
	}

	// pop the (id,key) pair with the maximum key value; return true if success, return false otherwise
	inline bool ArrayLinearHeap::pop_max(unsigned &id, unsigned &key) {
		if(empty()) return false;

		id = ids[-- heads[max_key+1]];
		key = max_key;
		assert(keys[id] == key);

		return true;
	}

	// get the (id,key) pair with the minimum key value; return true if success, return false otherwise
	inline bool ArrayLinearHeap::get_min(unsigned &id, unsigned &key) {
		if(empty()) return false;

		id = ids[heads[min_key]];
		key = min_key;
		assert(keys[id] == key);

		return true;
	}

	// pop the (id,key) pair with the minimum key value; return true if success, return false otherwise
	inline bool ArrayLinearHeap::pop_min(unsigned &id, unsigned &key) {
		if(empty()) return false;

		id = ids[heads[min_key] ++];
		key = min_key;
		assert(keys[id] == key);

		return true;
	}

  // increment the key of vertex id by 1
	inline unsigned ArrayLinearHeap::increment(unsigned id) {
		assert(keys[id] + 1 <= key_cap);

		unsigned &key = keys[id];
		unsigned pos1 = heads[key+1]-1, pos2 = rids[id];
		std::swap(ids[pos1], ids[pos2]);
		rids[ids[pos1]] = pos1; rids[ids[pos2]] = pos2;

		if(max_key == key) {
			++ max_key;
			heads[max_key+1] = heads[max_key];
		}

		++ key;
		-- heads[key];

		return keys[id];
	}

	// decrement the key of vertex id by 1
	inline unsigned ArrayLinearHeap::decrement(unsigned id) {
		assert(keys[id] >= 1);

		unsigned &key = keys[id];
		unsigned pos1 = heads[key], pos2 = rids[id];
		std::swap(ids[pos1], ids[pos2]);
		rids[ids[pos1]] = pos1; rids[ids[pos2]] = pos2;

		if(min_key == key) {
			-- min_key;
			heads[min_key] = heads[min_key+1];
		}

		++ heads[key];
		-- key;

		return keys[id];
	}