#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

const int kMaxN = 1e6 + 1;
int n, ans, a[kMaxN], d[kMaxN], c[kMaxN];
LL m;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    a[x] = i;
  }
  for (int i = 1; i < n; i++) {
    d[min(a[i], a[i + 1])]++, d[max(a[i], a[i + 1])]--;
  }
  for (int i = 1; i <= n; i++) {
    d[i] += d[i - 1], c[d[i]]++;
  }
  for (int i = n - 1; i >= 0; i--) {
    c[i] += c[i + 1];
  }
  for (int i = n; i >= 1; i--) {
    a[c[d[i]]--] = d[i];
  }
  for (int &i = ans; i <= n && m > 0; i += m > 0) {
    m -= a[i];
  }
  cout << (ans > n ? -1 : ans);
  return 0;
}
