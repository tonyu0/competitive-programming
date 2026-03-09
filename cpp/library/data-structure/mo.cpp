#include <algorithm>
#include <cmath>
#include <vector>

// 1. bucket_size = sqrt(n)
// 2. クエリの左端・右端を一通りpush()。
// 3. run()　
//    1.クエリの処理順を左端・右端から決める。
//     まず左端が位置するバケットで昇順ソートする。
//     同じバケットの場合は、左端はどうでもいい（後述）が右端で昇順ソート
//    2.やはり下の説明だと右端の計算量が微妙でやはり奇数番目のバケットは右端降順にすると
//     右端が右側に向かうジグザグになって右端の移動量が減りそう（明らかに早くなるが厳密な解析はまだ）
// 同一グループ内では、どの順番でクエリを処理しても、各クエリ間での左端の移動回数は√N回以下
// 右端を処理する際、右端でソートして左から順に処理すれば、右端は左から右へ移動するだけでよくなる。
// ->
// 各グループで、（右端単調増加より）右端の移動が高々N回になるから、右端の移動もO(N√N)で抑えられる。
// ->
// 各グループで、（バケットサイズが√Nだから）クエリごとの左端の移動は√N以内に抑えられるから、全N個のクエリでの移動を考えてもO(N√N)
// 4.
// query_idxごとにループして、今見ているquery_idxのl,rに今見ている区間が一致するようにmove()を使って区間を伸縮する
// move(idx)ではin配列（boolで今見ている区間を見ている）のin[idx]をflipする(toggleのこと)
// 5. 区間の伸縮が終わったらsolve()でquery_idxに対する解を確定する

class Mo {
public:
  Mo(int n, int q) : bucket_size((int)sqrt(n)), query_idx(q), in(n) {
    for (int i = 0; i < q; ++i) query_idx[i] = i;
  }

  // [l, r)
  void push(int l, int r) {
    left.emplace_back(l);
    right.emplace_back(r);
  }

  void run() {
    std::sort(begin(query_idx), end(query_idx), [&](int i, int j) {
      if (left[i] / bucket_size != left[j] / bucket_size)
        return left[i] < left[j]; // 違うバケットにいたら
      else if (left[i] / bucket_size % 2 == 0)
        return right[i] < right[j]; // 同じバケットにいたら
      return right[i] > right[j];
    });
    int nl = 0, nr = 0;
    for (int idx : query_idx) {
      while (nl > left[idx]) move(--nl);
      while (nr < right[idx]) move(nr++);
      while (nl < left[idx]) move(nl++);
      while (nr > right[idx]) move(--nr);
      solve(idx);
    }
  }

private:
  int bucket_size;
  std::vector<int> left, right, query_idx;
  std::vector<bool> in;
  void move(int idx) {
    in[idx].flip();
    if (in[idx])
      insert(idx);
    else
      erase(idx);
  }

  // 問題ごとに変える
  void insert(int idx);
  void erase(int idx);
  void solve(int idx);
};

/* 例: ABC174F　https://atcoder.jp/contests/abc174/submissions/15839130
// ---- mo 用 ----
vector<int> cnt(500001), a, ans;
int num_kind = 0;

void Mo::insert(int idx) {
  if (cnt[a[idx]] == 0) ++num_kind;
  ++cnt[a[idx]];
}

void Mo::erase(int idx) {
  if (cnt[a[idx]] == 1) --num_kind;
  --cnt[a[idx]];
}

void Mo::solve(int idx) { ans[idx] = num_kind; }
// ----
*/