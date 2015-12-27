// This is a #PART solver based on Double Exponential numerical integration.
// Usage: de reads from stdin. 
// see file 'in' for example, it should integrate to 1/16, as maxima:
// (%i1) 16*integrate(cos(2*x*%pi)*cos(3*x*%pi)*cos(6*x*%pi)*cos(9*x*%pi)*cos(12*x*%pi)*cos(20*x*%pi),x,-1,1);
// (%o1)                                 1

#include <mpreal.h> // mpfrc++
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace mpfr;

std::vector<mpreal> in;
mpreal pi, pi2;
size_t sz;

mpreal sq(const mpreal& x) { return x*x; }
mpreal f(mpreal t) { mpreal r=1; for (size_t n = 0; n < sz; ++n)r*=cos(in[n]*pi*t); return r; }
mpreal w(mpreal t) { return tanh(pi2*sinh(t)); }
mpreal dw(mpreal t){ return pi2*cosh(t)*sq(sech(pi2*sinh(t))); }
mpreal g(mpreal t) { return f(w(t))*dw(t); }

int main() {
	unsigned long iters, prec;
	std::cin >> prec; // first line is prec
	prec *= 8;
	mpreal::set_default_prec((int)prec);
	mpreal r;
	while (std::cin >> r) { in.push_back(r); prec = (int)max(ceil(log2(r)), prec); std::cout << r << std::endl; }
	sz = in.size();
//	prec = (int)max(prec, sz) + 1;
//	prec += log2(prec);
//	prec *= 16;
	std::cerr << "prec: " << prec << std::endl;
	for (size_t n = 0; n < in.size(); ++n) in[n] = mpreal((unsigned long)in[n], (int)prec);
	pi = acos(mpreal(-1)), pi2 = pi/mpreal(2);
	iters = (int)(prec * prec);
//	std::cout.precision(prec);

	mpreal sum = 0, y, t, c = 0, h;
	int N = 2 * iters + 1;
	h = mpreal(1)/mpreal(iters);
	mpreal max = pow(mpreal(2), sz);
	for (int m = -N; m != N; ++m) {
		y = /*max**/h*g(h*mpreal(m)) - c; // Kahan summation. Beware of compiler optimizations! Don't trust my makefile!
		t = sum + y;
		c = (t - sum) - y;
		sum = t;
	}
	std::cout << "prec: " << prec << " #PART (less than 1 supposed to be unpart): " << float((std::pow(2., (int)in.size()-2)) * sum) <</* " 2^(1-n) = " << std::pow(2., 1-(int)in.size()) <<*/ std::endl;
	std::cout << (exp(-mpreal(iters)) + (mpreal(1)+mpreal(1)/h)*exp(-exp(mpreal(iters)-1)/acos(-1))) << std::endl;
	return 0;
}
