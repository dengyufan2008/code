#include <fstream>
#include <vector>

using namespace std;

ifstream cin("h.in");
ofstream cout("h.out");

const int kMaxN = 1e5 + 2, kMaxL = 17;
int u, n, ans, a[kMaxN], p[kMaxN], q[kMaxN];
int s[kMaxN], t[kMaxN], d[kMaxL][kMaxN], lg[kMaxN];
vector<int> v;

void CalcST() {
  for (int i = 1; i <= n; i++) {
    s[i] = s[i - 1] & a[i];
  }
  for (int i = n; i >= 1; i--) {
    t[i] = t[i + 1] & a[i];
  }
}

int CalcAns() {
  int w = 0;
  CalcST();
  for (int i = 1; i < n; i++) {
    w = max(w, s[i] + t[i + 1]);
  }
  return w;
}

int Ask(int x, int y) {
  int l = lg[y - x + 1];
  return d[l][x] & d[l][y - (1 << l) + 1];
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 2; i < kMaxN; i++) {
    lg[i] = lg[i >> 1] + 1;
  }
  cin >> u;
  while (u--) {
    cin >> n, s[0] = t[n + 1] = ~(-1 << 30);
    for (int i = 1; i <= n; i++) {
      cin >> a[i], d[0][i] = a[i];
    }
    CalcST(), v.clear(), ans = 0;
    for (int i = 1, _p = 0, _q = 0; i <= n; i++) {
      ans = max(ans, i > 1 ? s[i - 1] + t[i] : 0);
      p[i] = s[i] == s[i - 1] ? p[i - 1] : i - 1;
      q[i] = t[i] == t[i - 1] ? q[i - 1] : i - 1;
      if (s[i] != s[i - 1] || t[i] != t[i + 1]) {
        v.push_back(i);
      }
    }
    for (int i = 1; i < kMaxL; i++) {
      for (int j = 1; j <= n; j++) {
        d[i][j] = d[i - 1][j];
        if (j + (1 << i - 1) <= n) {
          d[i][j] &= d[i - 1][j + (1 << i - 1)];
        }
      }
    }
    for (int i : v) {
      for (int j = 1; j <= i - 1; j++) {
        ans = max(ans, s[i] + (t[i + 1] & a[j]));
        for (int k = p[i - 1]; k >= j; k = p[k]) {
          ans = max(ans, (s[k] & a[i]) + (Ask(k + 1, i - 1) & t[i + 1] & a[j]));
        }
      }
      for (int j = i + 1; j <= n; j++) {
        ans = max(ans, (s[i - 1] & a[j]) + t[i]);
        for (int k = q[j]; k > i; k = q[k]) {
          ans = max(ans, (s[i - 1] & Ask(i + 1, k) & a[j]) + (t[k + 1] & a[i]));
        }
      }
    }
    for (int i = 0; i < v.size(); i++) {
      for (int j = i + 1; j < v.size(); j++) {
        swap(a[v[i]], a[v[j]]);
        ans = max(ans, CalcAns());
        swap(a[v[i]], a[v[j]]);
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
