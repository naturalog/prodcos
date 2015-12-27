#include <iostream>
#include <cstdlib>
#include <ctime>
#include <mpreal.h>
using namespace std;
using namespace mpfr;
/*
Generates pseudo-random and pseudo-hard instances of partition problem. It simply
sums the alternating sum of random numbers, which determines the last number.
cmdline arg: num of nums
*/

int main(int, char **argv) {
	int sz = atoi(argv[1]);
	mpreal::set_default_prec(2 * sz);
	random(time(0));
	srand(time(0));
	mpreal M = pow(mpreal(2), sz);
	cout.precision(sz*2);
	mpreal x, s = 0;
	cout << (8+sz) << endl;
	for (int n = 0; n < sz-1; ++n) {
//		cerr << 
		(x = ceil(M*mpfr::random()));
		//<< '\t';
		s += pow(-1,rand())*x;
		cout << x << endl;
//		cerr << s << endl;
	}
	s = mpfr::fabs(s);
	cout << s << endl;
//	cerr << s << endl;
}
