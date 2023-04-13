#include <chrono>
#include <gmp.h>
#include <iostream>

void run(uint times);

int main() {
  int sel = 0;
  do {
    std::cout << "> ";
    std::cin >> sel;
    run(sel);
  } while (sel);
  return 0;
}

void run(uint times) {
  mpf_set_default_prec(1024);
  mpf_t x, y, z, c;
  mpz_t i;

  mpf_inits(x, y, z, c, NULL);
  mpz_inits(i, NULL);

  gmp_randstate_t state;
  gmp_randinit_mt(state);
  gmp_randseed_ui(state,
                  std::chrono::system_clock::now().time_since_epoch().count());

  for (; mpz_cmp_ui(i, times) == -1; mpz_add_ui(i, i, 1)) {
    mpf_urandomb(x, state, mpf_get_default_prec());
    mpf_urandomb(y, state, mpf_get_default_prec());

    mpf_pow_ui(x, x, 2);
    mpf_pow_ui(y, y, 2);
    mpf_add(z, x, y);
    if (mpf_cmp_ui(z, 1) == -1 || mpf_cmp_ui(z, 1) == 0) {
      mpf_add_ui(c, c, 1);
    }
  }

  mpf_div_ui(c, c, times);
  mpf_mul_ui(c, c, 4);
  gmp_printf("%0.256Ff\n", c);

  gmp_randclear(state);
  mpf_clears(x, y, z, c, NULL);
  mpz_clears(i, NULL);
}