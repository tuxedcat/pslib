#pragma once
#include "Core.h"
#include "UnionFind.h"

template<typename T>
struct Graph {
	struct Edge {
		int s;
		int e;
		int ei;
		T w;
		Edge():s(0),e(0),ei(0),w(T()){};
		Edge(int s, int e, int ei, T w):s(s),e(e),ei(ei),w(w){};
		bool operator<(const Edge &r)const { return w < r.w; }
		bool operator>(const Edge &r)const { return w > r.w; }
	};
	int n;
	Arr<Arr<Edge>> g;

	Graph(int n=0) :n(n), g(n) {}
	Graph(const Graph& r) :n(r.n), g(r.g) {}

	void add_edge(int s, int e, T w, bool bidir=false){
		g[s].pushb({s, e, sz(g[s]), w});
		if(bidir)
			g[e].pushb({e, s, sz(g[e]), w});
	}

	struct DNV{T dist; int v; bool operator<(const DNV& r)const{return dist>r.dist;}};
	void dijkstra(Arr<T>& d, Arr<Edge>& p, int s) {
		PQ<DNV> pq;
		d = Arr<T>(n, inf<T>());
		p = Arr<Edge>(n, {-1,-1,-1,-1});
		pq.push({ d[s]=0, s });
		while (size(pq)){
			auto c = pq.top();
			pq.pop();

			if (c.dist != d[c.v])
				continue;

			auto& cg = g[c.v];
			for (auto &i : cg) {
				if (d[i.e] > c.dist + i.w) {
					p[i.e] = i;
					pq.push({ d[i.e]=c.dist + i.w, i.e });
				}
			}
		}
	}

	Arr<Arr<int>> floyd(){
		Arr<Arr<int>> a(n, Arr<int>(n,inf<int>()));
		rep(i,n){
			for(auto j:g[i])
				a[i][j.e]=1;
			a[i][i]=0;
		}
		rep(k,n)
			rep(i,n)
				rep(j,n)
					a[i][j]=min(a[i][j], a[i][k]+a[k][j]);
		return a;
	}

	bool spfa(Arr<T>& ub, Arr<Edge>& p, int s) {
		deque<int> q;
		Arr<bool> inq(n);
		ub = Arr<T>(n, inf<T>());
		p = Arr<Edge>(n,{-1,-1,-1,-1});
		int c[n]{};

		ub[s] = 0;
		inq[s] = true;
		q.pushb(s);
		while(sz(q)){
			int j = q.front();
			inq[j] = false;
			q.popf();
			for (auto k : g[j]) {
				if (valid_spfa_edge(k) && ub[j] + k.w < ub[k.e]) {
					p[k.e] = k;
					ub[k.e] = ub[j] + k.w;
					if (!inq[k.e]) {
						inq[k.e] = true;
						if(++c[k.e]>n)
							return false;
						if(sz(q) && ub[k.e]<ub[q.front()])
							q.pushf(k.e);
						else
							q.pushb(k.e);
					}
				}
			}
		}
		
		return q.empty();
	}

	Arr<Edge> cons_path(const Arr<T>& d, const Arr<Edge>& p, int dest){
		Arr<Edge> ret;
		while(p[dest].s!=-1){
			ret.pushb(g[p[dest].s][p[dest].ei]);
			dest=p[dest].s;
		}
		return ret;
	}

	Arr<Edge> mst_prim() {
		Arr<Edge> ret;
		Arr<bool> vis(n);
		PQ<Edge, Arr<Edge>, greater<Edge>> q;
		for(auto i:g[0])
			q.push(i);
		vis[0]=true;
		while (sz(q)) {
			auto c = q.top();
			q.pop();

			if (vis[c.e])
				continue;
			vis[c.e] = true;

			ret.pushb(c);
			for (auto &i : g[c.e]) {
				if (!vis[i.e]) {
					q.push(i);
				}
			}
		}
		return ret;
	}

	Arr<Edge> mst_kruskal() {
		Arr<Edge> e;
		for (auto &i : g)
			for (auto &j : i)
				e.pushb(j);
		sort(all(e));

		UF uf(n);
		Arr<Edge> ret;
		for (auto &i : e) {
			if (uf.find(i.s) != uf.find(i.e)) {
				uf.uni(i.s, i.e);
				ret.pushb(i);
			}
		}
		return ret;
	}

protected:
	virtual bool valid_spfa_edge(const Edge& w) const { return true; }
};