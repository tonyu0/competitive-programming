#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_map>
using namespace std;
using ll = long long;

// f^x ≡ y mod pを満たすxを√pの分割統治で求める考え方だが、
// BSGSは仕組み的には有限サイズの巡回群に使える。冪乗 mod
// pは位数p-1の巡回群をなすので使える。 巡回群上の分割統治である。
// x = m * i + jと考えると、f^j = y*f^(-mi) mod
// pと、iとjを分離できるので別々に計算して、後で突き合わせる
// m=√位数のグループに分ける⇨冪乗x=i*m+jと考えると
// iはグループ間、jはグループ内の移動で、前者をGiant、後者をBaby。
// どちらかをhashmapにいれ、どちらかをhashmapから検索して見つかったら答え。BSGS自体はO(√p）だが検索次第で最終的に色々
// jを先に調べてiを小さい順に調べると最小のxが求まる

int64_t mod_pow(int64_t n, int64_t e, int64_t p) {
  int64_t res = 1;
  while (e > 0) {
    if (e & 1) res = res * n % p;
    n = n * n % p;
    e >>= 1;
  }
  return res;
}

// g^x % p = hを満たすxを求める。
// x = i*m + j (m = √pとすればiはm以下、jはm未満)として上式を変形すると
// g^(i*m+j) ≡ h (mod p) pは素数なので両辺にg^((-m)*i)をかけて
// g^j ≡ h(g^(-m))^i
// baby stepでj, giant stepで(g^(-m))^iを総当たり
int64_t babystep_giantstep(int64_t g, int64_t h, int64_t p) {
  size_t m = (size_t)sqrt(p) + 1;
  unordered_map<int64_t, int64_t> table;

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
// https://atcoder.jp/contests/abc270/tasks/abc270_g
int main() {
  // まずA,Bは定数なので操作が位数p以下の巡回群になってそう
  // f^x(s) = g mod p
  // となる最小のx
  // f(x) = a * x + b
  // f(0) = 1 * s + 0
  // x = m*i + jとすると
  // f^(i*m)(s) = f^(-j)(g) mod p
  // これらを満たす最小のi,jを求める
  // 0<=i<m, 0<=j<m
  // f^mとf^(-1)がもとまれば、i,jを走査できる
  // f^(-1)(x) = x / a - b / a
  // f^mは普通に求める. x_{i+1} = x_i * a + bにx_i=x_{i-1} * ca + cbを代入して
  // f^2の係数を出す感じ...を繰り返す
  int t;
  cin >> t;
  while (t--) {
    ll p, a, b, s, g;
    cin >> p >> a >> b >> s >> g;
    if (s == g)
      cout << 0 << '\n';
    else if (a == 0) {
      if (b == g)
        cout << 1 << '\n';
      else
        cout << -1 << '\n';
    } else {
      ll m = sqrt(p);
      ll ma = 1, mb = 0; // m回適用した時の係数
      for (int i = 0; i < m; ++i) {
        // X_{i+1} = X_i * a + b
        // a -> a^2, b -> a * b + b
        mb = (a * mb + b) % p;
        ma = ma * a % p;
      }
      ll ia = mod_pow(a, p - 2, p);
      ll ib = ((-b * ia) % p + p) % p;
      // f^(-1) = ia * x + ib

      unordered_map<int64_t, int64_t> table;
      for (ll j = 0; j <= m; ++j) {
        if (table.find(g) == table.end()) table[g] = j;
        g = (g * ia + ib) % p;
      }
      ll ans = -1;
      for (ll i = 0; i <= m; ++i) {
        auto itr = table.find(s);
        if (itr != table.end()) {
          ans = m * i + itr->second;
          break;
        }
        s = (s * ma + mb) % p;
      }
      cout << ans << '\n';
    }
  }
}

// https://atcoder.jp/contests/arc042/tasks/arc042_d
int ARC042D() {
  ll X, P, A, B;
  cin >> X >> P >> A >> B;
  // X^i = Y(mod P)を考える。
  // iを全探索すると間に合わないのでYを固定して離散対数問題を解く。
  // Yは周期P-1なので、Pがでかいと結局間に合わないので、工夫する。
  if (B - A + 1 > P - 1) {
    cout << 1;
  } else if (B - A <
             100000) // 試すiが小さいとBSGSがTLEするのでここは愚直にやる。
  {
    int ans = P;
    // X^A (mod P)
    int t = mod_pow(X, A, P);
    for (int i = 0; i < B - A + 1; ++i) {
      ans = min(ans, t);
      t = t * X % P;
    }
    cout << ans;
  } else {
    A %= P - 1;
    B %= P - 1;
    // BSGSを使う。
    // X^i = h(mod P)
    for (int h = 0; h < P; ++h) {
      int res = babystep_giantstep(X, h, P);
      if (A <= res && res <= B) {
        cout << h;
        break;
      }
    }
  }
  cout << '\n';
  return 0;
}