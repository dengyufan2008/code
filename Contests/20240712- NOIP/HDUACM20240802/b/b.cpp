#include <algorithm>
#include <fstream>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 101;
int t, n, a[kMaxN];

int Gcd(int x, int y) {
  return y ? Gcd(y, x % y) : x;
}

bool C1() {
  for (int i = 2; i <= n; i++) {
    if (a[i] % a[1]) {
      return 0;
    }
  }
  return 1;
}

bool C21() {
  for (int i = 2; i <= n; i++) {
    bool o = 1;
    for (int j = 2; j <= n; j++) {
      if (a[j] % a[1] && a[j] % a[i]) {
        o = 0;
        break;
      }
    }
    if (o) {
      return 1;
    }
  }
  return 0;
}

bool C22() {
  int w = 0;
  for (int i = 2; i <= n; i++) {
    if (a[i] % a[1]) {
      w = Gcd(w, a[i]);
    }
  }
  return !w || a[1] < w;
}

bool C23() {
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      int w = a[j] % a[i], o = 1;
      if (w) {
        for (int k = 1; k <= n; k++) {
          if (j != k && a[k] % w && a[k] % a[j]) {
            o = 0;
            break;
          }
        }
        if (o) {
          return 1;
        }
      }
    }
  }
  return 0;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    if (C1()) {
      cout << n - 1 << '\n';
    } else if (C21() || C22() || C23()) {
      cout << n << '\n';
    } else {
      cout << n + 1 << '\n';
    }
  }
  return 0;
}
