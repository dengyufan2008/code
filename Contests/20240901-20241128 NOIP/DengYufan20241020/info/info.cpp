#include <fstream>
#define LL long long

using namespace std;

ifstream cin("info.in");
ofstream cout("info.out");

const int kMaxN = 4e5 + 1, kMaxV = 1e9;
int n, m, t;
LL a[kMaxN], b[kMaxN];

void Init() {
  static int k, s, c[kMaxN];
  cin >> k >> s >> t, t <<= 1;
  for (int i = 1; i <= k; i++) {
    cin >> c[i];
  }
  if (t > kMaxV) {
    cout << 1 << '\n', exit(0);
  }
  for (int i = s - 1; i >= 1; i--) {
    a[++n] = c[s] - c[i];
  }
  for (int i = s + 1; i <= k; i++) {
    b[++m] = c[i] - c[s];
  }
}

pair<int, int> Solve1() {
  int x = 0, y = 0;
  for (int i = 1, j = 1, o = 1; o;) {
    o = 0;
    for (; i <= n && a[i] <= b[y]; i++) {
      if (a[i] < a[x]) {
        x = i, o = 1;
      }
    }
    for (; j <= m && a[x] <= b[j]; j++) {
      if (b[j] > b[y]) {
        y = j, o = 1;
      }
    }
  }
  return {x, y};
}

pair<int, int> Solve2() {
  int x = n, y = m;
  for (int i = n - 1, j = m - 1, o = 1; o;) {
    o = 0;
    for (; i >= 0 && a[i] <= b[y]; i--) {
      if (a[i] <= a[x]) {
        x = i, o = 1;
      }
    }
    for (; j >= 0 && a[x] <= b[j]; j--) {
      if (b[j] >= b[y]) {
        y = j, o = 1;
      }
    }
  }
  return {x, y};
}

bool C(int x) {
  for (int i = 1; i <= n; i++) {
    a[i] = a[i] - 1LL * i * x;
  }
  for (int i = 1; i <= m; i++) {
    b[i] = 1LL * i * x - b[i];
  }
  bool ans = a[n] <= b[m] && Solve1() == Solve2();
  for (int i = 1; i <= n; i++) {
    a[i] = a[i] + 1LL * i * x;
  }
  for (int i = 1; i <= m; i++) {
    b[i] = 1LL * i * x - b[i];
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init();
  int l = 0, r = kMaxV;
  while (l <= r) {
    int mid = l + r >> 1;
    if (C(mid)) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  cout << (l + t - 1) / t << '\n';
  return 0;
}
