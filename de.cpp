// This is a #PART solver based on Double Exponential numerical integration.
// Usage: de reads from stdin. 
// first line is "prec", number of bits to hold the numbers all alongthe run.
// if prec<0, the program simply prints all results from prec=2 to -prec
// next lines contain one number each, the
// partition problem's input.
// see file 'in' for example, it should integrate to 1/16, as maxima:
// (%i1) 16*integrate(cos(2*x*%pi)*cos(3*x*%pi)*cos(6*x*%pi)*cos(9*x*%pi)*cos(12*x*%pi)*cos(20*x*%pi),x,-1,1);
// (%o1)                                 1
// update: now the output is in integers (simply num of partitions), so "de < in" should output 2

#include <mpreal.h> // mpfrc++
#include <iostream>
#include <cstdlib>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using namespace mpfr;
mpreal sq(const mpreal& x) { return x*x; }

int main(int argc, char** argv) {
	long prec;
//	cin >> prec;
//	cin >> iters;
	vector<unsigned long> in;
	unsigned long r, mx = 0;
	while (cin >> r) { in.push_back(r); mx = std::max(r, mx); }
	mx = ceil(log2(mx));
	mx = 13 + std::max(mx, in.size());
	mx += log2(mx);
	mx *= 16;
	auto go = [in](size_t prec) {
		size_t iters;
		mpreal::set_default_prec(prec);
		iters = prec;
		cout.precision(prec);

		mpreal r;
		const mpreal pi = acos(mpreal(-1)), pi2 = pi/mpreal(2);
	//	for (auto r : in) cout << r << endl;
		auto f=[in,pi](mpreal t){mpreal r=1; for(auto x:in)r*=cos(x*pi*t); return r;};
		auto w=[pi2](mpreal t){return tanh(pi2*sinh(t));};
		auto dw=[pi2](mpreal t){return pi2*cosh(t)*sq(sech(pi2*sinh(t)));};
		auto g=[f,w,dw](mpreal t) {return f(w(t))*dw(t);};

		mpreal sum = 0, y, t, c = 0, h;
		int N = 2 * iters + 1, sz = in.size();
		if (prec < sz) { cout << "cant prodcos " << sz << " numbers with prec " << prec << ", should be at least equal" << endl; exit(0); }
		h = mpreal(1)/mpreal(iters);
		mpreal max = pow(mpreal(2), sz);
		for (int m = -N; m != N; ++m) {
			y = /*max**/h*g(h*mpreal(m)) - c; // Kahan summation. Beware of compiler optimizations! Don't trust my makefile!
			t = sum + y;
			c = (t - sum) - y;
			sum = t;
		//	if (!(m%1000)) cout << m << '/' << N << ' ' << sum << endl;
		}
		cout << "prec: " << prec << " #PART: " << float(sum) << " 2^-n = " << std::pow(2., -(int)in.size()) << endl;
	};
	go(mx);
//	if (prec>0) go(mx);
//	else for (long p = 8; p <= -prec; ++p) go(p);
	return 0;
}
