#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <ostream>
#include <stdio.h>
#include <string>

using namespace std;



#define LIM 1234

template <int BASE = 10000>
//Tính cộng Nhân số lớn
struct bignum {
	int a[2309];
	int n;
	int& operator [] (int i){ return a[i]; }
	const int operator [] (int i) const { return a[i]; }
	void resize(int N){ for (int i = n; i<N; i++) a[i] = 0; n = N; }
	void trim()
	{ while ((n>1 && a[n - 1] == 0) || n>LIM) n--; }

	void normalize(){ for (int i = 0; i<n; i++) { a[i + 1] += a[i] / BASE; a[i] %= BASE; } trim(); }
	bignum(int x = 0) { a[0] = x; n = 1; }

	void operator = (int x);
	void operator = (const bignum &A);
	void operator += (const bignum &A);
	void operator *= (int k);
	void operator *= (const bignum &A);
	string toString() const;
	bignum <10000> toBase10();
};

template <int BASE> void bignum<BASE>::
operator = (int x){ a[0] = x; n = 1; }
template <int BASE> void bignum<BASE>::
operator = (const bignum &A){ for (int i = 0; i<A.n; i++) a[i] = A[i]; n = A.n; }

template <int BASE> void bignum<BASE>::
operator += (const bignum &A)
{
	int k;
	if (n > A.n)
		k = n;
	else
		k = A.n;
	resize( k + 1);
	for (int i = 0; i<A.n; i++) a[i] += A[i];
	normalize();
}

template <int BASE> void bignum<BASE>::
operator *= (int k){
	resize(n + 1);
	for (int i = 0; i<n; i++) a[i] *= k;
	normalize();
}

template <int BASE> bignum<BASE>
	operator * (const bignum<BASE> &A, const bignum<BASE> &B){
		bignum<BASE> R = 0;
		int i, j;
		R.resize(A.n + B.n);
		for (i = 0; i<A.n; i++)
		for (j = 0; j<B.n; j++)
			R[i + j] += A[i] * B[j];
		R.normalize();
		return R;
	}

	template <int BASE> void bignum<BASE>::
		operator *= (const bignum<BASE> &A){
			*this = (*this) * A;
		}

	template <int BASE> string bignum<BASE>::
		toString() const{
			char s[23];
			string r = "";
			sprintf(s, "%d", a[n - 1]);
			r += s;
			for (int i = n - 2; i >= 0; i--){ sprintf(s, "%04d", a[i]); r += s; }
			return r;
		}

	template <int BASE> bignum<10000> bignum<BASE>::
		toBase10(){
			bignum<10000> R = 0;
			for (int i = n - 1; i >= 0; i--)
			{
				R *= BASE; R += a[i];
			}
			return R;
		}

#undef LIM