#include <algorithm>
#include <cmath>
#include <iostream>
#define LL long long
#define LLL __int128_t

using namespace std;

const int kMaxN = 401, kMaxM = 1e5 + 1, kMaxV = 2e5 + 1, kInf = 1e9;
struct E {
  int a, b;
} e[kMaxN];
struct Q {
  LL x;
  int o;
  pair<LL, LL> ans;  // first + x / second
} q[kMaxM];
int n, m, f[kMaxV];  // 买 i 个物品的最小花费

LL Gcd(LL x, LL y) { return y ? Gcd(y, x % y) : x; }

void Write(LLL x) {
  if (x < 10) {
    putchar('0' + x);
  } else {
    Write(x / 10), putchar('0' + x % 10);
  }
}

void Print(LL x, LL s, LL t) {
  LL g = Gcd(x, t);
  Write(((LLL)s * t + x) / g), putchar(' ');
  Write(t / g), putchar('\n');
}

void Init() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].a >> e[i].b;
  }
  sort(e + 1, e + n + 1, [](E i, E j) {
    return i.a * j.b < i.b * j.a;
  });
  for (int i = 1; i < kMaxV; i++) {
    f[i] = kInf;
    for (int j = 1; j <= n; j++) {
      if (i >= e[j].b) {
        f[i] = min(f[i], f[i - e[j].b] + e[j].a);
      }
    }
  }
  for (int i = kMaxV - 2; i >= 1; i--) {
    f[i] = min(f[i], f[i + 1]);
  }
}

bool Update(pair<LL, LL> &ans, LL x, LL w, LL t) {
  if (((LLL)w * t + x) * ans.second < ((LLL)ans.first * ans.second + x) * t) {
    ans.first = w, ans.second = t;
    return 1;
  }
  return 0;
}

void CalcBig() {
  for (int i = 1; i <= m; i++) {
    static LL x;
    pair<LL, LL> &_ans = q[i].ans;
    cin >> x, q[i].x = x, q[i].o = i;
    LL l = e[1].b * (1 + sqrt(1 + x * 4.0 / e[1].a / e[1].b)) / 2;
    for (int j = 0; j < e[1].b; j++) {
      LL t = l - j;
      if (t < kMaxV) {
        t += (kMaxV - t + e[1].b - 1) / e[1].b * e[1].b;
      }
      LL s = (t - kMaxV) / e[1].b + 1;
      Update(_ans, x, s * e[1].a + f[t - s * e[1].b], t);
    }
  }
}

void Solve(int ql, int qr, int vl, int vr) {
  if (ql > qr || vl == vr) {
    for (int i = ql; i <= qr; i++) {
      Update(q[i].ans, q[i].x, f[vl], vl);
    }
    return;
  }
  int qmid = ql + qr >> 1, vmid;
  pair<LL, LL> ans = {0, 0};
  for (int i = vl; i <= vr; i++) {
    if (Update(ans, q[qmid].x, f[i], i)) {
      vmid = i;
    }
  }
  Update(q[qmid].ans, q[qmid].x, f[vmid], vmid);
  Solve(ql, qmid - 1, vl, vmid);
  Solve(qmid + 1, qr, vmid, vr);
}

void CalcSmall() {
  sort(q + 1, q + m + 1, [](Q i, Q j) {
    return i.x < j.x;
  });
  Solve(1, m, 1, kMaxV - 1);
}

int main() {
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init(), CalcBig(), CalcSmall();
  sort(q + 1, q + m + 1, [](Q i, Q j) {
    return i.o < j.o;
  });
  for (int i = 1; i <= m; i++) {
    Print(q[i].x, q[i].ans.first, q[i].ans.second);
  }
  return 0;
}
