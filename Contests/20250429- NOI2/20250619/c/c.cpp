#include <fstream>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 302, kMod = 1e9 + 7;
int n, ans, a[kMaxN];

void Input() {
  static string s;
  cin >> n >> s;
  for (int i = 1; i <= n; i++) {
    if (s[i - 1] == '(') {
      a[i] = 1;
    } else if (s[i - 1] == ')') {
      a[i] = -1;
    }
  }
  if (n & 1) {
    cout << 0 << '\n';
    exit(0);
  }
}

void Update(int &x, int y) {
  x += y, x >= kMod && (x -= kMod);
}

void Update(int &x, LL y) {
  x = (x + y) % kMod;
}

void CalcValid() {
  static int f[kMaxN][kMaxN];
  f[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = i; j >= 0; j -= 2) {
      f[i][j] = 0;
      if (j > 0 && a[i] != -1) {
        Update(f[i][j], f[i - 1][j - 1]);
      }
      if (j < i && a[i] != 1) {
        Update(f[i][j], f[i - 1][j + 1]);
      }
    }
  }
  Update(ans, f[n][0]);
}

void CalcInvalid(const bool u) {  // 是否需要保证两边都不合法的情况中右侧选中的不是最高点
  static int f[kMaxN][kMaxN][kMaxN];
  static int g[kMaxN][kMaxN << 1][3];  // 0/1:是否已经有了一个 =o 的位置 2:到过负数
  static int h[kMaxN][kMaxN << 1][2];  // 0/1:是否已经有了一个 =o 的位置
  fill(&f[0][0][0], &f[kMaxN][0][0], 0);
  f[0][0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = i - 1; j >= 0; j -= 2) {
      for (int k = j; k < i; k++) {
        int w = f[i - 1][j][k];
        if (w) {
          if (a[i] != -1) {
            Update(f[i][j + 1][max(k, j + 1)], w);
          }
          if (j > 0 && a[i] != 1) {
            Update(f[i][j - 1][k], w);
          }
        }
      }
    }
  }
  for (int o = 0; o <= n; o++) {
    g[n][kMaxN][!!o] = 0, g[n][kMaxN][!o] = 1;
    h[n][kMaxN][!!o] = 0, h[n][kMaxN][!o] = 1;
    for (int i = n; i >= 1; i--) {
      for (int j = -(n - i + 1); j <= n - i + 1; j += 2) {
        g[i - 1][j + kMaxN][0] = g[i - 1][j + kMaxN][1] = g[i - 1][j + kMaxN][2] = 0;
        h[i - 1][j + kMaxN][0] = h[i - 1][j + kMaxN][1] = 0;
        if (j > -(n - i + 1) && a[i] != 1) {
          if (j > 0) {
            Update(g[i - 1][j + kMaxN][0], g[i][j - 1 + kMaxN][0]);
            Update(g[i - 1][j + kMaxN][1], g[i][j - 1 + kMaxN][1]);
            if (j <= o) {
              Update(h[i - 1][j + kMaxN][0], h[i][j - 1 + kMaxN][0]);
              Update(h[i - 1][j + kMaxN][1], h[i][j - 1 + kMaxN][1]);
            }
          }
          Update(g[i - 1][j + kMaxN][2], g[i][j - 1 + kMaxN][2]);
        }
        if (j < n - i + 1 && a[i] != -1) {
          Update(g[i - 1][j + kMaxN][0], g[i][j + 1 + kMaxN][0]);
          Update(g[i - 1][j + kMaxN][1], g[i][j + 1 + kMaxN][1]);
          if (j >= 0 && j < o) {
            Update(h[i - 1][j + kMaxN][0], h[i][j + 1 + kMaxN][0]);
            Update(h[i - 1][j + kMaxN][1], h[i][j + 1 + kMaxN][1]);
          }
          Update(g[i - 1][j + kMaxN][2], g[i][j + 1 + kMaxN][2]);
        }
        if (j == o) {
          Update(g[i - 1][j + kMaxN][1], g[i - 1][j + kMaxN][0]);
          g[i - 1][j + kMaxN][0] = 0;
          Update(h[i - 1][j + kMaxN][1], h[i - 1][j + kMaxN][0]);
          h[i - 1][j + kMaxN][0] = 0;
        } else if (j > o << 1) {
          Update(g[i - 1][j + kMaxN][0], g[i - 1][j + kMaxN][1]);
          g[i - 1][j + kMaxN][1] = g[i - 1][j + kMaxN][2] = 0;
          Update(h[i - 1][j + kMaxN][0], h[i - 1][j + kMaxN][1]);
          h[i - 1][j + kMaxN][1] = 0;
        } else if (j < 0) {
          if (u && j == -1 && a[i] != -1) {
            int w = g[i - 1][j + kMaxN][1] - h[i][kMaxN][1];
            w < 0 && (w += kMod);
            Update(g[i - 1][j + kMaxN][2], w);
          } else {
            Update(g[i - 1][j + kMaxN][2], g[i - 1][j + kMaxN][1]);
          }
          g[i - 1][j + kMaxN][0] = g[i - 1][j + kMaxN][1] = 0;
        }
      }
    }
    for (int i = 0; i < n; i += 2) {
      if (a[i + 1] == 1) {
        continue;
      }
      for (int j = -(n - i - 1); j <= n - i - 1; j += 2) {
        if (o >= (j + 1 >> 1)) {
          if (j >= 1) {
            if (o - (j + 1) >= 0) {
              Update(ans, 1LL * f[i][0][o - (j + 1 >> 1)] * (g[i + 1][j + kMaxN][0] + g[i + 1][j + kMaxN][1]));
            } else {
              Update(ans, 1LL * f[i][0][o - (j + 1 >> 1)] * g[i + 1][j + kMaxN][1]);
            }
          }
          Update(ans, 1LL * f[i][0][o - (j + 1 >> 1)] * g[i + 1][j + kMaxN][2]);
        }
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Input(), CalcValid();
  CalcInvalid(0);
  for (int i = 1, j = n; i < j; i++, j--) {
    swap(a[i], a[j]), a[i] = -a[i], a[j] = -a[j];
  }
  CalcInvalid(1);
  cout << ans << '\n';
  return 0;
}
