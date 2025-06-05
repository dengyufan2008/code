#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 1e6;
struct A {
  int *p;
  LL w;
} a[kMaxN];
int t, n, m, u[kMaxN];

void Do() {
  static int p[kMaxN];
  for (int i = 0; i < m; i++) {
    p[a[0].p[i]] = i;
  }
  for (int i = 0; i < n * m; i++) {
    u[i] = p[u[i]];
  }
}

LL Calc(int *p) {
  static int d[kMaxN + 1];
  LL ans = 0;
  fill(&d[1], &d[m] + 1, 0);
  for (int i = 0; i < m; i++) {
    for (int j = p[i] + 1; j <= m; j += j & -j) {
      ans += d[j];
    }
    for (int j = p[i] + 1; j >= 1; j -= j & -j) {
      d[j]++;
    }
  }
  return ans;
}

void Sort() {
  for (int i = 0; i < n; i++) {
    a[i].w = Calc(a[i].p);
  }
  sort(a, a + n, [](A i, A j) {
    return i.w > j.w;
  });
}

bool Check() {
  static int p[kMaxN];
  LL t = Calc(a[0].p);
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < m; j++) {
      p[a[i].p[j]] = j;
    }
    for (int j = 0; j < m; j++) {
      a[i - 1].p[j] = p[a[i - 1].p[j]];
    }
    t -= Calc(a[i - 1].p);
  }
  return !t;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m, a[0].p = u;
    for (int i = 1; i < n; i++) {
      a[i].p = a[i - 1].p + m;
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> a[i].p[j], a[i].p[j]--;
      }
    }
    Do(), Sort(), Do(), Sort();
    if (Check()) {
      for (int i = 0; i < n; i++) {
        cout << (a[i].p - u) / m + 1 << " \n"[i + 1 == n];
      }
    } else {
      cout << -1 << '\n';
    }
  }
  return 0;
}
