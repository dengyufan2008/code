#include <bits/stdc++.h>

using namespace std;

const int kMaxM = 3005;

int a[kMaxM], s[kMaxM << 1], cnt[kMaxM], tmp[kMaxM];
int n, c, m, p[kMaxM << 1];
int r, mid, ans2;

int min(int x, int y) { return x < y ? x : y; }

int manacher(int* a) {
  memset(s, 0, sizeof(s));
  memset(p, 0, sizeof(p));
  s[m = 0] = 0, s[++m] = -1, r = mid = 0;
  for (int i = 0; i < n; ++i) {
    // cout << a[i] << ' ';
    s[++m] = a[i], s[++m] = -1;
  }
  // cout << '\n';
  int res = 0;
  for (int i = 1; i < m; ++i) {
    if (i <= r) {
      p[i] = min(p[(mid << 1) - i], p[mid] + mid - i);
    } else {
      p[i] = 1;
    }
    for (; s[i - p[i]] == s[i + p[i]]; ++p[i]) {
    }
    if (i + p[i] - 1 > r) {
      r = i + p[i] - 1, mid = i;
    }
    if (res < p[i]) {
      res = p[i];
    }
  }
  return res - 1;
}

int work() {
  int res = 0;
  for (int i = 0; i < n; i++) {
    tmp[i] = a[i];
    for (int j = i; j < n; j++) {
      for (int k = 0; k < n; k++) {
        tmp[k] = a[k];
      }
      sort(tmp + i, tmp + j + 1);
      int tmpp = manacher(tmp);
      res = max(res, tmpp);
      if (tmpp == 7) {
        // for (int i = 0; i < n; i++) {
        //   cout << tmp[i] << ' ';
        // }
        // cout << "3\n";
      }
    }
  }
  return res;
}

int main() {
  ifstream cin("kanzenkankaku.in");
  ofstream cout("kanzenkankaku.out");
  cin >> n >> c;
  s[m] = 0, s[++m] = -1;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    cnt[a[i]]++;
  }
  for (int i = 1; i <= c; i++) {
    ans2 = max(ans2, cnt[i]);
  }
  cout << max({work(), manacher(a), ans2}) << endl;

  return 0;
}