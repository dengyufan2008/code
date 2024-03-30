#include <fstream>
#include <queue>

using namespace std;

ifstream cin("kanzenkankaku.in");
ofstream cout("kanzenkankaku.out");

const int kMaxN = 3002;
int n, m, ans, a[kMaxN], b[kMaxN], c[kMaxN], d[kMaxN];

int Calc(int l, int r, bool o) {
  int s = 0, w = 0, mx = 0, h = 1, t = m, u = 0, _l = l, _r = r;
  fill(&b[1], &b[m] + 1, 0);
  fill(&c[1], &c[m] + 1, 0);
  fill(&d[1], &d[n] + 2, 0);
  if (o) {
    for (int i = r; i <= n; i++) {
      if (a[i] < a[l]) {
        u = a[i];
        break;
      }
    }
  }
  for (; _l >= 1 && _r <= n;) {
    for (; _r <= n && a[_r] == u; _r++) {
    }
    _l--, _r++;
  }
  for (_r--; _r >= r;) {
    if (a[_r] == a[++_l]) {
      d[_r] = d[_r + 1] + 1;
    }
    for (_r--; _r >= r && a[_r] == u; _r--) {
      d[_r] = d[_r + 1];
    }
  }
  l >= 1 && (b[a[l]]++);
  for (int i = l - 1; i >= 1 && a[i] >= a[i + 1]; b[a[i--]]++) {
  }
  for (int i = r; i <= n; i++) {
    if (a[i] == u) {
      s++;
    } else if (a[i] <= t) {
      c[a[i]]++;
      if (c[a[i]] > b[a[i]]) {
        t = a[i];
        for (; h > t; w -= min(b[h], c[h]), h--) {
        }
      } else {
        w += a[i] <= h;
        for (; h <= t && b[h] == c[h]; h++, w += min(b[h], c[h])) {
        }
      }
    }
    mx = max(mx, s + w * 2 + (s + w == i - r + 1 ? d[i + 1] * 2 : 0));
  }
  return mx;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    ans = max(ans, ++b[a[i]]);
  }
  for (int u : {0, 1}) {
    for (int i = 1; i <= n; i++) {
      for (int o : {0, 1}) {
        int l = 1, k = min(i, n - i + o);
        for (; l <= k; l++) {
          if (a[i - l + 1] != a[i + l - o]) {
            break;
          }
        }
        ans = max(ans, Calc(i - l + 1, i + l - o, 0) + max(l * 2 - 2 - o, 0));
      }
    }
    for (int i = 1; i <= n; i++) {
      ans = max(ans, Calc(i - 1, i, 1));
    }
    for (int i = 1; i <= n; i++) {
      a[i] = m - a[i] + 1;
    }
    for (int i = 1, j = n; i < j; i++, j--) {
      swap(a[i], a[j]);
    }
  }
  cout << ans << '\n';
  return 0;
}
