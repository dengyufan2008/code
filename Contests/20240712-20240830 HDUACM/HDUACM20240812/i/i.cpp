#include <fstream>
#define LL long long

using namespace std;

ifstream cin("i.in");
ofstream cout("i.out");

const LL kMaxN = 52, kMod = 1e9 + 7, kInv2 = kMod + 1 >> 1;
int o, n, a[kMaxN], s[kMaxN], t[kMaxN], c[kMaxN], d[kMaxN];
LL w, ans;

void Floor(int x, int y, int &q, int &r) {  // y > 0
  if (x >= 0) {
    q = x / y, r = x % y;
  } else {
    q = (x - y + 1) / y, r = (x % y + y) % y;
  }
}

void Ceil(int x, int y, int &q, int &r) {  // y > 0
  if (x >= 0) {
    q = (x + y - 1) / y, r = x % y;
  } else {
    q = x / y, r = (x % y + y) % y;
  }
}

void Add(int f[kMaxN], int l, int r, int x) {
  for (int i = l; i <= r; i++) {
    f[i] += x;
  }
}

void Calc(int i, int j, int k, int l) {
  if (a[i] == -1) {
    Add(s, i, n, -1), Add(t, 1, i, -1), Add(c, k, n, 1), Add(d, 1, k, 1);
  }
  if (a[j] == -1) {
    Add(s, j, n, -1), Add(t, 1, j, -1), Add(c, l, n, 1), Add(d, 1, l, 1);
  }
  w = kInv2 * (k + l) * (j - i) % kMod;
  for (int p = 1, q, r; p <= n; p++) {
    Floor((l - k) * (p - i), j - i, q, r);
    q = min(q + k - (p > i && p < j && !r), n);
    if (p != i && p != j && a[p] == -1) {
      if (q >= 1) {
        int v = k < l ? q - s[p - 1] - c[q] : q - t[p + 1] - c[q];
        w = v > 0 ? w * v % kMod : 0;
      } else {
        w = 0;
      }
    } else if (a[p] != -1 && a[p] > q) {
      w = 0;
    }
  }
  ans = (ans + w) % kMod, w = kInv2 * (k + l) * (j - i) % kMod;
  for (int p = 1, q, r; p <= n; p++) {
    Ceil((l - k) * (p - i), j - i, q, r);
    q = max(q + k + (p > i && p < j && !r), 1);
    if (p != i && p != j && a[p] == -1) {
      if (q <= n) {
        int v = k < l ? n - q + 1 - t[p + 1] - d[q] : n - q + 1 - s[p - 1] - d[q];
        w = v > 0 ? w * v % kMod : 0;
      } else {
        w = 0;
      }
    } else if (a[p] != -1 && a[p] < q) {
      w = 0;
    }
  }
  ans = (ans - w + kMod) % kMod;
  if (a[i] == -1) {
    Add(s, i, n, 1), Add(t, 1, i, 1), Add(c, k, n, -1), Add(d, 1, k, -1);
  }
  if (a[j] == -1) {
    Add(s, j, n, 1), Add(t, 1, j, 1), Add(c, l, n, -1), Add(d, 1, l, -1);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> o;
  while (o--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i], ~a[i] && (c[a[i]] = d[a[i]] = 1);
    }
    for (int i = 1; i <= n; i++) {
      s[i] = s[i - 1] + (a[i] == -1), c[i] += c[i - 1];
    }
    for (int i = n; i >= 1; i--) {
      t[i] = t[i + 1] + (a[i] == -1), d[i] += d[i + 1];
    }
    for (int i = 1; i <= n; i++) {
      for (int j = i + 1; j <= n; j++) {
        for (int k = 1; k <= n; k++) {
          for (int l = 1; l <= n; l++) {
            if (k != l && (c[k - 1] == c[k] || a[i] == k) && (c[l - 1] == c[l] || a[j] == l) &&
                (a[i] == -1 || a[i] == k) && (a[j] == -1 || a[j] == l)) {
              Calc(i, j, k, l);
            }
          }
        }
      }
    }
    cout << ans << '\n', ans = 0;
    for (int i = 1; i <= n; i++) {
      s[i] = t[i] = c[i] = d[i] = 0;
    }
  }
  return 0;
}
