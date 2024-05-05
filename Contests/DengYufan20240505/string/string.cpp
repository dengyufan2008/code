#include <algorithm>
#include <fstream>
#define LL long long
#define ULL unsigned LL
#define Copy(f, g) copy(f, f + kMaxB, g)

using namespace std;

ifstream cin("string.in");
ofstream cout("string.out");

const int kMaxN = 50000, kMaxB = 225;
const ULL kBase = 15553;
int n, m, a[kMaxN], d[kMaxN], p[kMaxN], q[kMaxN];
int l[kMaxN], r[kMaxN], s[kMaxN][kMaxB], h[kMaxN];
LL ans;
ULL w[kMaxN][kMaxB], v[kMaxN * 3][kMaxB], pw[kMaxN];

int W(int l, int x) {
  if (l + x > n) {
    return -114514;
  } else if (p[l + x] < l) {
    return -1;
  }
  return p[l + x];
}

void Init() {
  pw[0] = 1;
  for (int i = 1; i < n; i++) {
    pw[i] = pw[i - 1] * kBase;
  }
  ULL t = 0;
  for (int i = 0; i < n; i++) {
    t = t * kBase + p[i];
    if (i % kMaxB == kMaxB - 1) {
      w[0][i / kMaxB] = t;
      s[0][i / kMaxB] = ++m;
      ULL tt = 0;
      for (int j = i - kMaxB + 1; j <= i; j++) {
        tt = tt * kBase + p[j];
        v[m][j - i + kMaxB - 1] = tt;
      }
    }
  }
  for (int i = 0; i < n - 1; i++) {
    Copy(w[i], w[i + 1]), Copy(s[i], s[i + 1]);
    for (int o : {p[i] == -1 ? i : -1, q[i] < n ? q[i] : -1}) {
      if (~o) {
        for (int j = o / kMaxB; j <= (n - 1) / kMaxB; j++) {
          w[i + 1][j] -= p[o] * pw[j * kMaxB + kMaxB - 1 - o];
        }
        Copy(v[s[i + 1][o / kMaxB]], v[++m]), s[i + 1][o / kMaxB] = m;
        for (int j = o % kMaxB; j < kMaxB; j++) {
          v[m][j] -= p[o] * pw[j - o % kMaxB];
        }
      }
    }
  }
}

ULL Hash(int l, int r) {
  ULL ans = v[s[l][r / kMaxB]][r % kMaxB];
  if (r >= kMaxB) {
    ans += w[l][r / kMaxB - 1] * pw[r % kMaxB + 1];
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 0; i < n; i++) {
    d[i] = -1, q[i] = n;
  }
  for (int i = 0; i < n; i++) {
    cin >> a[i], p[i] = d[--a[i]];
    d[a[i]] = q[d[a[i]]] = l[i] = i;
  }
  Init(), sort(l, l + n, [](int i, int j) {
    int l = 0, r = n - max(i, j) + 1;
    while (l <= r) {
      int mid = l + r >> 1;
      if (Hash(i, i + mid) == Hash(j, j + mid)) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    return W(i, l) < W(j, l);
  });
  for (int i = 0; i < n; i++) {
    r[l[i]] = i;
  }
  ans = 1LL * n * (n + 1) / 2;
  for (int i = 1; i < n; i++) {
    h[r[i]] = max(h[r[i - 1]] - 1, 0);
    for (int &j = h[r[i]]; W(i, j) == W(a[r[i] - 1], j); j++) {
    }
    ans -= h[r[i]];
  }
  cout << ans << '\n';
  return 0;
}
