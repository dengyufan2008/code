#include <algorithm>
#include <fstream>

using namespace std;

ifstream cin("j.in");
ofstream cout("j.out");

const int kMaxN = 1e5 + 1;
int t, n, m, k, l, r, a[kMaxN], o[kMaxN];

bool C(int x) {
  int s = 0, c = x - k;
  for (int i = 1; i <= n; i++) {
    if (o[i] <= x && c > 0) {
      s += a[o[i]], c--;
      if (s >= m) {
        return 0;
      }
    }
  }
  return 1;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
      cin >> a[i], o[i] = i;
    }
    sort(o + 1, o + n + 1, [](int i, int j) {
      return a[i] < a[j];
    });
    l = 1, r = n;
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
