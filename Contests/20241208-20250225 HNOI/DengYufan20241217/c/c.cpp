#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 3e5 + 1;
int n, m;
LL a[kMaxN], b[kMaxN];
vector<pair<int, LL>> l;

bool Check() {
  static bool o[kMaxN];
  for (int i = 1; i <= n; i++) {
    o[i % m] ^= (a[i] ^ b[i]) & 1;
  }
  for (int i = 1; i < m; i++) {
    if (o[i - 1] ^ o[i]) {
      return 0;
    }
  }
  if (n < m * 2 - 1) {
    bool add = 1, del = 1;
    for (int i = n - m + 1; i < m; i++) {
      if (a[i] + b[i] != a[i + 1] + b[i + 1]) {
        add = 0;
      }
      if (a[i] - b[i] != a[i + 1] - b[i + 1]) {
        del = 0;
      }
    }
    if (!add && !del) {
      return 0;
    }
  }
  return 1;
}

void Solve(int n, int m) {
  // n should be m * 2 - 1
  static LL w[kMaxN];
  w[m] = a[n] + b[n];
  for (int i = 1, j = n; i < j; i++, j--) {
    LL add = (a[i + m - 1] + b[i + m - 1]) + (a[i + m] + b[i + m]);
    LL del = (a[i] - b[i]) - (a[i - 1] - b[i - 1]);
    (i & 1 ^ 1) && (del = -del);
    w[i] = add + del >> 1, w[j] = add - del >> 1;
  }
  for (int i = 1; i <= m; i++) {
    l.push_back({i, w[i]});
  }
  for (int i = m - 1; i >= 1; i--) {
    l.push_back({i, w[m * 2 - i]});
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
  }
  if (!Check()) {
    cout << "No\n";
    return 0;
  } else if (n < m * 2 - 1) {
    bool add = 1;
    for (int i = n - m + 1; i < m; i++) {
      if (a[i] + b[i] != a[i + 1] + b[i + 1]) {
        add = 0;
      }
    }
    if (!add) {
      l.push_back({1, 0});
      for (int i = 1; i <= m; i++) {
        a[i] = -a[i];
      }
    }
    for (int i = n - m + 1, j = m; j <= n; i++, j++) {
      a[i] = a[j], b[i] = b[j];
    }
    Solve(n * 2 - m * 2 + 1, n - m + 1);
  } else {
    // l should be empty
    LL p = 0, w;
    for (int i = n; i > m * 2 - 1; i--) {
      if (i > n - m) {
        w = b[i] - (n - i & 1 ? a[i] : -a[i]);
        l.push_back({i - m + 1, w + p});
      } else {
        w = b[i] + (m & 1 ? a[i] : -a[i]);
        LL q = m & 1 ? l[n - m - i].second : -l[n - m - i].second;
        l.push_back({i - m + 1, w + p - q});
      }
      p = w;
    }
    p = 0;
    for (int i = m + 1; i <= m * 2 - 1; i++) {
      if (i <= n - m + 1) {
        LL w = l[n - m - i + 1].second;
        p += i - m & 1 ? w : -w;
        a[i] = i - m & 1 ? p - a[i] : p + a[i];
      } else {
        a[i] = n - m * 2 + 1 & 1 ? p - a[i] : p + a[i];
      }
    }
    Solve(m * 2 - 1, m);
  }
  cout << "Yes\n";
  cout << l.size() << '\n';
  for (auto i : l) {
    cout << i.first << ' ' << i.first + m - 1 << ' ' << i.second << '\n';
  }
  return 0;
}
