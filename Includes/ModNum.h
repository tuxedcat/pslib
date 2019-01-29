#pragma once
#include "NumberTheory.h"

class NoModInv {};

//Do not use when Rabin Karp hashing(too weak, instead use ull).
struct ModNum {
	ModNum(i64 n=0) :n((n%mod+mod)%mod){}
	inline i64 val()const { return n; }

	inline ModNum operator - () const { return {-n}; }
	inline ModNum operator + (const ModNum& b)const { return n + b.val(); }
	inline ModNum operator - (const ModNum& b)const { return n - b.val() + mod; }
	inline ModNum operator * (const ModNum& b)const { return n * b.val(); }
	inline ModNum operator / (const ModNum& b)const { return *this * inv(b); }
	inline ModNum operator+= (const ModNum& b) { return *this = *this + b; }
	inline ModNum operator-= (const ModNum& b) { return *this = *this - b; }
	inline ModNum operator*= (const ModNum& b) { return *this = *this * b; }
	inline ModNum operator/= (const ModNum& b) { return *this = *this / b; }

	inline ModNum& operator++ () { *this += 1ll; return *this; }
	inline ModNum& operator-- () { *this -= 1ll; return *this; }
	inline ModNum operator++(int) { auto ret = *this; ++*this; return ret; }
	inline ModNum operator--(int) { auto ret = *this; --*this; return ret; }

	inline bool operator==(const ModNum& r) const { return n == r.n; }
	inline bool operator!=(const ModNum& r) const { return !(*this == r); }
	inline bool operator<(const ModNum& r) const { return n < r.n; }
	inline bool operator<=(const ModNum& r) const { return n <= r.n; }
	inline bool operator>(const ModNum& r) const { return n > r.n; }
	inline bool operator>=(const ModNum& r) const { return n >= r.n; }

	static inline ModNum zero(){ return 0; }
	static inline ModNum one(){ return 1; }
	static inline ModNum inf(){ return -1; }
private:
	i64 n;

	inline ModNum inv(const ModNum &b)const {
		auto res = xgcd(b.val(), -mod);
		if (1 % res.g)
			throw NoModInv();
		res.x *= 1 / res.g;
		while (res.x < 0)
			res.x += -mod / res.g;
		return res.x;
	}
};

ostream& operator<<(ostream& s, const ModNum& n) { return s << n.val(); }