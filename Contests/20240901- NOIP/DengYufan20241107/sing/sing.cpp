#include <fstream>

using namespace std;

ifstream cin("sing.in");
ofstream cout("sing.out");

const int kMaxN = 5e5 + 1;
int t, n, m, k, a[kMaxN], b[kMaxN];

void Solve() {
  cin >> n, m = n, k = 1;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], b[i] = 0;
  }
  for (int i = 1; i <= n; i++) {
    if (a[i] <= n) {
      m = min(m, a[i] - i + 1);
    }
    if (a[i] < i || a[i] < a[i - 1]) {
      cout << "NO\n";
      return;
    }
  }
  if (a[1] == n + 1) {
    cout << "NO\n";
    return;
  }
  for (int i = 1; i < m; i++) {
    b[i] = i;
  }
  b[a[1]] = m;
  for (int i = 1; i < n; i++) {
    for (; k <= n && b[k]; k++) {
    }
    if (!b[i]) {
      cout << "NO\n";
      return;
    } else if (a[i] == a[i + 1]) {
      b[k] = b[i];
    } else if (a[i + 1] <= n) {
      b[a[i + 1]] = b[i];
    } else if (i + 1 == k) {
      cout << "NO\n";
      return;
    } else {
      break;
    }
  }
  for (; k <= n; k++) {
    !b[k] && (b[k] = b[k - 1]);
  }
  cout << "YES\n";
  for (int i = 1; i <= n; i++) {
    cout << b[i] << " \n"[i == n];
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    Solve();
  }
  return 0;
}
