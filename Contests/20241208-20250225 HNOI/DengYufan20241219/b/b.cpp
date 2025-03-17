#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 1e5 + 1, kMaxL = 17, kMod = 998244353;
struct V {
  int c, d, f[kMaxL];
  LL in1, in2, up1[kMaxL], up2[kMaxL];
  LL out1, out2, down1[kMaxL], down2[kMaxL];
  vector<int> e;
} v[kMaxN];
int n, m;

void Calc1(int f, int x) {
  LL in1 = 0, in2 = 0, up1 = 0, up2 = 0;
  v[x].c = 1, v[x].d = v[f].d + 1, v[x].f[0] = f;
  for (int i : v[x].e) {
    if (i != f) {
      Calc1(x, i), v[x].c += v[i].c;
      in1 = (in1 + v[i].in1 + v[i].c * v[i].up1[0]) % kMod;
      in2 = (in2 + v[i].in2 + v[i].c * v[i].up2[0] + v[i].in1 * v[i].up1[0] * 2) % kMod;
      up1 = (up1 + v[i].up1[0] + 1) % kMod;
      up2 = (up2 + v[i].up2[0] - 1) % kMod;
    }
  }
  v[x].in1 = in1, v[x].in2 = in2;
  v[x].up1[0] = (up1 + 1) % kMod;
  v[x].up2[0] = (up2 + 1 + up1 * v[x].up1[0] * 2 + up1 * 2) % kMod;
}

void Calc2(int f, int x) {
  LL down1 = (v[x].down1[0] + 1) % kMod, down2 = (v[x].down2[0] - 1) % kMod;
  !f && (down1 = down2 = 0);
  for (int i : v[x].e) {
    if (i != f) {
      down1 = (down1 + v[i].up1[0] + 1) % kMod;
      down2 = (down2 + v[i].up2[0] - 1) % kMod;
    }
  }
  for (int i : v[x].e) {
    if (i != f) {
      down1 = (down1 - v[i].up1[0] - 1) % kMod;
      down2 = (down2 - v[i].up2[0] + 1) % kMod;
      v[i].down1[0] = (down1 + 1) % kMod;
      v[i].down2[0] = (down2 + 1 + down1 * v[i].down1[0] * 2 + down1 * 2) % kMod;
      Calc2(x, i);
      down1 = (down1 + v[i].up1[0] + 1) % kMod;
      down2 = (down2 + v[i].up2[0] - 1) % kMod;
    }
  }
}

void Calc3(int f, int x) {
  LL out1 = 0, out2 = 0;
  for (int i : v[x].e) {
    if (i != f) {
      Calc3(x, i);
      out1 = (out1 + v[i].out1 + v[i].c * v[i].down1[0]) % kMod;
      out2 = (out2 + v[i].out2 + v[i].c * v[i].down2[0] + v[i].out1 * v[i].down1[0] * 2) % kMod;
    }
  }
  v[x].out1 = out1, v[x].out2 = out2;
}

int Lca(int x, int y) {
  v[x].d < v[y].d ? swap(x, y) : void();
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].d - (1 << i) >= v[y].d) {
      x = v[x].f[i];
    }
  }
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].f[i] != v[y].f[i]) {
      x = v[x].f[i], y = v[y].f[i];
    }
  }
  return x == y ? x : v[x].f[0];
}

LL Ask(int x, int y) {
  int z = Lca(x, y), xc = v[x].c, yc = v[y].c;
  LL x1 = v[x].in1, x2 = v[x].in2;
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].d - v[z].d >> i & 1) {
      x2 = (x2 + v[x].up2[i] * xc + x1 * v[x].up1[i] * 2) % kMod;
      x1 = (x1 + v[x].up1[i] * xc) % kMod;
      x = v[x].f[i];
    }
  }
  LL y1 = v[y].out1, y2 = v[y].out2;
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[y].d - v[z].d >> i & 1) {
      y2 = (y2 + v[y].down2[i] * yc + y1 * v[y].down1[i] * 2) % kMod;
      y1 = (y1 + v[y].down1[i] * yc) % kMod;
      y = v[y].f[i];
    }
  }
  return ((x2 * yc + y2 * xc + x1 * y1 * 2) % kMod + kMod) % kMod;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  Calc1(0, 1), Calc2(0, 1), Calc3(0, 1);
  for (int i = 1; i < kMaxL; i++) {
    for (int x = 1; x <= n; x++) {
      int y = v[x].f[i - 1];
      v[x].f[i] = v[y].f[i - 1];
      v[x].up1[i] = (v[x].up1[i - 1] + v[y].up1[i - 1]) % kMod;
      v[x].up2[i] = (v[x].up2[i - 1] + v[y].up2[i - 1] + v[x].up1[i - 1] * v[y].up1[i - 1] * 2) % kMod;
      v[x].down1[i] = (v[x].down1[i - 1] + v[y].down1[i - 1]) % kMod;
      v[x].down2[i] = (v[x].down2[i - 1] + v[y].down2[i - 1] + v[x].down1[i - 1] * v[y].down1[i - 1] * 2) % kMod;
    }
  }
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    cout << Ask(x, y) << '\n';
  }
  return 0;
}
