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
