#include <algorithm>
#include <fstream>
#include <vector>
#define PII pair<int, int>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 22, kInf = 2e9, kMod = 998244353;
int n, m, k, w[1 << kMaxN], d[1 << kMaxN];
PII a[kMaxN], f[1 << kMaxN];
vector<int> p[1 << kMaxN];

PII Add(PII x, int y) { return {x.first + y, x.second}; }

void Merge(PII &x, PII y) {
  if (x.first > y.first) {
    x = y;
  } else if (x.first == y.first) {
    x.second = (x.second + y.second) % kMod;
  }
}

bool C(int s, int t) { return (s & -s) ^ (t & -t); }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> a[i].first >> a[i].second;
  }
  m = n >> 1, sort(a, a + n, [](PII i, PII j) {
    return i.second > j.second;
  });
  for (int i = 0; i < n; i++) {
    w[1 << i] = a[i].first, d[1 << i] = a[i].second;
  }
  for (int s = 0; s < 1 << n; s++) {
    f[s] = {s ? kInf : 0, 1};
    if (s & s - 1 ^ s) {
      w[s] = w[s & s - 1] + w[s & -s];
      d[s] = d[s & -s];
    }
  }
  for (int s = 0; s < 1 << m; s++) {
    for (int t = s; t; t = t - 1 & s) {
      if (C(t - 1 & s, s)) {
        p[s].push_back(t - 1 & s);
      }
    }
    sort(p[s].begin(), p[s].end(), [](int i, int j) {
      return w[i] > w[j];
    });
  }
  for (int s = 0; s < 1 << n - m; s++) {
    for (int t = s; t < 1 << n - m; t = t + 1 | s) {
      p[s << m].push_back(t << m);
    }
    sort(p[s << m].begin(), p[s << m].end(), [](int i, int j) {
      return w[i] > w[j];
    });
  }
  for (int s = 0; s < 1 << n; s++) {
    int l = s & ~(-1 << m), r = s >> m << m;
    PII g = {kInf, 1};
    for (int i = 0, j = 0; j < p[r].size(); j++) {
      int _r = p[r][j];
      for (; l && i < p[l].size(); i++) {
        int _l = p[l][i];
        if (w[_l] + w[r] + k >= w[l] + w[_r]) {
          Merge(g, Add(f[_l | r], d[l]));
        } else {
          break;
        }
      }
      Merge(f[l | _r], g);
      if (C(_r, r) && !l && w[r] + k >= w[_r]) {
        Merge(f[l | _r], Add(f[l | r], d[_r]));
      }
    }
  }
  cout << f[~(-1 << n)].first << ' ' << f[~(-1 << n)].second << '\n';
  return 0;
}
