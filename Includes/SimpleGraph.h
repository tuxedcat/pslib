#pragma once
#include "DirectedGraph.h"

struct SimpleGraph: public DirectedGraph{
	SimpleGraph(int n=0):DirectedGraph(n){}

	void add_edge(int s, int e){ DirectedGraph::add_edge(s, e, false); }

	Arr<int> articul_points(){
		Arr<int> ord(n, -1), ret;
		int o=0;
		hfor(i, 0, n){
			if(ord[i] != -1)
				continue;
			dfs_ap(i, -1, o, ord, ret);
		}
		return ret;
	}

	Arr<pair<int,int>> bridges(){
		Arr<int> ord(n, -1);
		Arr<pair<int,int>> ret;
		int o=0;
		hfor(i, 0, n){
			if(ord[i] != -1)
				continue;
			dfs_bridge(i, -1, o, ord, ret);
		}
		return ret;
	}

	void bcc(){}
	
	void blossom(){}
	
private:
	int dfs_ap(int v, int p, int& o, Arr<int>& ord, Arr<int>& ans){
		int ret = ord[v]=o++;
		int subcnt=0;
		bool isAP = false;
		for(auto i: g[v]){
			if(ord[i.e] != -1){
				ret = min(ret, ord[i.e]);
				continue;
			}

			int res=dfs_ap(i.e, v, o, ord, ans);
			subcnt++;
			isAP |= res>=ord[v];
			ret = min(ret, res);
		}
		if(isAP && (p!=-1 || subcnt>1))
				ans.pushb(v);
		return ret;
	}
	int dfs_bridge(int v, int p, int& o, Arr<int>& ord, Arr<pair<int, int>>& ans){
		int ret = ord[v]=o++;
		bool conn = false;
		for(auto i: g[v]){
			if(ord[i.e] != -1){
				if(p!=-1)
					conn |= ord[i.e]<ord[p];
				ret = min(ret, ord[i.e]);
				continue;
			}

			int res=dfs_bridge(i.e, v, o, ord, ans);
			conn |= res<ord[v];
			ret = min(ret, res);
		}
		if(!conn && p!=-1)
				ans.pushb({min(v, p), max(v, p)});
		return ret;
	}
};