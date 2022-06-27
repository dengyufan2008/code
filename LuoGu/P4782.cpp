#include <iostream>
#include <stack>
#include <vector>
#define LL long long

using namespace std;

struct V {
  int d, l, r;
  vector<int> e;
} v[2000001];
int n, m, k, l;
bool ans = 1;
stack<int> s;

void S(int x) {
  if (v[x].d) {
    return;
  }
  v[x].d = v[x].l = ++k, s.push(x);
  for (int i : v[x].e) {
    S(i);
    if (!v[i].r) {
      v[x].l = min(v[x].l, v[i].l);
    }
  }
  if (v[x].d == v[x].l) {
    l++;
    while (s.top() != x) {
      v[s.top()].r = l;
      v[x].e.insert(v[x].e.end(), v[s.top()].e.begin(), v[s.top()].e.end());
      s.pop();
    }
    v[x].r = l, s.pop();
  }
}

int main() {
  cin >> n >> m;
  for (int i = 1, x, p, y, q; i <= m; i++) {
    cin >> x >> p >> y >> q;
    v[x * 2 ^ p].e.push_back(y * 2 + 1 ^ q);
    v[y * 2 ^ q].e.push_back(x * 2 + 1 ^ p);
  }
  for (int i = 1; i <= n; i++) {
    S(i * 2), S(i * 2 + 1);
  }
  for (int i = 1; i <= n; i++) {
    ans &= v[i * 2].r != v[i * 2 + 1].r;
  }
  if (ans) {
    cout << "POSSIBLE\n";
    for (int i = 1; i <= n; i++) {
      cout << (v[i * 2].r < v[i * 2 + 1].r) << ' ';
    }
  } else {
    cout << "IMPOSSIBLE\n";
  }
  return 0;
}
