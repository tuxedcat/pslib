#pragma once
#include "core.h"
#include "math/struct/monoid.h"

//SplayBST는 splay+a(자료구조)로 변환가능할듯.
//NOTE: Upd없어도 삭제 후 삽입하면 됨
//NOTE: using open range (lb,ub), not half open range [lb,ub), 2 mock nodes
//ex: https://atcoder.jp/contests/jsc2021/tasks/jsc2021_f
template<Monoid Q, Monoid U>
struct SplayBST{
	using T=decltype(Q::id());
	struct N;
	SplayBST(): root(new N(inf<T>()*2)){root->setL(new N(-inf<T>()*2)); root->renew();}
	~SplayBST(){delete root;}

	int size()const{return root->s-2;}//remove two mock node
	void ins(T v){
		splay(root->ub(v));
		N* node=new N(v);
		node->setL(root->l);
		root->setL(node);
		
		node->renew();
		root->renew();

		splay(node);
	}
	void del(T v){
		N* x=interval(root->lb(v),root->ub(v));
		
		splay(x);
		N *xl=x->l, *xr=x->r;
		x->setL(0);
		x->setR(0);
		delete x;

		xl->p=0; x->l=0;
		splay(xl);

		splay(xr->begin());
		root->setL(xl);

		root->renew();
	}
	N* q(T s, T e){ return interval(root->lb(s),root->ub(e)); }

	N* splay(N *x){
		while(x->p)
			x->step_splay();
		return root=x;
	}
	N* interval(N* s, N* e){
		splay(s);
		N* root_save=root;
		root->r->p=0;
		root=root->r;
		splay(e);
		root->p=root_save;
		root_save->r=root;
		root=root_save;
		return root->r->l;
	}

	struct N{
		N *l=0,*r=0,*p=0;
		int s=1;
		T v=Q::id(),a=Q::id();
		N(T v):v(v){}
		~N(){
			if(l) delete l;
			if(r) delete r;
		}
		void setL(N* x){l=x; if(x)x->p=this;}
		void setR(N* x){r=x; if(x)x->p=this;}
		void step_splay(){
			N *p=this->p,*pp=p->p;
			if(!p) return;
			if(pp) (this==p->l ^ p==pp->l ? this : p)->rot();
			this->rot();
		}
		void rot(){
			if(!this->p) return;
			N *p=this->p,*pp=p->p;
			if(pp){
				if(p==pp->l) pp->setL(this);
				else pp->setR(this);
			}else this->p=0;
			if(this==p->l) p->setL(r),this->setR(p);
			else p->setR(l),this->setL(p);
			if(pp)pp->renew();
			p->renew();
			this->renew();
		}
		void renew(){
			a=Q::f(Q::f(l?l->a:Q::id(),v),r?r->a:Q::id());
			s=(l?l->s:0)+(r?r->s:0)+1;
		}
		N* lb(T x, N* z=0){
			if(l and x<=v) return l->lb(x,z);
			if(r and x>v) return r->lb(x,this);
			return x>v?this:z;
		}
		N* ub(T x, N* z=0){
			if(l and x<v) return l->ub(x,this);
			if(r and x>=v) return r->ub(x,z);
			return x<v?this:z;
		}
		N* begin(){return l?l->begin():this;}
		N* end(){return r?r->end():this;}
		void iter(auto f){
			if(l)l->iter(f);
			f(v);
			if(r)r->iter(f);
		}
	} *root;
};
