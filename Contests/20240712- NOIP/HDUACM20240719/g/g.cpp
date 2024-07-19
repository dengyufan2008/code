#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("g.in");
ofstream cout("g.out");

const int kMaxN = 2e5 + 1;
int n, f[kMaxN], g[kMaxN], o[kMaxN];
int d1[kMaxN], d2[kMaxN], ans[kMaxN];
LL s;

void Add1(int x, int y) {
  for (int i = x; i <= n; i += i & -i) {
    d1[i] += y;
  }
}

int Ask1(int x) {
  int ans = 0;
  for (int i = x; i >= 1; i -= i & -i) {
    ans += d1[i];
  }
  return ans;
}

void Add2(int x, int y) {
  for (int i = x; i >= 1; i -= i & -i) {
    d2[i] += y;
  }
}

int Ask2(int x) {
  int ans = 0;
  for (int i = x; i <= n; i += i & -i) {
    ans += d2[i];
  }
  return ans;
}

void Solve(int l, int r) {
  if (l == r) {
    return;
  }
  int mid = l + r >> 1;
  for (int i = l; i <= r; i++) {
    o[i] = i;
  }
  sort(o + l, o + r + 1, [](int i, int j) {
    return f[i] < f[j] || f[i] == f[j] && i > j;
  });
  for (int i = l; i <= r; i++) {
    if (o[i] <= mid) {
      Add1(g[o[i]], 1);
    } else {
      ans[o[i]] -= Ask1(g[o[i]] - 1);
    }
  }
  for (int i = l; i <= r; i++) {
    if (o[i] <= mid) {
      Add1(g[o[i]], -1);
    }
  }
  for (int i = r; i >= l; i--) {
    if (o[i] <= mid) {
      ans[o[i]] += Ask2(g[o[i]] + 1);
    } else {
      Add2(g[o[i]], 1);
    }
  }
  for (int i = r; i >= l; i--) {
    if (o[i] > mid) {
      Add2(g[o[i]], -1);
    }
  }
  Solve(l, mid), Solve(mid + 1, r);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> f[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> g[i];
  }
  Solve(1, n), s = 1LL * n * (n - 1) * (n - 2) / 6;
  for (int i = 1; i <= n; i++) {
    ans[i] += i - 1, s -= 1LL * ans[i] * (ans[i] - 1) / 2;
  }
  cout << s << '\n';
  return 0;
}
