

class ListLinearHeap {

private:
  unsigned int n; //total V
  unsigned int key_cap; // maximum allowed key value
  unsigned int max_key; // upper bound of the current maximum key value
  unsigned int min_key; //lower bound of the current minimum key value
  unsigned int *keys; // key values of elements
  unsigned int *heads; //the first element in a doubly linked list
  unsigned int *pres; // previous element in a doubly linked list
  unsigned int *nexts; // next element

public:
  ListLinearHeap(unsigned _n, unsigned _key_cap):n(_n),key_cap(_key_cap),min_key(_key_cap),
                            max_key(0),heads(nullptr),keys(nullptr),pres(nullptr),nexts(nullptr){}
  ~ListLinearHeap();
  void init(unsigned _n, unsigned _key_cap, unsigned *_elems, unsigned *_keys);
  void insert(unsigned element, unsigned key);
  unsigned remove(unsigned element);
  unsigned get_n() {return n;}
  unsigned get_key_cap() {return key_cap;}
  unsigned get_key(unsigned element) {return keys[element];}
  unsigned increment(unsigned element, unsigned inc);
  unsigned decrement(unsigned element, unsigned dec);
  bool get_max(unsigned &element, unsigned &key);
  bool pop_max(unsigned &element, unsigned &key);
  bool get_min(unsigned &element, unsigned &key);
  bool pop_min(unsigned &element, unsigned &key);
  bool empty() {tighten();	return min_key > max_key;}

private:
  void tighten() {
		while(min_key <= max_key&&heads[min_key] == n) ++ min_key;
		while(min_key <= max_key&&heads[max_key] == n) -- max_key;
	}
};

inline void ListLinearHeap::init(unsigned _n, unsigned _key_cap, unsigned *_elems, unsigned *_keys)
{
  if(keys == nullptr) keys = new unsigned[n];
  if(pres == nullptr) pres = new unsigned[n];
  if(nexts == nullptr) nexts = new unsigned[n];
  if(heads == nullptr) heads = new unsigned[key_cap + 1];
  min_key = _key_cap; max_key = 0;
  for(unsigned i = 0; i <= _key_cap; ++i) heads[i] = n;
  for(unsigned i = 0; i < _n; ++i) insert(_elems[i], _keys[i]);
}

inline void ListLinearHeap::insert(unsigned element, unsigned key)
{
  keys[element] = key;
  pres[element] = n;
  nexts[element] = heads[key];
  if(heads[key] != n) pres[heads[key]] = element;
  heads[key] = element;
  if(key < min_key) min_key = key;
  if(key > max_key) max_key = key;
}

inline unsigned ListLinearHeap::remove(unsigned element)
{
  if(pres[element] = n) {
    heads[keys[element]] = nexts[element];
    if(nexts[element] != n) pres[nexts[element]] = n;
  }else
  {
    nexts[pres[element]] = nexts[element];
    if(nexts[element] != n) pres[nexts[element]] = pres[element];
  }

  return keys[element];
  
}

inline unsigned ListLinearHeap::increment(unsigned element, unsigned inc = 1)
{
  unsigned new_key = remove(element) + inc;
  insert(element, new_key);

  return new_key;
}

inline unsigned ListLinearHeap::decrement(unsigned element, unsigned dec = 1)
{
  unsigned new_key = remove(element) - dec;
  insert(element, new_key);

  return new_key;
}

inline bool ListLinearHeap::get_max(unsigned &element, unsigned &key)
{
  if(empty()) return false;

  element = heads[max_key];
  key = max_key;
  return true;

}

inline bool ListLinearHeap::pop_max(unsigned &element, unsigned &key)
{
  if(empty()) return false;

  element = heads[max_key];
  key = max_key;
  remove(element);

  return true;

}

inline bool ListLinearHeap::get_min(unsigned &element, unsigned &key)
{
  if(empty()) return false;

  element = heads[min_key];
  key = min_key;
  return true;

}

inline bool ListLinearHeap::pop_min(unsigned &element, unsigned &key)
{
  if(empty()) return false;

  element = heads[min_key];
  key = min_key;
  remove(element);
  return true;

}