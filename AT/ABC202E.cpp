#include <bits/stdc++.h>
#define LL long long

using namespace std;

vector<vector<int>> children, lst;
vector<int> in, out, depth;
int n, q, u, d, timer;

void S(const int u) {
  in[u] = timer++;
  lst[depth[u]].push_back(in[u]);
  for (const int v : children[u]) {
    depth[v] = depth[u] + 1;
    S(v);
  }
  out[u] = timer++;
}

int main() {
  cin >> n;
  children = lst = vector<vector<int>>(n), in = out = depth = vector<int>(n);
  for (int i = 1, p; i < n; ++i) {
    cin >> p;
    children[p - 1].push_back(i);
  }
  S(0);
  cin >> q;
  while (q--) {
    cin >> u >> d;
    u--;
    const auto& v = lst[d];
    cout << lower_bound(v.cbegin(), v.cend(), out[u]) - lower_bound(v.cbegin(), v.cend(), in[u]) << endl;
  }
  return 0;
}
