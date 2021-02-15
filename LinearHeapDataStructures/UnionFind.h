#include<assert.h>

class UnionFind {

private:
  unsigned n;
  unsigned *parent;
  unsigned *rank;
public:
  UnionFind(unsigned _n):n(_n),parent(nullptr),rank(nullptr){}
  ~UnionFind() {
		if(parent != nullptr) {
			delete[] parent;
			parent = nullptr;
		}
		if(rank != nullptr) {
			delete[] rank;
			rank = nullptr;
		}
  }

  void init(unsigned _n = 0) {
		if(_n == 0) _n = n;
		assert(_n <= n);

		if(parent == nullptr) parent = new unsigned[n];
		if(rank == nullptr) rank = new unsigned[n];

		for(unsigned i = 0;i < _n;i ++) {
			parent[i] = i;
			rank[i] = 0;
		}
	}

  void init(unsigned *ids, unsigned _n) {
		assert(_n <= n);

		if(parent == nullptr) parent = new unsigned[n];
		if(rank == nullptr) rank = new unsigned[n];

		for(unsigned i = 0;i < _n;i ++) {
			unsigned u = ids[i];
			parent[u] = u;
			rank[u] = 0;
		}
	}

  void add(unsigned u, unsigned v) {
		parent[u] = v;
		rank[u] = 0;
	}

  unsigned UF_find(unsigned u) {
		unsigned res = u;
		while(parent[res] != res) res = parent[res];
    //路径压缩，所有子孙节点都指向root
		while(parent[u] != res) {
			unsigned tmp = parent[u];
			parent[u] = res;
			u = tmp;
		}
		return res;
	}

  // return the new root of the merged tree
	unsigned UF_union(unsigned u, unsigned v) {
		unsigned tu = UF_find(u);
		unsigned tv = UF_find(v);

		if(tu == tv) return tu;

		unsigned res;
		if(rank[tu] > rank[tv]) {
			res = tu;
			parent[tv] = tu;
		}
		else {
			res = tv;
			parent[tu] = tv;
			if(rank[tu] == rank[tv]) ++ rank[tv];
		}
		return res;
	}

};