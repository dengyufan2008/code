#include <fstream>
#include <queue>
#define LL long long

using namespace std;

ifstream cin("f.in");
ofstream cout("f.out");

const int kMaxN = 2e5 + 1;
int n, m, t;
LL l, r, w[kMaxN], d[kMaxN];
vector<pair<int, int>> v[kMaxN];
priority_queue<pair<int, int>> q;

bool P(LL mid, LL s) {
  while (!q.empty()) {
    q.pop();
  }
  for (int i = 1; i <= n; i++) {
    d[i] = 0;
  }
  LL g = 0;
  for (int i = 1; i <= t; i++) {
    LL f = i < t ? w[i] + s - mid + 1 >> 1 : s;
    for (auto j : v[i]) {
      if (j.first > t) {
        q.push(j);
      }
    }
    g -= d[i];
    for (; g < f && !q.empty();) {
      int h = min(f - g, (LL)q.top().second), x = q.top().first;
      g += h, d[x] += h;
      h = q.top().second - h, q.pop();
      h ? q.push({x, h}) : void();
    }
    if (g < f) {
      return 0;
    }
  }
  for (int i = t + 1; i <= n; i++) {
    LL f = w[i] + s - mid + 1 >> 1;
    g -= d[i];
    if (g < f) {
      return 0;
    }
  }
  return 1;
}

bool C(LL mid) {  // 经证明, 只有这两种取值. 比较愚蠢的地方.
  return P(mid, w[t] - mid) || P(mid, w[t] - mid + 1);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, a, b, c; i <= m; i++) {
    cin >> a >> b >> c;
    a > b ? swap(a, b) : void();
    v[a].push_back({b, c}), w[a] += c, w[b] -= c;
  }
  for (int i = 1; i <= n; i++) {
    w[i] += w[i - 1], w[t] < w[i] && (t = i);
  }
  l = 0, r = w[t] - 1;
  while (l <= r) {
    LL mid = l + r >> 1;
    if (C(mid)) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  cout << l << '\n';
  return 0;
}
