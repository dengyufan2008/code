// 谁爱写谁写
#include <algorithm>
#include <fstream>
#define LL long long
#define PII pair<int, int>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

// const int kMaxN = 3001, kMod = 998244353;
const int kMaxN = 5, kMod = 998244353;
int n, c, d;
LL ans;
PII a[kMaxN];
PII mnl[kMaxN][kMaxN];  // x 在 (ix, jx) 中, y >= iy 的最小值和出现次数
PII mxl[kMaxN][kMaxN];  // x 在 (ix, jx) 中, y <= iy 的最大值和出现次数
PII mnr[kMaxN][kMaxN];  // x 在 (ix, jx) 中, y >= jy 的最小值和出现次数
PII mxr[kMaxN][kMaxN];  // x 在 (ix, jx) 中, y <= jy 的最大值和出现次数

void Init() {
  for (int i = 1; i <= n; i++) {
    PII mn = {d + 1, 0}, mx = {0, 0};
    int j = i;
    for (; j <= n && a[i].first == a[j].first; j++) {
    }
    for (int k = j; j <= n; j = k) {
      PII _mn = mn, _mx = mx;
      for (; k <= n && a[j].first == a[k].first; k++) {
        mnl[i][k] = _mn, mxl[i][k] = _mx;
        if (a[k].second >= a[i].second) {
          if (!mn.first || mn.first > a[k].second) {
            mn = {a[k].second, 1};
          } else if (mn.first == a[k].second) {
            mn.second++;
          }
        }
        if (a[k].second <= a[i].second) {
          if (!mx.first || mx.first < a[k].second) {
            mx = {a[k].second, 1};
          } else if (mx.first == a[k].second) {
            mx.second++;
          }
        }
      }
    }
  }
  for (int j = 1; j <= n; j++) {
    PII mn = {d + 1, 0}, mx = {0, 0};
    int i = j;
    for (; i >= 1 && a[j].first == a[i].first; i--) {
    }
    for (int k = i; i >= 1; i = k) {
      PII _mn = mn, _mx = mx;
      for (; k >= 1 && a[i].first == a[k].first; k--) {
        mnr[k][j] = _mn, mxr[k][j] = _mx;
        if (a[k].second >= a[j].second) {
          if (!mn.first || mn.first > a[k].second) {
            mn = {a[k].second, 1};
          } else if (mn.first == a[k].second) {
            mn.second++;
          }
        }
        if (a[k].second <= a[j].second) {
          if (!mx.first || mx.first < a[k].second) {
            mx = {a[k].second, 1};
          } else if (mx.first == a[k].second) {
            mx.second++;
          }
        }
      }
    }
  }
}

void Sum2(LL x, LL w) {
  ans = (ans + ((332748118 * x + 499122176) % kMod * x + 166374059) * x % kMod * w) % kMod;
}

void Sum3(LL x, LL w) {
  ans = (ans + ((748683265 * x + 499122176) % kMod * x + 748683265) * x % kMod * x % kMod * w) % kMod;
}

void Sum4(LL x, LL w) {
  ans = (ans + (((598946612 * x + 499122176) % kMod * x + 332748118) % kMod * x % kMod * x + 565671800) % kMod * x % kMod * w) % kMod;
}

void Sum(int l, int r, LL a2, LL a3, LL a4, int w) {  // [l, r)
  if (l >= r) {
    return;
  }
  a2 = a2 * w % kMod, a3 = a3 * w % kMod, a4 = a4 * w % kMod;
  Sum2(l, -a2), Sum2(r, a2);
  if (a3) {
    Sum3(l, -a3), Sum3(r, a3);
  }
  if (a4) {
    Sum4(l, -a4), Sum4(r, a4);
  }
}

void CalcW(int l, int r, int p, int q, int w) {
  int s = max(r - l + 2, q - p + 2), t = min(c, d) + 1;
  int f0 = c - l + 1, f1 = r + 1, f2 = d - p + 1, f3 = q + 1;
  LL g0 = l, g1 = l - r - 1, g2 = c + 1, g3 = c - r;
  LL h0 = p, h1 = p - q - 1, h2 = d + 1, h3 = d - q;

  Sum(max(s, max(f1, f3)), min(t, min(f0, f2)), g0 * h0, 0, 0, w);
  Sum(max(s, f1), min(t, min(f0, min(f2, f3))), g0 * h1, g0, 0, w);
  Sum(max(s, max(f1, max(f2, f3))), min(t, f0), g0 * h2, -g0, 0, w);
  Sum(max(s, max(f1, f2)), min(t, min(f0, f3)), g0 * h3, 0, 0, w);

  Sum(max(s, f3), min(t, min(f0, min(f1, f2))), g1 * h0, h0, 0, w);
  Sum(s, min(t, min(f0, min(f1, min(f2, f3)))), g1 * h1, g1 + h1, 1, w);
  Sum(max(s, max(f2, f3)), min(t, min(f0, f1)), g1 * h2, -g1 + h2, -1, w);
  Sum(max(s, f2), min(t, min(f0, min(f1, f3))), g1 * h3, h3, 0, w);

  Sum(max(s, max(f0, max(f1, f3))), min(t, f2), g2 * h0, -h0, 0, w);
  Sum(max(s, max(f0, f1)), min(t, min(f2, f3)), g2 * h1, g2 - h1, -1, w);
  Sum(max(s, max(f0, max(f1, max(f2, f3)))), t, g2 * h2, -g2 - h2, 1, w);
  Sum(max(s, max(f0, max(f1, f2))), min(t, f3), g2 * h3, -h3, 0, w);

  Sum(max(s, max(f0, f3)), min(t, min(f1, f2)), g3 * h0, 0, 0, w);
  Sum(max(s, f0), min(t, min(f1, min(f2, f3))), g3 * h1, g3, 0, w);
  Sum(max(s, max(f0, max(f2, f3))), min(t, f1), g3 * h2, -g3, 0, w);
  Sum(max(s, max(f0, f2)), min(t, min(f1, f3)), g3 * h3, 0, 0, w);
}

void CalcAns() {
  Sum(1, min(c, d) + 1, (c + 1) * (d + 1), -(c + 1) - (d + 1), 1, 1);
  for (int i = 1; i <= n; i++) {  // 只有一个点
    CalcW(a[i].first, a[i].first, a[i].second, a[i].second, -1);
  }
  for (int i = 2; i <= n; i++) {  // x 轴上退化
    if (a[i - 1].first == a[i].first) {
      CalcW(a[i].first, a[i].first, a[i - 1].second, a[i].second, 1);
    }
  }
  for (int i = 1; i <= n; i++) {  // x 轴上未退化
    for (int j = i + 1; j <= n; j++) {
      if (a[i].first == a[j].first) {
        continue;
      }
      int p = a[j - 1].first == a[j].first ? a[j - 1].second : 0;
      int q = a[i + 1].first == a[i].first ? a[i + 1].second : d + 1;
      if (a[i].second <= a[j].second) {
        if (mnl[i][j].first >= a[j].second && mnl[i][j].first < q &&
            mxr[i][j].first <= a[i].second && mxr[i][j].first > p) {
          if (mnl[i][j].first == a[j].second) {
            if (mxr[i][j].first == a[i].second) {
              ;
            } else {
              ;
            }
          } else {
            if (mxr[i][j].first == a[i].second) {
              ;
            } else {
              ;
            }
          }
        }
      } else {
        ;
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> c >> d >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].first >> a[i].second;
  }
  sort(a + 1, a + n + 1);
  Init(), CalcAns();
  cout << (ans + kMod) % kMod << '\n';
  return 0;
}
