// This is a #PART solver based on Double Exponential numerical integration.
// Usage: de reads from stdin. 
// first line is "prec", number of bits to hold the numbers all alongthe run.
// next lines contain one number each, the
// partition problem's input.
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

int main(int argc, char** argv) {
	size_t prec, iters;
	cin >> prec;
//	cin >> iters;
	mpreal::set_default_prec(prec);
	iters = prec;
	cout.precision(prec);

	mpreal r;
	const mpreal pi = acos(mpreal(-1)), pi2 = pi/mpreal(2);
	vector<mpreal> in;
	while (cin >> r) in.push_back(r);
	for (auto r : in) cout << r << endl;
	auto f=[in,pi](mpreal t){mpreal r=1; for(auto x:in)r*=cos(x*pi*t); return r;};
	auto w=[pi2](mpreal t){return tanh(pi2*sinh(t));};
	auto dw=[pi2](mpreal t){return pi2*cosh(t)*sqr(sech(pi2*sinh(t)));};
	auto g=[f,w,dw](mpreal t) {return f(w(t))*dw(t);};

	mpreal sum = 0, y, t, c = 0, h;
	int N = 2 * iters + 1;
	h = mpreal(1)/mpreal(iters);
	for (int m = -N; m != N; ++m) {
		y = h*g(m*h) - c; // Kahan summation. Beware of compiler optimizations! Don't trust my makefile!
		t = sum + y;
		c = (t - sum) - y;
		sum = t;
		if (!(m%1000)) cout << m << '/' << N << ' ' << sum << endl;
	}
	cout << (sum/2) << endl;
}
