#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("h.in");
ofstream cout("h.out");

const int kMaxN = 1e5 + 1, kMod = 1e9 + 7;
struct V {
  int d;
  LL w;
  vector<int> e;
} v[kMaxN];
int t, n, m;

int Log2(int x) {
  int ans = 0;
  for (; x > 1; x >>= 1) {
    ans++;
  }
  return ans;
}

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

void T1(int f, int x) {
  v[x].w = v[f].w + 1LL * (v[x].e.size() - 1) * m + 1;
  for (int i : v[x].e) {
    if (i != f) {
      T1(x, i);
    }
  }
}

void Solve1() {
  int s = 1;
  m = Pow(2, m) - 1, T1(0, 1);
  for (int i = 2; i <= n; i++) {
    if (v[s].w < v[i].w) {
      s = i;
    }
  }
  T1(0, s), s = 1;
  for (int i = 2; i <= n; i++) {
    if (v[s].w < v[i].w) {
      s = i;
    }
  }
  cout << v[s].w << '\n';
}

void T2(int f, int x) {
  v[x].d = v[f].d + 1;
  v[x].w = v[f].w + (v[x].e.size() - 1);
  for (int i : v[x].e) {
    if (i != f) {
      T2(x, i);
    }
  }
}

void Solve2() {
  int s = 1;
  T2(0, 1);
  for (int i = 2; i <= n; i++) {
    if (v[s].w < v[i].w || v[s].w == v[i].w && v[s].d < v[i].d) {
      s = i;
    }
  }
  T2(0, s), s = 1;
  for (int i = 2; i <= n; i++) {
    if (v[s].w < v[i].w || v[s].w == v[i].w && v[s].d < v[i].d) {
      s = i;
    }
  }
  cout << (v[s].w * (Pow(2, m) - 1) + v[s].d) % kMod << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    for (int i = 1; i <= n; i++) {
      v[i].e.clear();
    }
    cin >> n >> m;
    for (int i = 1, x, y; i < n; i++) {
      cin >> x >> y;
      v[x].e.push_back(y), v[y].e.push_back(x);
    }
    if (n == 1) {
      cout << 1 << '\n';
    } else if (m <= Log2(n)) {
      Solve1();
    } else {
      Solve2();
    }
  }
  return 0;
}
