---
layout: default
title: fenwick_tree
---

# {{ page.title }}

## 概要

### Points:
各数字のLSBは区間の長さを表す。LSBはi&-iみたいに簡単に取れるので左端から　すべて埋められる
更新時は、被覆される要素すべて更新　たかだかlogn　単純に区間のサイズを足し引きして必要なところを更新している。
-i = ~i + 1

### TODO:
* 抽象化 任意の区間演算ならアーベル群　sum xor など
    - [1,i]だけならmin,maxもいける(こいつらは逆操作できない)、だがBIT2本でmin,maxも行ける模様?
* BIT2本で区間加算するやつ　→　クエリをバラしてやるところが遅延評価セグ木っぽい？
* 必要なところだけ作るBIT　→　辞書配列に持たせる　indexでかくても各要素へのアクセスが少ないパターン
* 多次元BITのverify

## 計算量
update(i, x): update i-th element to x
query(i): returns a result of applying operations to [1, i] (1-indexed)
O(logn) each

## 使用例

## verify

- lower_bound(): https://atcoder.jp/contests/arc033/submissions/58037272


## コード

{% highlight cpp %}
{% include data-structure/fenwick_tree.hpp %}
{% endhighlight %}