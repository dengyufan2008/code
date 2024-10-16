#include <fstream>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 1e5 + 1;
int n, m, d[kMaxN], p[kMaxN];
long long k, a[kMaxN];

void Mul(int a[kMaxN], int b[kMaxN]) {
  static int c[kMaxN];
  for (int i = 1; i <= n; i++) {
    c[i] = b[a[i]];
  }
  for (int i = 1; i <= n; i++) {
    a[i] = c[i];
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1, p = 0; i <= n; i++) {
    cin >> a[i], a[i] -= p, p += a[i];
  }
  cin >> m >> k;
  for (int i = 1; i <= n; i++) {
    d[i] = p[i] = i;
  }
  for (int i = 1, x; i <= m; i++) {
    cin >> x, swap(p[x], p[x + 1]);
  }
  for (long long i = 1; i <= k; i <<= 1) {
    if (i & k) {
      Mul(d, p);
    }
    Mul(p, p);
  }
  for (int i = 1; i <= n; i++) {
    a[d[i]] += a[d[i - 1]];
    cout << a[d[i]] << ".0\n";
  }
  return 0;
}
