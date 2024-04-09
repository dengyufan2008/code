#include <algorithm>
#include <bitset>
#include <fstream>
#define Bit bitset<kMaxN>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 1001;
int n, m, k, h, maxh, la[kMaxN], lb[kMaxN], ans[kMaxN << 1][kMaxN << 1];
Bit t, a[kMaxN], b[kMaxN];

int CalcA() {
  int ans = 1;
  for (int i = 2; i <= n; i++) {
    if (a[la[i]] != a[la[i - 1]]) {
      ans++;
    }
  }
  return ans;
}

int CalcB() {
  int ans = 1;
  for (int i = 2; i <= n; i++) {
    if (b[lb[i]] != b[lb[i - 1]]) {
      ans++;
    }
  }
  return ans;
}

void M(Bit s, Bit t) {
  if (s.none() || t.none()) {
    return;
  }
  for (int i = 1; i <= n; i++) {
    if (s[i]) {
      ans[i][h] = 2;
    } else {
      ans[i][h] = 0;
    }
    if (t[i]) {
      ans[i + n][h] = 2;
    } else {
      ans[i + n][h] = 1;
    }
  }
  h++;
}

void Add() {
  for (int i = 1; i <= n; i++) {
    ans[i][h] = 0;
  }
  for (int i = n + 1; i <= n * 2; i++) {
    ans[i][h] = 1;
  }
  h++;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> k;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    x > y ? swap(x, y) : void();
    if (x <= n && y > n) {
      a[x][y - n] = b[y - n][x] = 1;
    }
  }
  for (int i = 1; i <= n; i++) {
    la[i] = lb[i] = i;
  }
  sort(la + 1, la + n + 1, [](int i, int j) {
    return a[i].to_string() < a[j].to_string();
  });
  sort(lb + 1, lb + n + 1, [](int i, int j) {
    return b[i].to_string() < b[j].to_string();
  });
  if (CalcA() < CalcB()) {
    for (int i = 1, j = 1; i <= n; i = j) {
      t.reset();
      for (; j <= n && a[la[i]] == a[la[j]]; j++) {
        t[la[j]] = 1;
      }
      M(t, a[la[i]]);
    }
  } else {
    for (int i = 1, j = 1; i <= n; i = j) {
      t.reset();
      for (; j <= n && b[lb[i]] == b[lb[j]]; j++) {
        t[lb[j]] = 1;
      }
      M(b[lb[i]], t);
    }
  }
  maxh = -1;
  for (int i = 1, j = 1; i <= n; i = j) {
    for (; j <= n && a[la[i]] == a[la[j]]; j++) {
    }
    if (i + 1 < j) {
      for (int k = 0; k < j - i; k++) {
        for (int _k = k, _h = 0; _k; _k >>= 1, _h++) {
          ans[la[i + k]][h + _h] = _k & 1, maxh = max(maxh, _h);
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= maxh; j++) {
      ans[lb[i] + n][h + j] = 2;
    }
  }
  h += maxh + 1;
  maxh = -1;
  for (int i = 1, j = 1; i <= n; i = j) {
    for (; j <= n && b[lb[i]] == b[lb[j]]; j++) {
    }
    if (i + 1 < j) {
      for (int k = 0; k < j - i; k++) {
        for (int _k = k, _h = 0; _k; _k >>= 1, _h++) {
          ans[lb[i + k] + n][h + _h] = _k & 1, maxh = max(maxh, _h);
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= maxh; j++) {
      ans[la[i]][h + j] = 2;
    }
  }
  h += maxh + 1;
  if (h < k) {
    Add();
  }
  cout << h << '\n';
  for (int i = 1; i <= n * 2; i++) {
    for (int j = 0; j < h; j++) {
      cout << char('A' + ans[i][j]);
    }
    cout << '\n';
  }
  return 0;
}
