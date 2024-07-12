// 你说
// 为什么会有人浪费大好时光
// 来一个lj oj上卡分块题的常数
// 不如原神启动

#include <cmath>
#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("c.in");
// ofstream cout("c.out");

const int kMaxN = 2e5 + 1, kMaxL = 451, kInf = 1e9;
struct V {
  int et, f, ppt, pblf[kMaxL];
  LL pps, pbsf[kMaxL], pbss[kMaxL];
} v[kMaxN];
int n, m, b, blockn, e[kMaxN];
LL p, ans, bbs[kMaxL][kMaxL];

int Block(int x) { return (x - 1) / b + 1; }

int Next(int x) { return ((x - 1) / b + 1) * b + 1; }

int Last(int x) { return ((x - 1) / b + (x % b == 0)) * b; }

void T(int x) {
  int blockx = Block(x);
  v[x].pbsf[blockx]++;
  v[x].pblf[blockx] = min(v[x].pblf[blockx], x);
  v[x].pbss[blockx]++;
  for (int i = v[x].et; i; i = e[i]) {
    for (int j = 1; j <= blockn; j++) {
      v[i].pbsf[j] += v[x].pbsf[j];
      v[i].pblf[j] = min(v[i].pblf[j], v[x].pblf[j]);
    }
    T(i);
    for (int j = 1; j <= blockn; j++) {
      v[x].pbss[j] += v[i].pbss[j];
    }
  }
}

LL Calc(int x, int l, int t) {
  (v[x].ppt != t) && (v[x].ppt = t) && (v[x].pps = 0);
  if (x < l) {
    return 0;
  } else if (v[x].pps) {
    return v[x].pps;
  }
  return v[x].pps = Calc(v[x].f, l, t) + 1;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  b = sqrt(n), blockn = Block(n);
  for (int i = 2; i <= n; i++) {
    cin >> v[i].f;
    e[i] = v[v[i].f].et, v[v[i].f].et = i;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= blockn; j++) {
      v[i].pblf[j] = kInf;
    }
  }
  T(1);
  for (int i = 1; i <= n; i++) {
    for (int j = 2; j <= blockn; j++) {
      v[i].pbsf[j] += v[i].pbsf[j - 1];
      v[i].pbss[j] += v[i].pbss[j - 1];
    }
    for (int j = blockn - 1; j >= 1; j--) {
      v[i].pblf[j] = min(v[i].pblf[j], v[i].pblf[j + 1]);
    }
    for (int j = 1, blocki = Block(i); j <= blockn; j++) {
      bbs[blocki][j] += v[i].pbsf[j];
    }
  }
  cin >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    ans = 0;
    x = (x ^ p) % n + 1, y = (y ^ p) % n + 1;
    x > y ? swap(x, y) : (void)0;
    int blockx = Block(x), blocky = Block(y);
    if (blockx != blocky) {
      int l = Next(x), r = Last(y), blockl = Block(l), blockr = Block(r);
      for (int j = r + 1; j <= y; j++) {
        ans += v[j].pbsf[blocky] - v[j].pbsf[blockl - 1];
        if (v[j].pblf[blockl] != kInf) {
          ans += Calc(v[v[j].pblf[blockl]].f, x, i);
        }
      }
      for (int j = blockl; j <= blockr; j++) {
        ans += bbs[j][blockr] - bbs[j][blockl - 1];
      }
      for (int j = x; j <= l - 1; j++) {
        ans += v[j].pbss[blockr] - v[j].pbss[blockx - 1];
      }
    } else {
      for (int j = x; j <= y; j++) {
        if (v[j].pblf[blockx] != kInf) {
          ans += Calc(j, x, i);
        }
      }
    }
    cout << (p = ans) << '\n';
  }
  return 0;
}
