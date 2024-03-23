#include <fstream>
#define LL long long

using namespace std;

ifstream cin("perm.in");
ofstream cout("perm.out");

const LL kMaxN = 1 << 17;
LL q, n, m, s, ans, a[kMaxN], d[kMaxN], _d[kMaxN], c[kMaxN];

void Sort(LL l, LL r) {
  if (l >= r) {
    return;
  }
  LL mid = l + r >> 1, k = 0, _d[r - l + 1];
  Sort(l, mid), Sort(mid + 1, r);
  for (LL i = l, j = mid + 1; i <= mid || j <= r;) {
    if (i <= mid && (j > r || a[d[i]] < a[d[j]])) {
      _d[k++] = d[i++];
      c[r - l + 1 >> 1] -= r - j + 1;
    } else {
      _d[k++] = d[j++];
      c[r - l + 1 >> 1] += mid - i + 1;
      s += mid - i + 1;
    }
  }
  for (LL i = 0; i < k; i++) {
    d[l + i] = _d[i];
  }
}

int main() {
  cin >> q >> q;
  while (q--) {
    cin >> n;
    m = 1 << n, ans = kMaxN * kMaxN;
    for (LL i = 0; i < m; i++) {
      cin >> a[i];
    }
    for (LL i = 0; i < n; i++) {
      for (LL j = 0; j < m; j++) {
        d[j] = j >> i | (j & ((1 << i) - 1)) << n - i;
        _d[j] = d[j], c[j] = 0;
      }
      s = 0, Sort(0, m - 1);
      for (LL j = 0; j < n; j++) {
        if (c[1 << j] > 0) {
          s -= c[1 << j];
          for (LL k = 0; k < m; k++) {
            _d[k] ^= 1 << j;
          }
        }
      }
      ans = min(ans, s);
    }
    cout << ans << '\n';
  }
  return 0;
}
