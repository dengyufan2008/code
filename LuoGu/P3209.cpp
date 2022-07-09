#include <algorithm>
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
int t, n, m, k, l, d[2][201];
bool ans = 1;
PII a[607];
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
  cin >> t;
  while (t--) {
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
      v[i].d = v[i].l = v[i].r = 0;
      v[i].e.clear();
    }
    for (int i = 1; i <= m; i++) {
      a[i].first = d[1][a[i].first], a[i].second = d[1][a[i].second];
    }
    sort(a + 1, a + m + 1);
    for (int i = 1; i <= m; i++) {
      for (int j = i + 1; j < i + m; j++) {
        int k = (j - 1) % m + 1;
        if (a[i].first < a[k].first && a[i].second < a[k].second || a[i].first > a[k].first && a[i].second > a[k].second) {
          v[i].e.push_back(k + m), v[i + m].e.push_back(k);
          v[k].e.push_back(i + m), v[k + m].e.push_back(i);
        }
      }
    }
    for (int i = 1; i <= m; i++) {
      S(i), S(i + m);
    }
    for (int i = 1; i <= m; i++) {
      ans &= v[i].r != v[i + m].r;
    }
    cout << (ans ? "YES\n" : "NO\n");
  }
  return 0;
}
