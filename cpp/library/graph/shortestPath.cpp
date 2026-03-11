#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

template <bool directed = false>
class shortest_path {
  using P = std::pair<int, long long>;
  static constexpr int INF = 0x3f3f3f3f;

  int n;
  std::vector<std::vector<P>> graph;

public:
  shortest_path(int n) : n(n), graph(n) {}
  void add_edge(int u, int v, ll c) {
    graph[u].emplace_back(v, c);
    if (!directed) graph[v].emplace_back(u, c);
  }

  bool bellman_ford(int s, vector<long long>& dist) {
    int n = graph.size();
    dist.assign(n, INF);
    dist[s] = 0;

    for (int i = 0; i < n; ++i) {
      bool update = false;
      for (int v = 0; v < n; ++v) {
        for (auto [nv, cost] : graph[v]) {
          if (dist[v] != INF && dist[nv] > dist[v] + cost) {
            dist[nv] = dist[v] + cost;
            update = true;

            if (i == n - 1) {
              // negative cycle
              return true;
            }
          }
        }
      }
      if (!update) break;
    }
    return false;
  }

  std::vector<ll> dijkstra(int s) {
    std::vector<ll> dist(n, 1LL << 60);
    dist[s] = 0;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.emplace(0, s);
    while (!pq.empty()) {
      auto [d, v] = pq.top();
      pq.pop();
      if (dist[v] < d) continue;
      for (auto [nv, cost] : graph[v]) {
        if (dist[nv] > dist[v] + cost) {
          dist[nv] = dist[v] + cost;
          pq.emplace(dist[nv], nv);
        }
      }
    }
    return dist;
  }
};