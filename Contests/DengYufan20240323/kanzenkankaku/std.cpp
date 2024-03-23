#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>
#define ULL unsigned long long

using namespace std;

ifstream cin("kanzenkankaku.in");
ofstream cout("kanzenkankaku.ans");

const int kMaxN = 3001;
int n, m, a[kMaxN];

namespace Sub1 {
const int kMaxN = 302, kBase = 15553;
int ans, b[kMaxN], c[kMaxN], w[kMaxN];
ULL hash[kMaxN][kMaxN][kMaxN][2], pw[kMaxN];
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

bool Ask(int i, int j, int l, int r) {
  ULL s = hash[i][j][r][0] - hash[i][j][l - 1][0] * pw[r - l + 1];
  ULL t = hash[i][j][l][1] - hash[i][j][r + 1][1] * pw[r - l + 1];
  return s == t;
}

bool Check(int x, int l, bool b) {
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      if (Ask(i, j, x - l + 1, x + l - b)) {
        return 1;
      }
    }
  }
  return 0;
}

bool Check1(int x, int l, bool b) {
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      if (Ask(i, j, x - l + 1, x + l - b)) {
        cout << i << ' ' << j << '\n';
        return 1;
      }
    }
  }
  return 0;
}

int main() {
  pw[0] = 1;
  for (int i = 1; i <= n; i++) {
    pw[i] = pw[i - 1] * kBase;
    for (int j = i; j <= n; j++) {
      copy(&a[1], &a[n] + 1, &b[1]);
      fill(&c[1], &c[m] + 1, 0);
      for (int k = i; k <= j; k++) {
        c[a[k]]++;
      }
      for (int k = 2; k <= m; k++) {
        c[k] += c[k - 1];
      }
      for (int k = i; k <= j; k++) {
        b[i + --c[a[k]]] = a[k];
      }
      for (int k = 1; k <= n; k++) {
        hash[i][j][k][0] = hash[i][j][k - 1][0] * kBase + b[k];
      }
      for (int k = n; k >= 1; k--) {
        hash[i][j][k][1] = hash[i][j][k + 1][1] * kBase + b[k];
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    w[i] = i;
  }
  ans = 1;
  shuffle(w + 1, w + n + 1, Rand);
  for (int i = 1; i <= n; i++) {
    int l = ans + 2, r = min(w[i], n - w[i] + 1);
    if (ans < r && Check(w[i], ans + 1, 1)) {
      while (l <= r) {
        int mid = l + r >> 1;
        if (Check(w[i], mid, 1)) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      ans = r;
      cout << w[i] << ' ' << r << ' ' << 1 << ' ' << r * 2 - 1 << '\n';
      Check1(w[i], r, 1);
    }
  }
  ans = ans * 2 - 1;
  shuffle(w + 1, w + n + 1, Rand);
  for (int i = 1; i <= n; i++) {
    int l = ans / 2 + 2, r = min(w[i], n - w[i]);
    if (ans / 2 < r && Check(w[i], ans / 2 + 1, 0)) {
      while (l <= r) {
        int mid = l + r >> 1;
        if (Check(w[i], mid, 0)) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      ans = r * 2;
      cout << w[i] << ' ' << r << ' ' << 0 << ' ' << r * 2 << '\n';
      Check1(w[i], r, 0);
    }
  }
  cout << ans << '\n';
  return 0;
}
}  // namespace Sub1

namespace Sub2 {
const int kMaxN = 3001, kBase = 15553;
int ans, b[kMaxN], c[kMaxN], d[kMaxN], w[kMaxN];
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

void Sort(int i, int j) {
  copy(&a[1], &a[n] + 1, &b[1]);
  fill(&c[1], &c[m] + 1, 0);
  for (int k = i; k <= j; k++) {
    c[a[k]]++;
  }
  for (int k = 2; k <= m; k++) {
    c[k] += c[k - 1];
  }
  for (int k = i; k <= j; k++) {
    b[i + --c[a[k]]] = a[k];
  }
}

bool Ans(int x, int l, bool b) {
  for (int i = 1; i <= l; i++) {
    if (a[x - i + 1] != a[x + i - b]) {
      return 0;
    }
  }
  return 1;
}

bool Check(int x, int l, bool b) {
  int p = 1, q = l;
  for (int &i = p; i <= l; i++) {
    if (a[x - i + 1] != a[x + i - b]) {
      break;
    }
  }
  for (int &i = q; i >= 1; i--) {
    if (a[x - i + 1] != a[x + i - b]) {
      break;
    }
  }
  if (Ans(x, l, b)) {
    return 1;
  }
  Sort(x + p - b, x + q - b);
  if (Ans(x, l, b)) {
    return 1;
  }
  Sort(x - q + 1, x - p + 1);
  if (Ans(x, l, b)) {
    return 1;
  }
  int s[3] = {};
  for (int i = 1; i <= l; i++) {
    s[a[x - i + 1]]++;
  }
  for (int i = x + 1 - b; i <= n; i++) {
    s[a[i]]--;
    if (!s[1] && s[2] <= 0) {
      return 1;
    }
  }
  s[1] = s[2] = 0;
  for (int i = 1; i <= l; i++) {
    s[a[x + i - b]]++;
  }
  for (int i = x; i >= 1; i--) {
    s[a[i]]--;
    if (!s[2] && s[1] <= 0) {
      return 1;
    }
  }
  for (int i = 2, j = x + i - b, k = 0; i <= l; i++) {
    for (; j >= 1 && k < i * 2 - 2 - b; k++) {
      for (j--; j >= 1 && a[j] == 1; j--) {
      }
    }
    if (j < 1) {
      break;
    } else if (a[x + i - b] == 1) {
      int zero = min(x - i - j + 2, l - i + 1);
      if (d[x + i - b + zero - 1] == d[x + i - b - 1] && i + zero > q) {
        return 1;
      }
    } else {
      k++;
    }
  }
  for (int i = 2, j = x - i + 1, k = 0; i <= l; i++) {
    for (; j <= n && k < i * 2 - 2 - b; k++) {
      for (j++; j <= n && a[j] == 2; j++) {
      }
    }
    if (j > n) {
      break;
    } else if (a[x - i + 1] == 2) {
      int one = min(j - i - x + 1 + b, l - i + 1);
      if (d[x - i + 1] == d[x - i + 1 - one] + one && i + one > q) {
        return 1;
      }
    } else {
      k++;
    }
  }
  return 0;
}

int main() {
  for (int i = 1; i <= n; i++) {
    w[i] = i;
    d[i] = d[i - 1] + a[i] - 1;
  }
  ans = 1;
  shuffle(w + 1, w + n + 1, Rand);
  for (int i = 1; i <= n; i++) {
    int l = ans + 2, r = min(w[i], n - w[i] + 1);
    if (ans < r && Check(w[i], ans + 1, 1)) {
      while (l <= r) {
        int mid = l + r >> 1;
        if (Check(w[i], mid, 1)) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      ans = r;
    }
  }
  ans = ans * 2 - 1;
  shuffle(w + 1, w + n + 1, Rand);
  for (int i = 1; i <= n; i++) {
    int l = ans / 2 + 2, r = min(w[i], n - w[i]);
    if (ans / 2 < r && Check(w[i], ans / 2 + 1, 0)) {
      while (l <= r) {
        int mid = l + r >> 1;
        if (Check(w[i], mid, 0)) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      ans = r * 2;
    }
  }
  for (int i = 1, j = 0, k = 0; i <= n; i++) {
    ans = max(ans, a[i] == 1 ? ++j : ++k);
  }
  cout << ans << '\n';
  return 0;
}
}  // namespace Sub2

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  return Sub1::main();
  // if (n <= 300 && m <= 300) {
  //   return Sub1::main();
  // } else if (m <= 2) {
  //   return Sub2::main();
  // }
  return 0;
}
