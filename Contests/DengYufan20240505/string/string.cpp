#include <algorithm>
#include <fstream>
#define LL long long
#define ULL unsigned LL
#define Copy(f, g) copy(f, f + kMaxB, g)

using namespace std;

ifstream cin("string.in");
ofstream cout("string.out");

const int kMaxN = 50001, kMaxB = 225;
const ULL kBase = 15553;
int n, m, a[kMaxN], d[kMaxN], p[kMaxN], q[kMaxN];
int l[kMaxN], s[kMaxN][kMaxB];
LL ans;
ULL w[kMaxN][kMaxB], v[kMaxN * 3][kMaxB], pw[kMaxN];

int W(int l, int x) {
  if (l + x >= n) {
    return -1;
  } else if (p[l + x] > x) {
    return 0;
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
    if (i % kMaxB == kMaxB - 1 || i == n - 1) {
      w[0][i / kMaxB] = t;
      s[0][i / kMaxB] = ++m;
      ULL tt = 0;
      for (int j = i - i % kMaxB; j <= i; j++) {
        tt = tt * kBase + p[j];
        v[m][j - i + i % kMaxB] = tt;
      }
    }
  }
  for (int i = 0; i < n - 1; i++) {
    Copy(w[i], w[i + 1]), Copy(s[i], s[i + 1]);
    if (q[i] < n) {
      for (int j = q[i] / kMaxB; j <= (n - 1) / kMaxB; j++) {
        w[i + 1][j] -= p[q[i]] * pw[min(j * kMaxB + kMaxB, n) - 1 - q[i]];
      }
      Copy(v[s[i + 1][q[i] / kMaxB]], v[++m]), s[i + 1][q[i] / kMaxB] = m;
      for (int j = 0; j + q[i] % kMaxB < kMaxB && q[i] + j < n; j++) {
        v[m][j + q[i] % kMaxB] -= p[q[i]] * pw[j];
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

int Lcp(int x, int y) {
  int l = 0, r = n - max(x, y) - 1;
  while (l <= r) {
    int mid = l + r >> 1;
    if (Hash(x, x + mid) == Hash(y, y + mid)) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return l;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 0; i < n; i++) {
    d[i] = -1, q[i] = n;
  }
  for (int i = 0; i < n; i++) {
    cin >> a[i], a[i]--;
    p[i] = ~d[a[i]] ? i - d[a[i]] : 0;
    d[a[i]] = q[d[a[i]]] = l[i] = i;
  }
  Init(), sort(l, l + n, [](int i, int j) {
    int l = Lcp(i, j);
    return W(i, l) < W(j, l);
  });
  ans = 1LL * n * (n + 1) / 2;
  for (int i = 1; i < n; i++) {
    ans -= Lcp(l[i - 1], l[i]);
  }
  cout << ans << '\n';
  return 0;
}
