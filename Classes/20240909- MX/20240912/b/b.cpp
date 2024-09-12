#include <fstream>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxL = 60;
int n, m, c[kMaxL];
LL p[kMaxL];
bool o;

void Insert(LL x) {
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (x >> i & 1) {
      if (p[i]) {
        x ^= p[i];
      } else {
        p[i] = x;
        return;
      }
    }
  }
  o = 1;
}

void ReCalc() {
  for (int i = 0; i < kMaxL; i++) {
    for (int j = i + 1; j < kMaxL; j++) {
      if (p[j] >> i & 1) {
        p[j] ^= p[i];
      }
    }
  }
  c[0] = !!p[0];
  for (int i = 1; i < kMaxL; i++) {
    c[i] = c[i - 1] + !!p[i];
  }
}

LL Ask(LL x) {
  LL w = 0;
  x -= o;
  if (x >= (1LL << c[kMaxL - 1])) {
    return -1;
  }
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (p[i]) {
      if ((x < (1LL << c[i] - 1)) ^ (w >> i & 1 ^ 1)) {
        w ^= p[i];
      }
      x &= ~(-1LL << c[i] - 1);
    }
  }
  return w;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    static LL x;
    cin >> x, Insert(x);
  }
  ReCalc(), cin >> m;
  for (int i = 1; i <= m; i++) {
    static LL x;
    cin >> x, cout << Ask(x) << '\n';
  }
  return 0;
}
