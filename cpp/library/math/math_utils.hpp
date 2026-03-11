#include <iostream>
#include <vector>

namespace math_utils {

int64_t mod_pow(int64_t n, int64_t e, int64_t p) {
  int64_t res = 1;
  while (e > 0) {
    if (e & 1) res = res * n % p;
    n = n * n % p;
    e >>= 1;
  }
  return res;
}

std::tuple<long long, long long, long long> ext_gcd(long long a, long long b) {
  if (b > 0) {
    auto [d, y, x] = ext_gcd(b, a % b);
    y -= a / b * x;
    return {d, x, y};
  }
  return {a, 1, 0};
}

std::pair<long long, long long> linear_congruence(
  const std::vector<long long>& B, const std::vector<long long>& M) {
  // 各合同式を解きながら更新していく。
  long long x = 0, lcm = 1;
  for (int i = 0; i < (int)B.size(); ++i) {
    auto [g, x, y] = ext_gcd(lcm, M[i]);
    // Mp ≡ d (mod m[i])
    // Mp - m[i]q = d
    // p is inv of M/d (mod. m[i]/d)
    // Mとm[i]は互いに素じゃなくても、b[i] - rがgcd(M, m[i])で割り切れれば良い。
    if ((B[i] - x) % g != 0) return std::make_pair(0, -1);
    long long tmp = (B[i] - x) / g * p % (M[i] / g);
    x += lcm * tmp;
    lcm *= M[i] / g;
  }
  return std::make_pair((x + lcm) % lcm, lcm);
}

// floor_sum(n, m, a, b) returns \sum_{x = 0} ^ {n - 1}[(a * x + b) / m]
long long floor_sum(long long n, long long m, long long a, long long b) {
  long long res = 0;
  // a = m * q + r
  // ->[(x *(m * q + r) + b) / m] = q * x +[(r * x + b) / m]
  // \sum_{x = 0 } ^ {n - 1 } q * x =[a / m] * n *(n - 1) / 2
  if (a >= m) {
    res += a / m * n * (n - 1) / 2;
    a %= m;
  }
  if (b >= m) {
    res += b / m * n;
    b %= m;
  }

  long long ymax = (a * (n - 1) + b) / m;
  if (ymax == 0) return res;
  if (b < m * ymax) {
    // b >= m * ymaxとなるようにbを調整。
    // floor_sumの2番目、4番目の引数は
    // while b < m* ymax:
    // b += a
    // res -= ymax
    long long diff = m * ymax - b;
    long long add_cnt = (diff + a - 1) / a;
    res -= add_cnt * ymax;
    b += add_cnt * a;
  }

  res += n * ymax + floor_sum(ymax, a, m, b - m * ymax);
  return res;
}

int next_combination(int comb) {
  int x = comb & -comb;
  // 最下位の1が連続している区間(0101110 -> 1001111)
  int y = comb + x;
  // 最下位の1が連続している区間の1つ上のビットを1にして、それ以下のビットを0
  return ((comb & ~y) / x >> 1) | y;
  // 立ってるビットが1減るまでxを右シフト、それをyとorする
}

int64_t babystep_giantstep(int64_t g, int64_t h, int64_t p) {
  size_t m = (size_t)sqrt(p) + 1;
  std::unordered_map<int64_t, int64_t> table;

  // baby step
  // g^i % p(i = 0 ~ √p)を求める
  int64_t baby = 1;
  for (size_t j = 0; j < m; ++j) {
    table[baby] = j;
    baby = (baby * g) % p;
  }

  // g^(-m)は、gのべき乗modpはp-1周期なので、g^(p-1-m)を求めれば良い
  // giant step
  int64_t gm = mod_pow(g, p - 1 - m, p);
  int64_t giant = h;
  for (size_t i = 0; i < m; ++i) {
    auto itr = table.find(giant);
    if (itr != table.end()) return i * m + itr->second;
    giant = (giant * gm) % p;
  }
  return -1;
}

template <typename T>
T lagrange_interpolation(std::vector<T>& x, std::vector<T>& y, T t) {
  T sum = 0;
  int n = (int)x.size();

  for (int i = 0; i < n; i++) {
    T num = y[i], denom = 1;
    for (int j = 0; j < n; j++) {
      if (i == j) continue;
      num = num * (t - x[j]);
      denom = denom * (x[i] - x[j]);
    }
    T prod = num / denom;
    sum += prod;
  }

  return sum;
}

}; // namespace math_utils
