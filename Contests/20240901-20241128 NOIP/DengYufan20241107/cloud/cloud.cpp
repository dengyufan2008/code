#include <fstream>
#define LL long long

using namespace std;

ifstream cin("cloud.in");
ofstream cout("cloud.out");

const int kMaxN = 24;
int n, f[1 << kMaxN];
LL a[1 << kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[1 << i];
  }
  for (int i = n - 1; i > 0; i--) {
    a[1 << i] -= a[1 << i - 1];
  }
  for (int s = 0; s < 1 << n; s++) {
    if (s != (s & -s)) {
      a[s] = a[s ^ (s & -s)] + a[s & -s];
    }
  }
  for (int s = 0; s < 1 << n; s++) {
    f[s] += !a[s];
    for (int t = (1 << n) - 1 ^ s; t; t ^= t & -t) {
      f[s | t & -t] = max(f[s | t & -t], f[s]);
    }
  }
  cout << n - f[(1 << n) - 1] + 1 << '\n';
  return 0;
}
