#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("persona.in");
ofstream cout("persona.out");

const int kMaxN = 5e5 + 1, kMaxV = 1e6;
int n, a[kMaxN][4];
LL ans;

class Bit {
  int d[kMaxV << 1];

 public:
  void Init() { fill(&d[1], &d[kMaxV << 1], 0); }

  void Add(int x) {
    for (int i = x + kMaxV; i >= 1; i -= i & -i) {
      d[i]++;
    }
  }

  int Ask(int x) {
    int ans = 0;
    for (int i = x + kMaxV; i < kMaxV << 1; i += i & -i) {
      ans += d[i];
    }
    return ans;
  }
} bit;

LL Solve2(int o1, int o2, bool u2) {  // u:strictly less or not
  struct E {
    int w, s;
  };
  static E e[kMaxN];
  LL ans = 0;
  for (int i = 1; i <= n; i++) {
    e[i].w = a[i][o1];
    e[i].s = a[i][o2] - a[i][o1];
  }
  sort(e + 1, e + n + 1, [](E i, E j) {
    return i.s < j.s;
  });
  for (int i = 1, j = n; i <= n; i++) {
    for (; j >= 1 && e[i].s + e[j].s >= u2; j--) {
    }
    ans += 1LL * e[i].w * (n - j);
  }
  return ans;
}

LL Solve3(int o1, int o2, int o3, bool u2, bool u3) {
  struct E {
    int w, s, t;
  };
  static E e[kMaxN];
  LL ans = 0;
  for (int i = 1; i <= n; i++) {
    e[i].w = a[i][o1];
    e[i].s = a[i][o2] - a[i][o1];
    e[i].t = a[i][o3] - a[i][o1];
  }
  sort(e + 1, e + n + 1, [](E i, E j) {
    return i.s < j.s;
  });
  bit.Init();
  for (int i = 1, j = n; i <= n; i++) {
    for (; j >= 1 && e[i].s + e[j].s >= u2; j--) {
      bit.Add(e[j].t);
    }
    ans += 1LL * e[i].w * bit.Ask(u3 - e[i].t);
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 4; j++) {
      cin >> a[i][j], ans += a[i][j];
    }
  }
  ans *= n;
  for (int i = 1; i <= n; i++) {
    int mn = a[i][0], mx = a[i][0];
    for (int j = 1; j < 4; j++) {
      mn = min(mn, a[i][j]);
      mx = max(mx, a[i][j]);
    }
    ans -= mn + mx;
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i != j) {
        ans -= Solve2(i, j, i > j);
      }
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = j + 1; k < 4; k++) {
        if (i != j && i != k) {
          ans += Solve3(i, j, k, i > j, i > k);
        }
      }
    }
  }
  cout << ans << '\n';
  return 0;
}
