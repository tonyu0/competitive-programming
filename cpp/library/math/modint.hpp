#include <vector>

template <std::int64_t Mod>
class modint {
public:
  using i64 = std::int64_t;

private:
  i64 v;
  static constexpr i64 normalize(i64 x) noexcept {
    x %= Mod;
    if (x < 0) x += Mod;
    return x;
  }

public:
  constexpr modint() noexcept : v(0) {}
  constexpr modint(i64 x) noexcept : v(normalize(x)) {}
  [[nodiscard]] static constexpr i64 mod() noexcept { return Mod; }
  [[nodiscard]] constexpr i64 val() const noexcept { return v; }

  /* operators */
  [[nodiscard]] constexpr modint operator+(const modint &rhs) const noexcept {
    return modint(*this) += rhs;
  }
  [[nodiscard]] constexpr modint operator-(const modint &rhs) const noexcept {
    return modint(*this) -= rhs;
  }
  [[nodiscard]] constexpr modint operator*(const modint &rhs) const noexcept {
    return modint(*this) *= rhs;
  }
  [[nodiscard]] constexpr modint operator/(const modint &rhs) const noexcept {
    return modint(*this) /= rhs;
  }
  constexpr modint &operator+=(const modint &rhs) noexcept {
    v += rhs.v;
    if (v >= Mod) v -= Mod;
    return *this;
  }
  constexpr modint &operator-=(const modint &rhs) noexcept {
    v -= rhs.v;
    if (v < 0) v += Mod;
    return *this;
  }
  constexpr modint &operator*=(const modint &rhs) noexcept {
    v = (v * rhs.v) % Mod;
    return *this;
  }
  constexpr modint &operator/=(const modint &rhs) noexcept {
    return *this *= rhs.inv();
  }

  /* comparison */
  [[nodiscard]] constexpr bool operator==(const modint &rhs) const noexcept {
    return v == rhs.v;
  }
  [[nodiscard]] constexpr bool operator!=(const modint &rhs) const noexcept {
    return v != rhs.v;
  }

  /* inverse (extgcd) */
  [[nodiscard]] constexpr modint inv() const noexcept {
    i64 a = v, b = Mod;
    i64 s = 1, t = 0;
    while (b > 0) {
      i64 q = a / b;
      a -= q * b;
      swap(a, b);
      s -= q * t;
      swap(s, t);
    }
    return modint(s);
  }

  /* power */
  [[nodiscard]] constexpr modint pow(i64 exp) const noexcept {
    modint base = *this;
    modint res = 1;
    while (exp > 0) {
      if (exp & 1) res *= base;
      base *= base;
      exp >>= 1;
    }
    return res;
  }

  /* conversion */
  explicit constexpr operator i64() const noexcept { return v; }

  /* IO */
  friend std::ostream &operator<<(std::ostream &os, const modint &m) {
    return os << m.v;
  }
  friend std::istream &operator>>(std::istream &is, modint &m) {
    i64 t;
    is >> t;
    m = modint(t);
    return is;
  }
};

template <long long mod = 1000000007>
class combination {
  using mint = modint<mod>;

public:
  constexpr combination(size_t n) : fac(n + 1), inv(n + 1), inv_fac(n + 1) {
    fac[0] = 1;
    inv_fac[0] = 1;
    inv[1] = 1;
    // i * inv[i] = 1 mod p.
    // p = p / i * i + p % i
    // => p / i * i + p % i = 0 mod p
    // => (p / i * -inv[p % i]) * i = 1 mod p
    for (size_t i = 2; i <= n; ++i) { inv[i] -= inv[mod % i] * mint(mod / i); }
    for (size_t i = 1; i <= n; ++i) {
      fac[i] = fac[i - 1] * mint(i);
      inv_fac[i] = inv_fac[i - 1] * inv[i];
    }
  }

  mint operator()(size_t n, size_t k) {
    if (n < k) { return 0; }
    return fac[n] * inv_fac[n - k] * inv_fac[k];
  }
  mint factrial(size_t n) { return fac[n]; }

private:
  std::vector<mint> fac, inv, inv_fac;
};