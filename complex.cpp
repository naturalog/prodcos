#include <mpc.h>
#include <iostream>
#include <string>
#include <vector>
#include <mpfr.h>
using namespace std;

mpfr_prec_t prec = 4096;

//auto getnums() 
int main() {
	string s;
	auto r = new mpc_t[4096];
	int sz = 0;
	mpc_t pi, ay, ipi, zero, one;
	mpfr_t eps;
	mpc_init2(pi, prec); mpfr_init2(eps, prec); mpc_init2(ay, prec); mpc_init2(ipi, prec); mpc_init2(zero, prec); mpc_init2(one, prec);
	mpc_set_si(ay, -1, MPC_RNDNZ); mpc_set_si(one, 1, MPC_RNDNZ); mpc_set_si(zero, 0, MPC_RNDNZ); mpfr_set_si(eps, 2, MPFR_RNDZ);
	mpc_acos(pi, ay, MPC_RNDNZ); mpc_sqrt(ay, ay, MPC_RNDNZ); mpc_mul(ipi, pi, ay, MPC_RNDNZ);
//	cout << mpc_get_str(10, 0, ipi, MPC_RNDNZ);
	while (cin >> s) {
		auto& t = r[sz];
		mpc_init2(t, prec);
		mpc_set_str(t, s.c_str(), 10, MPC_RNDNZ);
//		mpc_mul(r[sz], r[sz], ay, MPC_RNDNZ);
//		mpc_exp(r[sz], r[sz], MPC_RNDNZ);
		++sz;
	}
	mpfr_pow_si(eps, eps, -14, MPFR_RNDZ);
//	for (int n = 0; n < sz; ++n)
//		cout << mpc_get_str(10, 0, r[n], MPC_RNDNZ) << endl;

	mpc_t x, tt;
	mpfr_t fr, p, sum, t;
	mpc_init2(x, prec); mpfr_init2(fr, prec); mpc_init2(tt, prec); mpfr_init2(sum, prec); mpfr_init2(p, prec); mpfr_init2(t, prec);
	mpfr_set_si(sum, 0, MPFR_RNDZ);
	int it = 0;
	for (mpfr_set_si(t, -1, MPFR_RNDZ); mpfr_cmp_si(t, 1) < 0; mpfr_add(t, t, eps, MPFR_RNDZ)) {
		mpfr_set_ui(p, 1, MPFR_RNDZ);
		mpfr_mul(p, p, eps, MPFR_RNDZ);
		mpc_set_fr(tt, t, MPC_RNDNZ);
		for (int n = 0; n < sz; ++n) {
//			mpc_pow(x, r[n], tt, MPC_RNDNZ);
			mpc_mul(x, r[n], pi, MPFR_RNDZ);
			mpc_mul_fr(x, x, t, MPFR_RNDZ);
			mpc_cos(x, x, MPFR_RNDZ);
			mpc_real(fr, x, MPFR_RNDZ);
			mpfr_mul(p, p, fr, MPFR_RNDZ);
		}
		mpfr_add(sum, sum, p, MPFR_RNDZ);
		if ((++it)%100== 0)
			mpfr_out_str(stdout, 10, 0, sum, MPFR_RNDZ), cout << endl;
	}
	mpfr_out_str(stdout, 10, 0, sum, MPFR_RNDZ), cout << endl;
	
	return 0;
}
