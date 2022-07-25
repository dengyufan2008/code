#include <iostream>
#include <stack>
#include <vector>
#define LL long long
#define PII pair<int, int>

using namespace std;

struct V {
  int d, l, r;
  vector<int> e;
} v[1214];
int t, n, m, _m, k, l, d[2][201];
bool ans;
PII a[607];
vector<PII> c;
stack<int> s;

void Tarjan(int x) {
  if (v[x].d) {
    return;
  }
  v[x].d = v[x].l = ++k, s.push(x);
  for (int i : v[x].e) {
    Tarjan(i);
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
  cin >> t;
  while (t--) {
    k = l = _m = 0, ans = 1, c.clear();
    fill(&v[1], &v[1214], v[0]);
    cin >> n >> m;
    if (m > n * 3 + 6) {
      cout << "NO\n";
      continue;
    }
    for (int i = 1; i <= m; i++) {
      cin >> a[i].first >> a[i].second;
    }
    for (int i = 1; i <= n; i++) {
      cin >> d[0][i];
      d[1][d[0][i]] = i;
    }
    for (int i = 1; i <= m; i++) {
      a[i].first = d[1][a[i].first], a[i].second = d[1][a[i].second];
      if (a[i].first > a[i].second) {
        swap(a[i].first, a[i].second);
      }
    }
    for (int i = 1; i <= m; i++) {
      for (int j = 1; j <= m; j++) {
        if (i != j && a[i].second - a[i].first != 1 && a[j].second - a[j].first != 1 &&
            a[i].second - a[i].first != n - 1 && a[j].second - a[j].first != n - 1 &&
            (a[i].first < a[j].first && a[i].second < a[j].second ||
             a[i].first > a[j].first && a[i].second > a[j].second)) {
          _m += 2, c.push_back({i, j});
        }
      }
    }
    m = _m;
    for (auto i : c) {
      v[i.first].e.push_back(i.second + m);
      v[i.first + m].e.push_back(i.second);
    }
    for (int i = 1; i <= m; i++) {
      Tarjan(i), Tarjan(i + m);
    }
    for (int i = 1; i <= m; i++) {
      ans &= v[i].r != v[i + m].r;
    }
    cout << (ans ? "YES\n" : "NO\n");
  }
  return 0;
}
