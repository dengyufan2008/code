#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 40, kMaxM = 3188646;
struct E {
  int c;
  LL w;
  E operator*(int x) { return {c + x, w}; }
  void operator+=(E e) {
    if (c > e.c) {
      c = e.c, w = e.w;
    } else if (c == e.c) {
      w += e.w;
    }
  }
} d[2][kMaxM];
int n, m, a[kMaxN];
bool b[kMaxN];
E *f, *g;
vector<int> l;

void Clear(int x, int q) {
  if (x == n) {
    g[q] = {n * n, 0};
    return;
  }
  int y = x;
  for (; y < n && b[x] == b[y]; y++) {
  }
  if (b[x]) {
    Clear(y, q);
  } else {
    q *= y - x + 1;
    for (int i = 0; i <= y - x; i++) {
      Clear(y, q + i);
    }
  }
}

void S(int x, int p, int q, int w, int c) {
  if (x == n) {
    g[q] += f[p], g[q + w] += f[p] * c;
    return;
  }
  int y = x;
  for (; y < n && b[x] == b[y]; y++) {
  }
  if (b[x]) {
    S(y, p, q, w, c);
  } else if (y <= m) {
    p *= y - x + 1;
    for (int i = 0; i <= y - x; i++) {
      S(y, p + i, p + i, 0, c);
    }
  } else if (x <= m) {
    p *= (m - x + 1) * (y - m), q *= y - x + 1;
    for (int i = 0; i <= m - x; i++) {
      for (int j = 0; j < y - m; j++) {
        S(y, p + j, q + j, 1, c + j);
      }
      p += y - m, q++;
    }
  } else {
    p *= y - x + 1, q *= y - x + 1, w *= y - x + 1;
    for (int i = 0; i <= y - x; i++) {
      S(y, p + i, q + i, w, c + i);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i], a[i]--, b[i] = 1;
  }
  d[0][0] = {0, 1};
  for (int i = 0; i < n; i++) {
    f = d[i & 1], g = d[i & 1 ^ 1];
    m = a[i], b[m] = 0;
    Clear(0, 0), S(0, 0, 0, 0, 0);
  }
  for (int i = 1; i <= n; i++) {
    cout << g[i].c << ' ' << g[i].w << '\n';
  }
  return 0;
}
