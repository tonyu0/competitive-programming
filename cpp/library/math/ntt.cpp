#include <algorithm>
#include <iostream>
#include <vector>

std::vector<long long> modfft(std::vector<long long> A, long long mod, int root,
                              bool inverse = false) {
  int n = A.size(), mask = n - 1;
  std::vector<long long> tmp(n);
  for (int i = n >> 1; i >= 1; i >>= 1) {
    long long zeta = modpow(root, (mod - 1) / n * i, mod);
    if (inverse) zeta = modinv(zeta, mod);
    long long powzeta = 1;
    for (int j = 0; j < n; j += i) {
      for (int k = 0; k < i; ++k)
        tmp[j | k] =
          (A[((j << 1) | k) & mask] + powzeta * A[((j << 1) | i | k) & mask]) %
          mod;
      powzeta = powzeta * zeta % mod;
    }
    swap(A, tmp);
  }

  if (inverse) {
    long long invn = modinv(n, mod);
    for (int i = 0; i < n; ++i) (A[i] *= invn) %= mod;
  }
  return A;
}

std::vector<long long> conv(std::vector<long long> A, std::vector<long long> B,
                            long long mod = 0x49000001, int root = 3) {
  int siz = A.size() + B.size() - 1, n = 1;
  while (n < siz) n <<= 1;
  A.resize(n), B.resize(n);
  A = modfft(A, mod, root), B = modfft(B, mod, root);
  for (int i = 0; i < n; ++i) (A[i] *= B[i]) %= mod;
  A = modfft(A, mod, root, true);
  return A;
}