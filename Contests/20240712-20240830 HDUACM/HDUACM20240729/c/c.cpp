#include <fstream>
#include <set>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 2e5 + 1;
int t, n, m, k, l, r, a[kMaxN], prime[kMaxN];
bool b[kMaxN];
auto cmp = [](int i, int j) { return a[i] < a[j]; };
set<int, decltype(cmp)> s(cmp);

bool C(int x) {
  int c = m;
  s.clear(), s.insert(0);
  for (int i = 1; i <= n && c; i++) {
    for (int j : s) {
      if (a[i] - a[j] >= x) {
        if (!b[i - j]) {
          c--, s.clear();
          break;
        }
      } else {
        break;
      }
    }
    s.insert(i);
  }
  return !c;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  b[1] = 1;
  for (int i = 2; i < kMaxN; i++) {
    if (!b[i]) {
      prime[++k] = i;
    }
    for (int j = 1; j <= k && i * prime[j] < kMaxN; j++) {
      b[i * prime[j]] = 1;
      if (!(i % prime[j])) {
        break;
      }
    }
  }
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> a[i], a[i] += a[i - 1];
    }
    l = -2e8, r = 2e8;
    while (l <= r) {
      int mid = l + r >> 1;
      if (C(mid)) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    if (r < -2e8) {
      cout << "impossible\n";
    } else {
      cout << r << '\n';
    }
  }
  return 0;
}
