#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("mex.in");
ofstream cout("mex.out");

const int kMaxN = 201, kMaxM = 20, kMod = 998244353;
struct V {
  LL f[kMaxN];
  vector<int> e;
} v[kMaxN];
int n, c[kMaxN];
LL f[1 << kMaxM], g[1 << kMaxM];
LL fact[kMaxN], _fact[kMaxN];

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

LL C(int x, int y) {
  return fact[x] * _fact[y] % kMod * _fact[x - y] % kMod;
}

void Del(int fa, int x) {
  static vector<int> e;
  for (int i : v[x].e) {
    if (i != fa && !v[i].e.empty()) {
      e.push_back(i);
    }
  }
  v[x].e.swap(e), e.clear();
}

int CalcB(int x) {
  fill(&c[0], &c[n], 0);
  for (int i : v[x].e) {
    c[v[i].e.size()]++;
  }
  int b = n - 1;
  for (int i = n - 1; i >= 1; i--) {
    c[i] += c[i + 1];
    if (i + c[i] < b + c[b]) {
      b = i;
    }
  }
  if (b + c[b] > kMaxM) {
    cout << "shit " << x << '\n';
    exit(0);
  }
  return b;
}

void T(int fa, int x) {
  for (int i : v[x].e) {
    if (i != fa) {
      if (v[i].e.size() > 1) {
        T(x, i);
      } else {
        v[i].e.clear();
      }
    }
  }
  Del(fa, x);
  int b = CalcB(x), l = c[b], w = c[0] - c[1];
  sort(v[x].e.begin(), v[x].e.end(), [](int i, int j) {
    return v[i].e.size() > v[j].e.size();
  });
  f[0] = 1;
  for (int s = 1; s < 1 << b; s++) {
    f[s] = 0;
  }
  for (int o = l; o < v[x].e.size(); o++) {
    int i = v[x].e[o];
    for (int s = (1 << b) - 1; s >= 0; s--) {
      v[i].f[0] = (v[i].f[0] - 1 + kMod) % kMod;
      for (int j = 0; j <= v[i].e.size(); j++) {
        f[s | 1 << j] = (f[s | 1 << j] + f[s] * v[i].f[j]) % kMod;
      }
    }
  }
  for (int s = 0; s < 1 << b; s++) {
    g[0] = f[s];
    for (int t = 1; t < 1 << l; t++) {
      g[t] = 0;
    }
    for (int i = 0; i <= v[x].e.size(); i++) {
      ;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1]);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  cin >> n;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  if (n == 1) {
    cout << "1\n1\n";
    return 0;
  }
  T(0, 1);
  for (int i = 0; i <= n; i++) {
    cout << v[1].f[i] << '\n';
  }
  return 0;
}
