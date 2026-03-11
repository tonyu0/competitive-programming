---
layout: default
title: math_utils
---

# {{ page.title }}

## 概要

### ext_gcd
a * x + b * y = gcd(a, b)を満たすx, yを取得
最終的にa0 = gcd(a, b), b0 = 0, x = 1, y = 0の状態を作り出す。
そこから来た道を辿り、a0, b0からa, bを復元する過程でx, yを求めるイメージ。

### linear_congruence
連立線形合同式を解く。拡張ユークリッドの誤除法を用いる。
解は無数にあるので、解全体を表す x ≡ b (mod m)のbとmのペアを返す。
x ≡ b1 (mod m1), x ≡ b2 (mod m2), ...
m1, m2 ...が互いに素なら、xが一意に定まる。

### floor_sum
floor((a * x + b) / m) = yとなるxの範囲を考える。
ceil, floorは不等式で評価するとよい
最小値xは
y <= (a * x + b) / mなので
my <= ax + b
my - b / a <= x
xは整数なので、最小値は左辺の切り上げ(ceil((m * y - b) / a))
最小値x_iが分かると、iになる範囲はx_{i + 1 } - x_i
ymaxだけはn - x_ymax
(x_2 - x_1) * 1 +(x_3 - x_2) * 2 +... +(x_ymax - x_{ymax - 1}) *(ymax- 1)+(n - x_ymax) * ymax
整理すると、(最後のn * ymaxにより、ymax個の塊にnをぶんぱい可能)
\sum_{i = 1 } ^ {ymax }(n - x_i)
これを崩してymax - 1までの小問題にできるか考える。
(ここでx_max = m * y_max - bと置くとうまくいくっぽいが、仕組みが分からん)
\sum_{i = 1 } ^ {ymax}(n - ceil(m * i - b) / a)の和の順番を逆にして
\sum_{i = 0 } ^ {ymax - 1}(n - ceil(m *(ymax - i) - b) / a)
(0 - ceil(x) = floor(0 - x) を使って)
 \sum_{i = 0 } ^ {ymax - 1 }(n + floor((b - m *(ymax - i)) / a)
n*ymax + \sum_{i = 0 } ^ {ymax - 1 } floor((m * i + b - m * ymax)/a)
最初の式 : \sum_{i = 0 } ^ {n - 1 } floor((a * i + b) / a)と比較すると

### next_combination
説明: nに含まれるサイズkの部分集合を列挙する。
2の補数表現より-x == (~x) + 1なので、最下位ビットは x & -xで取れる。
部分集合を投げると次の部分集合を返してくれる関数
bit全探索のビット数固定版とも言える

### babystep_giantstep
f^x ≡ y mod pを満たすxを√pの分割統治で求める考え方だが、
BSGSは仕組み的には有限サイズの巡回群に使える。冪乗 mod
pは位数p-1の巡回群をなすので使える。 巡回群上の分割統治である。
x = m * i + jと考えると、f^j = y*f^(-mi) mod
pと、iとjを分離できるので別々に計算して、後で突き合わせる
m=√位数のグループに分ける⇨冪乗x=i*m+jと考えると
iはグループ間、jはグループ内の移動で、前者をGiant、後者をBaby。
どちらかをhashmapにいれ、どちらかをhashmapから検索して見つかったら答え。BSGS自体はO(√p）だが検索次第で最終的に色々
jを先に調べてiを小さい順に調べると最小のxが求まる

g^x % p = hを満たすxを求める。
x = i*m + j (m = √pとすればiはm以下、jはm未満)として上式を変形すると
g^(i*m+j) ≡ h (mod p) pは素数なので両辺にg^((-m)*i)をかけて
g^j ≡ h(g^(-m))^i
baby stepでj, giant stepで(g^(-m))^iを総当たり

### lagrange_interpolation
n個の点情報(x, y)を受け取り、n-1次のラグランジュ多項式上でのx =
tの値を返す関数 計算量: O(n^2)

x, yの値を渡すとラグランジュ補間

## 計算量

## 使用例

## verify

### next_combination
https://atcoder.jp/contests/abc018/submissions/8411220

### babystep_giantstep
https://atcoder.jp/contests/abc270/submissions/72793289
↑ライブラリ未使用、考え方のみ
https://atcoder.jp/contests/arc042/submissions/8698256

### lagrange_interpolation
https://atcoder.jp/contests/arc033/submissions/8525787
解けてない

## コード
```
# comment
```