#include <algorithm>
#include <fstream>

using namespace std;

ifstream cin("i.in");
ofstream cout("i.out");

const int kMaxN = 1e5 + 1;
int n, a[kMaxN];
bool b[kMaxN];

int Gcd(int x, int y) { return y ? Gcd(y, x % y) : x; }

bool C() {
  int d = 0, p = -1, q = 0;
  for (int i = 1; i <= n; i++) {
    if (!b[i]) {
      if (p != -1) {
        d = Gcd(d, a[i] - p);
      }
      p = a[i];
    }
  }
  p = -1;
  for (int i = 1; i <= n; i++) {
    if (p != -1 && a[i] - p == d && b[i]) {
      if (q) {
        b[i] = 0, p = a[i];
      } else if (i == n || a[i] != a[i + 1]) {
        q = i, b[i] = 0, p = a[i];
      }
    } else if (!b[i]) {
      if (p != -1 && a[i] - p != d) {
        return 0;
      }
      p = a[i];
    }
  }
  return 1;
}

void Print() {
  int c = 0;
  for (int i = 1; i <= n; i++) {
    c += b[i];
  }
  if (c == n) {
    c--, b[n] = 0;
  }
  cout << c << '\n';
  for (int i = 1; i <= n; i++) {
    if (b[i]) {
      cout << a[i] << ' ';
    }
  }
  cout << '\n';
  cout << n - c << '\n';
  for (int i = 1; i <= n; i++) {
    if (!b[i]) {
      cout << a[i] << ' ';
    }
  }
  cout << '\n';
}

bool Calc1() {
  fill(&b[1], &b[n] + 1, 0), b[1] = b[2] = 1;
  int d = a[2] - a[1], p = a[2];
  for (int i = 3; i <= n; i++) {
    if (a[i] - p == d) {
      b[i] = 1, p = a[i];
    } else if (a[i] - p > d) {
      break;
    }
  }
  return C() ? Print(), 1 : 0;
}

bool Calc2() {
  fill(&b[1], &b[n] + 1, 0), b[1] = b[3] = 1;
  int d = a[3] - a[1], p = a[3];
  for (int i = 4; i <= n; i++) {
    if (a[i] - p == d) {
      b[i] = 1, p = a[i];
    } else if (a[i] - p > d) {
      break;
    }
  }
  return C() ? Print(), 1 : 0;
}

bool Calc3() {
  fill(&b[1], &b[n] + 1, 0), b[2] = b[3] = 1;
  int d = a[3] - a[2], p = a[3];
  for (int i = 4; i <= n; i++) {
    if (a[i] - p == d) {
      b[i] = 1, p = a[i];
    } else if (a[i] - p > d) {
      break;
    }
  }
  return C() ? Print(), 1 : 0;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  sort(a + 1, a + n + 1);
  if (n <= 3) {
    cout << 1 << '\n';
    cout << a[1] << " \n";
    cout << n - 1 << '\n';
    for (int i = 2; i <= n; i++) {
      cout << a[i] << ' ';
    }
    cout << '\n';
  } else if (!Calc1() && !Calc2() && !Calc3()) {
    cout << -1 << '\n';
  }
  return 0;
}
/*
几个例子:
11
0 3 6 8 9 12 13 15 18 23 28

8
0 6 10 12 14 16 18 20

*/
