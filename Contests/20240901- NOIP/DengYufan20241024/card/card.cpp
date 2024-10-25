#include <fstream>
#define LL long long

using namespace std;

ifstream cin("card.in");
ofstream cout("card.out");

const int kMaxN = 3e5 + 1, kInf = 1e9;
int t, n, o[kMaxN];
bool a[kMaxN];
LL m;

bool C(int mid) {
  int c = 0;
  LL ans = 0;
  for (int i = 1; i <= n; i++) {
    a[i] = o[i] >= mid;
    c += a[i], ans += a[i] & i & 1;
  }
  ans += 1LL * (c - 1 >> 1) * (c + 1 >> 1);
  ans += c & 1 ^ 1 ? c >> 1 : 0;
  for (int i = 1, j = 1, k = 0; i <= n; i = j) {
    for (; j <= n && a[i] == a[j]; j++) {
    }
    if (a[i]) {
      ans += 1LL * (n - c) * ((j - i) >> 1);
      if (j - i & 1) {
        ans += n - c - k + (k + (i & 1 ^ 1) >> 1);
      }
    } else {
      k += j - i;
    }
  }
  return ans >= m;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    int l = kInf, r = -kInf;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> o[i], l = min(l, o[i]), r = max(r, o[i]);
    }
    while (l <= r) {
      int mid = l + r >> 1;
      if (C(mid)) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    cout << r << '\n';
  }
  return 0;
}
