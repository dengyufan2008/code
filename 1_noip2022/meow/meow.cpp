#include <iostream>
#include <queue>

using namespace std;

int t, n, m, k, a[2000001], d[602], p[602];  // 2n:Down 2n+1:Up
queue<int> q;
vector<pair<int, int>> ans;

int main() {
  cin >> t;
  while (t--) {
    ans.clear(), fill(&d[0], &d[602], 0), fill(&p[0], &p[602], 0);
    while (q.empty()) {
      q.pop();
    }
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) {
      cin >> a[i];
    }
    for (int i = 1; i < n; i++) {
      q.push(i), q.push(i);
    }
    for (int i = 1; i <= m; i++) {
      if (p[a[i]]) {
        if (p[a[i]] & 1) {
          ans.push_back({p[a[i]] / 2, 0});
        } else {
          ans.push_back({n, 0}), ans.push_back({p[a[i]] / 2, n});
        }
        q.push(p[a[i]]), d[p[a[i]]] = 0, p[a[i]] = 0;
      } else if (!q.empty()) {
        ans.push_back({q.front(), 0});
        if (d[q.front() * 2]) {
          p[a[i]] = q.front() * 2 + 1, d[q.front() * 2 + 1] = a[i];
        } else {
          p[a[i]] = q.front() * 2, d[q.front() * 2] = a[i];
        }
        q.pop();
      } else {
        ;
      }
    }
    cout << ans.size() << '\n';
    for (auto i : ans) {
      if (i.second) {
        cout << 2 << ' ' << i.first << ' ' << i.second << '\n';
      } else {
        cout << 1 << ' ' << i.first << '\n';
      }
    }
  }
  return 0;
}
