#pragma once
#include "core.h"
#include "math/struct/monoid.h"

//example https://www.acmicpc.net/source/59898625
template<Monoid Q>
struct SegDyn{
	using T=decltype(Q::id());
	const static int xlo=-inf<i32>();
	const static int xhi=inf<i32>();
	T v=Q::id();
	SegDyn *l{},*r{};
	~SegDyn(){release();}
	void release(){if(l)delete l,l=0; if(r)delete r,r=0;}

	void join(SegDyn* o){
		if(!o)return;
		v=Q::f(v,o->v);
		if(l)
			l->join(o->l);
		else if(o->l)
			l=o->l, o->l=nullptr;
		if(r)
			r->join(o->r);
		else if(o->r)
			r=o->r, o->r=nullptr;
	}

	T upd(int i, T x, int cs=xlo, int ce=xhi){
		if(ce<=i or i+1<=cs)return v;
		if(i<=cs and ce<=i+1)return v=x;
		int cm=(cs+ce)/2;
		if(!l)l=new SegDyn;
		if(!r)r=new SegDyn;
		return v=Q::f(l->upd(i,x,cs,cm),r->upd(i,x,cm,ce));
	}
	T q(int s,int e, int cs=xlo, int ce=xhi){
		if(ce<=s or e<=cs)return Q::id();
		if(s<=cs and ce<=e) return v;
		int cm=(cs+ce)/2;
		if(!l)l=new SegDyn;
		if(!r)r=new SegDyn;
		return Q::f(l->q(s,e,cs,cm),r->q(s,e,cm,ce));
	}
	//pred(acc[s,i),i)를 만족하는 최소i
	int prefix_search(auto pred,int s=xlo){T acc=Q::id();return prefix_search(xlo,xhi,s,pred,acc);}
	//pred(acc[i,e),i)를 만족하는 최대i
	int suffix_search(auto pred,int e=xhi){T acc=Q::id();return suffix_search(xlo,xhi,e,pred,acc);}
	//kth: boj2243
	//mex: 폴리곤_숲게임_lib.cpp
	//nearest_greaters: https://codeforces.com/contest/1691/submission/159109187
private:
	int prefix_search(int cs,int ce,int s,auto pred,T& acc){
		if(!l)l=new SegDyn;
		if(!r)r=new SegDyn;
		int cm=(cs+ce)/2,ret=inf<int>();
		if(ce<=s)
			;
		else if(cs<s)
			assmin(ret,l->prefix_search(cs,cm,s,pred,acc))||assmin(ret,r->prefix_search(cm,ce,s,pred,acc));
		else{
			if(pred(acc,cs)){acc=Q::f(acc,v);return cs;}
			if(!pred(Q::f(acc,v),ce)){acc=Q::f(acc,v);return inf<int>();}
			if(ce-cs==1)return ce;
			assmin(ret,l->prefix_search(cs,cm,s,pred,acc))||assmin(ret,r->prefix_search(cm,ce,s,pred,acc));
		}
		return ret;
	}
	//https://codeforces.com/blog/entry/83883
	int suffix_search(int cs,int ce,int e,auto pred,T& acc){
		int cm=(cs+ce)/2,ret=-1;
		if(e<=cs)
			;
		else if(e<ce)
			assmax(ret,r->suffix_search(cm,ce,e,pred,acc))||assmax(ret,l->suffix_search(cs,cm,e,pred,acc));
		else{
			if(pred(acc,ce)){acc=Q::f(acc,v);return ce;}
			if(!pred(Q::f(v,acc),cs)){acc=Q::f(v,acc);return -1;}
			if(ce-cs==1)return cs;
			assmax(ret,r->suffix_search(cm,ce,e,pred,acc))||assmax(ret,l->suffix_search(cs,cm,e,pred,acc));
		}
		return ret;
	}
};
