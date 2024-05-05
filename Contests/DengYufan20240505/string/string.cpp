#include <algorithm>
#include <fstream>
#define LL long long
#define ULL unsigned LL

using namespace std;

ifstream cin("string.in");
ofstream cout("string.out");

const int kMaxN = 50000, kMaxB = 225;
const ULL kBase = 15553;
struct V {
  int s[kMaxB];
  ULL w[kMaxB];
} v[kMaxB * kMaxB * 2];
int n, m, a[kMaxN], d[kMaxN], p[kMaxN], q[kMaxN];
int l[kMaxN], r[kMaxN], s[kMaxN], h[kMaxN];
LL ans;
ULL pw[kMaxN];

int W(int l, int x) {
  if (l + x > n) {
    return -1;
  } else if (p[l + x] < l) {
    return 0;
  }
  return p[l + x];
}

void Init() {
  pw[0] = 1;
  for (int i = 1; i < n; i++) {
    pw[i] = pw[i - 1] * kBase;
  }
  ULL w1 = 0;
  for (int i = 0; i < n; i++) {
    w1 = w1 * kBase + p[i];
    if (i % kMaxB == kMaxB - 1) {
      v[0].s[i / kMaxB] = ++m;
      v[0].w[i / kMaxB] = w1;
      ULL w2 = 0;
      for (int j = i - kMaxB + 1; j <= i; j++) {
        w2 = w2 * kBase + p[j];
        v[m].w[j - i + kMaxB - 1] = w2;
      }
    }
  }
  for (int i = 0; i < n - 1; i++) {
    v[++m] = v[s[i]], s[i + 1] = m;
    for (int j = q[i] / kMaxB; j <= n / kMaxB; j++) {
      v[++m] = v[v[s[i]].s[j]], v[s[i]].s[j] = m;
      v[s[i + 1]].w[j] -= i * pw[j * kMaxB + kMaxB - 1 - q[i]];
    }
    for (int j = q[i] % kMaxB; j < kMaxB; j++) {
      v[v[s[i + 1]].s[q[i] / kMaxB]].w[j] -= i * pw[j - q[i] % kMaxB];
    }
  }
}

ULL Hash(int l, int r) {
  ULL ans = v[v[s[l]].s[r / kMaxB]].w[r % kMaxB];
  if (r >= kMaxB) {
    ans += v[s[l]].w[r / kMaxB - 1] * pw[r % kMaxB + 1];
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
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
  ans = 1LL * n * (n - 1) / 2;
  for (int i = 1; i < n; i++) {
    h[r[i]] = max(h[r[i - 1]] - 1, 0);
    for (int &j = h[r[i]]; W(i, j) == W(a[r[i] - 1], j); j++) {
    }
    ans -= h[r[i]];
  }
  cout << ans << '\n';
  return 0;
}
