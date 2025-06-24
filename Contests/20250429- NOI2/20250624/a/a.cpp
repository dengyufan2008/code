#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 5e5 + 1, kMod = 998244353, kInv2 = kMod + 1 >> 1;
struct V {
  LL f[3];  // 下接重链长度的 k 次方的期望
  LL g;     // 子树内剖分合法的概率
  LL ans;   // 子树内存在重链的贡献
  vector<int> e;
} v[kMaxN];
int n, p, q;
LL pw[kMaxN];

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

void Update(LL &x, LL y) { x = (x + y) % kMod; }

void Init() {
  int a, b;
  cin >> n >> a >> b;
  p = a * Pow(b) % kMod, q = (1 - p + kMod) % kMod;
  for (int i = 2, x; i <= n; i++) {
    cin >> x, v[x].e.push_back(i);
  }
  pw[0] = 1;
  for (int i = 1; i <= n; i++) {
    pw[i] = pw[i - 1] * p % kMod;
  }
}

void Trans(int x) {
  static LL pre[kMaxN], suf[kMaxN];
  int c = v[x].e.size();
  pre[0] = v[v[x].e[0]].g;
  for (int i = 1; i <= c - 1; i++) {
    int y = v[x].e[i];
    pre[i] = pre[i - 1] * v[y].g % kMod;
  }
  suf[c - 1] = v[v[x].e[c - 1]].g;
  for (int i = c - 2; i >= 0; i--) {
    int y = v[x].e[i];
    suf[i] = suf[i + 1] * v[y].g % kMod;
  }

  v[x].f[0] = pre[c - 1] * pw[c] % kMod;
  v[x].g = pre[c - 1] * (pw[c] + c * pw[c - 1] % kMod * q % kMod) % kMod;
  for (int i = 0; i <= c - 1; i++) {
    static LL f[3];
    int y = v[x].e[i];
    f[0] = v[y].f[0], f[1] = (v[y].f[0] + v[y].f[1]) % kMod;
    f[2] = (v[y].f[0] + v[y].f[1] * 2 + v[y].f[2]) % kMod;
    for (int o = 0; o <= 2; o++) {
      LL w = f[o];
      if (i >= 1) {
        w = w * pre[i - 1] % kMod;
      }
      if (i <= c - 2) {
        w = w * suf[i + 1] % kMod;
      }
      w = w * pw[c - 1] % kMod * q % kMod;
      Update(v[x].f[o], w);
    }
  }
  for (int i = 0; i <= c - 1; i++) {
    int y = v[x].e[i];
    {
      LL w = (v[y].f[1] + v[y].f[2]) * kInv2 % kMod;
      if (i >= 1) {
        w = w * pre[i - 1] % kMod;
      }
      if (i <= c - 2) {
        w = w * suf[i + 1] % kMod;
      }
      w = w * (pw[c] + (c - 1) * pw[c - 1] % kMod * q % kMod) % kMod;
      Update(v[x].ans, w);
    }
    {
      LL w = v[y].ans;
      if (i >= 1) {
        w = w * pre[i - 1] % kMod;
      }
      if (i <= c - 2) {
        w = w * suf[i + 1] % kMod;
      }
      w = w * (pw[c] + c * pw[c - 1] % kMod * q % kMod) % kMod;
      Update(v[x].ans, w);
    }
  }
}

void Dp(int x) {
  if (v[x].e.empty()) {
    v[x].f[0] = v[x].g = 1;
    return;
  }
  for (int i : v[x].e) {
    Dp(i);
  }
  Trans(x);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init(), Dp(1);
  LL ans = (v[1].ans + (v[1].f[1] + v[1].f[2]) * kInv2) % kMod;
  cout << (ans + kMod) % kMod << '\n';
  return 0;
}
