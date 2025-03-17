#include <fstream>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 3e5 + 1, kMod = 998244353, kInv2 = kMod + 1 >> 1;
struct V {
  int f, r;
  LL p;
  bool b;  // 做完之后概率是否依旧独立
} v[kMaxN];
int n, m;
LL ans;

int GetRoot(int x) {
  return v[x].r == x ? x : v[x].r = GetRoot(v[x].r);
}

bool Merge(int x, int y) {
  x = GetRoot(x), y = GetRoot(y);
  if (x != y) {
    v[x].r = y;
    return 1;
  }
  return 0;
}

void S(int x, LL w) {
  if (x > n) {
    ans = (ans + v[n].p * w) % kMod;
  } else if (GetRoot(x) != GetRoot(n)) {
    S(x + 1, w);
  } else if (v[x].b) {
    LL p = v[x].p, q = v[v[x].f].p;
    v[x].p = p * q % kMod, v[v[x].f].p = (1 - (1 - p) * (1 - q)) % kMod;
    S(x + 1, w);
    v[x].p = p, v[v[x].f].p = q;
  } else {
    LL p = v[x].p, q = v[v[x].f].p;
    v[x].p = v[v[x].f].p = 1;  // 钦定都有
    S(x + 1, w * (p * q % kMod) % kMod);
    v[x].p = v[v[x].f].p = 0;  // 钦定都没有
    S(x + 1, w * ((1 - p) * (1 - q) % kMod) % kMod);
    v[x].p = 0, v[v[x].f].p = 1;  // 钦定自己没有, 父亲有
    S(x + 1, w * ((1 - p) * q % kMod + p * (1 - q) % kMod) % kMod);
    v[x].p = p, v[v[x].f].p = q;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    static char c;
    cin >> c;
    if (c == 'C') {
      v[i].p = 1;
    } else if (c == '?') {
      v[i].p = kInv2, m++;
    }
  }
  for (int i = 1; i <= n; i++) {
    cin >> v[i].f, v[i].r = i;
  }
  for (int i = n; i >= 1; i--) {
    v[i].b = Merge(i, v[i].f);
  }
  S(1, 1);
  for (int i = 1; i <= m; i++) {
    ans = ans * 2 % kMod;
  }
  cout << (ans + kMod) % kMod << '\n';
  return 0;
}
