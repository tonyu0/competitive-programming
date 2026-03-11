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

// a * x + b * y = gcd(a, b)を満たすx, yを取得
// 最終的に
// a0 = gcd(a, b), b0 = 0, x = 1, y = 0の状態を作り出す。
// そこから来た道を辿り、a0, b0からa, bを復元する過程でx, yを求めるイメージ。
long long extgcd(long long a, long long b, long long& x, long long& y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  long long g = extgcd(b, a % b, y, x);
  y -= (a / b) * x;
  return g;
}

std::tuple<long long, long long, long long> ext_gcd(long long a, long long b) {
  if (b > 0) {
    auto [d, y, x] = ext_gcd(b, a % b);
    y -= a / b * x;
    return {d, x, y};
  }
  return {a, 1, 0};
}

// 連立線形合同式を解く。拡張ユークリッドの誤除法を用いる。
// 解は無数にあるので、解全体を表す x ≡ b (mod m)のbとmのペアを返す。
// x ≡ b1 (mod m1), x ≡ b2 (mod m2), ...
// m1, m2 ...が互いに素なら、xが一意に定まる。
std::pair<long long, long long> linear_congruence(
  const std::vector<long long>& B, const std::vector<long long>& M) {
  // 各合同式を解きながら更新していく。
  long long x = 0, lcm = 1;
  for (int i = 0; i < (int)B.size(); ++i) {
    long long p, q;
    long long g = extgcd(lcm, M[i], p, q);
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

  // floor((a * x + b) / m) = yとなるxの範囲を考える。
  // ceil, floorは不等式で評価するとよい
  // 最小値xは
  // y <= (a * x + b) / mなので
  // my <= ax + b
  // my - b / a <= x
  // xは整数なので、最小値は左辺の切り上げ(ceil((m * y - b) / a))
  // 最小値x_iが分かると、iになる範囲はx_{i + 1 } - x_i
  // ymaxだけはn - x_ymax
  // (x_2 - x_1) * 1 +(x_3 - x_2) * 2 +... +(x_ymax - x_{ymax - 1}) *(ymax
  // - 1)
  // +(n - x_ymax) * ymax
  // 整理すると、(最後のn * ymaxにより、ymax個の塊にnをぶんぱい可能)
  // \sum_{i = 1 } ^ {ymax }(n - x_i)
  // これを崩してymax - 1までの小問題にできるか考える。
  // (ここでx_max = m * y_max - bと置くとうまくいくっぽいが、仕組みが分からん)
  // \sum_{i = 1 } ^ {ymax}(n - ceil(m * i - b) / a)の和の順番を逆にして
  // \sum_{i = 0 } ^ {ymax - 1}(n - ceil(m *(ymax - i) - b) / a)
  // (0 - ceil(x) = floor(0 - x) を使って)
  //  \sum_{i = 0 } ^ {ymax - 1 }(n + floor((b - m *(ymax - i)) / a)
  // n*ymax + \sum_{i = 0 } ^ {ymax - 1 } floor((m * i + b - m * ymax)/a)
  // 最初の式 : \sum_{i = 0 } ^ {n - 1 } floor((a * i + b) / a)と比較すると
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

// 説明: nに含まれるサイズkの部分集合を列挙する。
// 2の補数表現より-x == (~x) + 1なので、最下位ビットは x & -xで取れる。
// 部分集合を投げると次の部分集合を返してくれる関数
// bit全探索のビット数固定版とも言える
int next_combination(int comb) {
  int x = comb & -comb;
  // 最下位の1が連続している区間(0101110 -> 1001111)
  int y = comb + x;
  // 最下位の1が連続している区間の1つ上のビットを1にして、それ以下のビットを0
  return ((comb & ~y) / x >> 1) | y;
  // 立ってるビットが1減るまでxを右シフト、それをyとorする
}

// f^x ≡ y mod pを満たすxを√pの分割統治で求める考え方だが、
// BSGSは仕組み的には有限サイズの巡回群に使える。冪乗 mod
// pは位数p-1の巡回群をなすので使える。 巡回群上の分割統治である。
// x = m * i + jと考えると、f^j = y*f^(-mi) mod
// pと、iとjを分離できるので別々に計算して、後で突き合わせる
// m=√位数のグループに分ける⇨冪乗x=i*m+jと考えると
// iはグループ間、jはグループ内の移動で、前者をGiant、後者をBaby。
// どちらかをhashmapにいれ、どちらかをhashmapから検索して見つかったら答え。BSGS自体はO(√p）だが検索次第で最終的に色々
// jを先に調べてiを小さい順に調べると最小のxが求まる

// g^x % p = hを満たすxを求める。
// x = i*m + j (m = √pとすればiはm以下、jはm未満)として上式を変形すると
// g^(i*m+j) ≡ h (mod p) pは素数なので両辺にg^((-m)*i)をかけて
// g^j ≡ h(g^(-m))^i
// baby stepでj, giant stepで(g^(-m))^iを総当たり
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

// 説明:
// n個の点情報(x, y)を受け取り、n-1次のラグランジュ多項式上でのx =
// tの値を返す関数 計算量: O(n^2)

// x, yの値を渡すとラグランジュ補間
template <typename T>
T LagrangeInterpolation(std::vector<T>& x, std::vector<T>& y, T t) {
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

// 使用例
// https://atcoder.jp/contests/abc018/tasks/abc018_4
void ABC018D() {
  int N, M, P, Q, R, x, y, z, happy[325][325];
  std::cin >> N >> M >> P >> Q >> R;
  for (int i = 0; i < R; ++i) {
    std::cin >> x >> y >> z;
    --x, --y;
    happy[x][y] = z;
  }

  // 上記の関数で片方の組み合わせは全列挙できるので、もう片方の最適な選び方を速めに決める。
  int ans = 0;
  for (int comb = (1 << P) - 1; comb < (1 << N);
       comb = math_utils::next_combination(comb)) {
    std::vector<int> otoko(M);
    for (int i = 0; i < N; ++i)
      if (comb >> i & 1)
        for (int j = 0; j < M; ++j) otoko[j] += happy[i][j];
    sort(otoko.rbegin(), otoko.rend());

    int tmp = 0;
    for (int i = 0; i < Q; ++i) tmp += otoko[i];
    ans = std::max(ans, tmp);
  }
  std::cout << ans << '\n';
}

// https://atcoder.jp/contests/abc270/tasks/abc270_g
int ABC270G() {
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
  std::cin >> t;
  while (t--) {
    long long p, a, b, s, g;
    std::cin >> p >> a >> b >> s >> g;
    if (s == g)
      std::cout << 0 << '\n';
    else if (a == 0) {
      if (b == g)
        std::cout << 1 << '\n';
      else
        std::cout << -1 << '\n';
    } else {
      long long m = sqrt(p);
      long long ma = 1, mb = 0; // m回適用した時の係数
      for (int i = 0; i < m; ++i) {
        // X_{i+1} = X_i * a + b
        // a -> a^2, b -> a * b + b
        mb = (a * mb + b) % p;
        ma = ma * a % p;
      }
      long long ia = math_utils::mod_pow(a, p - 2, p);
      long long ib = ((-b * ia) % p + p) % p;
      // f^(-1) = ia * x + ib

      std::unordered_map<int64_t, int64_t> table;
      for (long long j = 0; j <= m; ++j) {
        if (table.find(g) == table.end()) table[g] = j;
        g = (g * ia + ib) % p;
      }
      long long ans = -1;
      for (long long i = 0; i <= m; ++i) {
        auto itr = table.find(s);
        if (itr != table.end()) {
          ans = m * i + itr->second;
          break;
        }
        s = (s * ma + mb) % p;
      }
      std::cout << ans << '\n';
    }
  }
}

// https://atcoder.jp/contests/arc042/tasks/arc042_d
int ARC042D() {
  long long X, P, A, B;
  std::cin >> X >> P >> A >> B;
  // X^i = Y(mod P)を考える。
  // iを全探索すると間に合わないのでYを固定して離散対数問題を解く。
  // Yは周期P-1なので、Pがでかいと結局間に合わないので、工夫する。
  if (B - A + 1 > P - 1) {
    std::cout << 1;
  } else if (B - A <
             100000) // 試すiが小さいとBSGSがTLEするのでここは愚直にやる。
  {
    int ans = P;
    // X^A (mod P)
    int t = math_utils::mod_pow(X, A, P);
    for (int i = 0; i < B - A + 1; ++i) {
      ans = std::min(ans, t);
      t = t * X % P;
    }
    std::cout << ans;
  } else {
    A %= P - 1;
    B %= P - 1;
    // BSGSを使う。
    // X^i = h(mod P)
    for (int h = 0; h < P; ++h) {
      int res = math_utils::babystep_giantstep(X, h, P);
      if (A <= res && res <= B) {
        std::cout << h;
        break;
      }
    }
  }
  std::cout << '\n';
  return 0;
}

// 解けてない
// https://atcoder.jp/contests/arc033/tasks/arc033_4
void ARC033D() {
  int n;
  std::cin >> n;
  long p, t;

  std::vector<long> x(n + 1), y(n + 1);
  for (int i = 0; i <= n; ++i) {
    std::cin >> p;
    x[i] = i, y[i] = p;
  }
  std::cin >> t;
  std::cout << math_utils::LagrangeInterpolation<long>(x, y, t) << '\n';
}