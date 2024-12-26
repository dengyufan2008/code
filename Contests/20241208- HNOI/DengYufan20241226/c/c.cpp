#include <fstream>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 13;
int o, a, b, t, n, ans;
bool d[kMaxN];

void S(int t) {
  if (!t) {
    if (n != b) {
      return;
    }
    for (int i = 1; i <= b; i++) {
      if (d[i]) {
        return;
      }
    }
    ans++;
    return;
  }
  int x;
  d[++n] = 1, S(t - 1), n--;
  for (x = n; x >= 1 && !d[x]; x--) {
    d[x] = 1, d[++n] = 0, S(t - 1), d[x] = 0, n--;
  }
  if (x) {
    if (x < n) {
      d[x] = 0, n--, S(t - 1), d[x] = 1, d[++n] = 0;
    } else {
      n--, S(t - 1), d[++n] = 1;
    }
  }
  for (x = n; x >= 1 && !d[x]; x--) {
    d[x] = 1, S(t - 1), d[x] = 0;
  }
  if (x) {
    d[x] = 0, S(t - 1), d[x] = 1;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> o;
  while (o--) {
    cin >> a >> b >> t, n = a, ans = 0;
    for (int i = 1; i <= a; i++) {
      d[i] = 0;
    }
    S(t), cout << ans << '\n';
  }
  return 0;
}
