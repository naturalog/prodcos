// This is a #PART solver based on Double Exponential numerical integration.
// Usage: de reads from stdin. 
// see file 'in' for example, it should integrate to 1/16, as maxima:
// (%i1) 16*integrate(cos(2*x*%pi)*cos(3*x*%pi)*cos(6*x*%pi)*cos(9*x*%pi)*cos(12*x*%pi)*cos(20*x*%pi),x,-1,1);
// (%o1)                                 1

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

vector<unsigned long> in;
mpreal pi, pi2;

mpreal f(mpreal t) { mpreal r=1; for(auto x:in)r*=cos(x*pi*t); return r; }
mpreal w(mpreal t) { return tanh(pi2*sinh(t)); }
mpreal dw(mpreal t){ return pi2*cosh(t)*sq(sech(pi2*sinh(t))); }
mpreal g(mpreal t) { return f(w(t))*dw(t); }

int main() {
	unsigned long r, prec = 0, iters;
	while (cin >> r) { in.push_back(r); prec = std::max(r, prec); }
	prec = ceil(log2(prec));
	prec = 1 + std::max(prec, in.size());
	prec += log2(prec);
	prec *= 3;
	mpreal::set_default_prec(prec);
	pi = acos(mpreal(-1)), pi2 = pi/mpreal(2);
	iters = prec * 16;
	cout.precision(prec);

	mpreal sum = 0, y, t, c = 0, h;
	int N = 2 * iters + 1, sz = in.size();
	h = mpreal(1)/mpreal(iters);
	mpreal max = pow(mpreal(2), sz);
	for (int m = -N; m != N; ++m) {
		y = /*max**/h*g(h*mpreal(m)) - c; // Kahan summation. Beware of compiler optimizations! Don't trust my makefile!
		t = sum + y;
		c = (t - sum) - y;
		sum = t;
	}
	cout << "prec: " << prec << " #PART: " << float(sum) << " 2^-n = " << std::pow(2., -(int)in.size()) << endl;
	return 0;
}
