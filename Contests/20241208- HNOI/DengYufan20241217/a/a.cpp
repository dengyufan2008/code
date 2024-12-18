// 挂了，但不想调了
#include <algorithm>
#include <fstream>
#include <queue>
#include <set>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const LL kMod = 1e9 + 7, kInf = 1e18;
const int kMove[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
struct Q {
  int o;    // 方向
  LL t;     // 长度
  LL x, y;  // 最晚时刻被加入的点的坐标
};
int n, m, o;
LL x, y, ans;
char c;
queue<Q> q;

class H {
  multiset<LL> s;

 public:
  void Push(LL x) { s.insert(x); }

  void Erase(LL x) {
    auto p = s.lower_bound(x);
    s.erase(p);
  }

  LL Top(bool o) {  // 1:min 0:max
    if (s.empty()) {
      return o ? kInf : -kInf;
    }
    return o ? *s.begin() : *--s.end();
  }
} h[2];

void Init() {
  o = x = 0, y = n - 1, q.push({o, n, x, y});
  h[0].Push(0), h[0].Push(y), h[1].Push(0);
}

LL Push(LL t) {
  LL __x = x, __y = y;
  LL mn = kInf, _t = t, _x, _y, u[6];
  while (_t && !q.empty()) {
    auto g = q.front();
    LL l = h[o & 1].Top(o & 2);
    LL t1 = o & 1 ? abs(l - x) : abs(l - y);
    if (g.o == 0) {
      h[0].Erase(g.y - g.t + 1), h[0].Erase(g.y);
      h[1].Erase(g.x);
    } else if (g.o == 1) {
      h[1].Erase(g.x - g.t + 1), h[1].Erase(g.x);
      h[0].Erase(g.y);
    } else if (g.o == 2) {
      h[0].Erase(g.y + g.t - 1), h[0].Erase(g.y);
      h[1].Erase(g.x);
    } else {
      h[1].Erase(g.x + g.t - 1), h[1].Erase(g.x);
      h[0].Erase(g.y);
    }
    LL r = h[g.o & 1].Top(g.o & 2 ^ 2);
    LL t2 = -1;
    if (g.o == 0) {
      if (g.y - g.t + 1 <= r) {
        t2 = r - g.y + g.t - 1;
      }
    } else if (g.o == 1) {
      if (g.x - g.t + 1 <= r) {
        t2 = r - g.x + g.t - 1;
      }
    } else if (g.o == 2) {
      if (g.y + g.t - 1 >= r) {
        t2 = g.y + g.t - r - 1;
      }
    } else {
      if (g.x + g.t - 1 >= r) {
        t2 = g.x + g.t - r - 1;
      }
    }
    LL t3 = -1;
    if (t2 != -1 && (o ^ g.o) == 2) {
      if (o & 1) {
        if (o == 3 && g.x - g.t + 1 <= x) {
          t3 = x - g.x + g.t - 1 >> 1;
        } else if (o == 1 && x <= g.x + g.t - 1) {
          t3 = g.x + g.t - 1 - x >> 1;
        }
      } else {
        if (o == 2 && g.y - g.t + 1 <= y) {
          t3 = y - g.y + g.t - 1 >> 1;
        } else if (o == 0 && y <= g.y + g.t - 1) {
          t3 = g.y + g.t - 1 - y >> 1;
        }
      }
    }
    t1 = min(t1, min(_t, g.t)), t1 = max(t1, 1LL);
    t2 = min(t2, min(_t, g.t)), (t2 == -1) && (t2 = kInf), t2 = max(t2, 1LL);
    t3 = min(t3, min(_t, g.t)), (t3 == -1) && (t3 = kInf), t3 = max(t3, 1LL);
    u[0] = _t, u[1] = g.t, u[2] = t1, u[3] = t2, u[4] = t3, u[5] = g.t == 1 ? kInf : g.t - 1, sort(u, u + 6);
    for (int i = 0; i < 6; i++) {
      if (u[i] == t1 || u[i] == t2 || u[i] == t3 || u[i] == g.t - 1) {
        LL uw = h[0].Top(0), rw = h[1].Top(0), dw = h[0].Top(1), lw = h[1].Top(1);
        _x = x + u[i] * kMove[o][0];
        _y = y + u[i] * kMove[o][1];
        uw = max(uw, max(__y + kMove[o][1], _y)), rw = max(rw, max(__x + kMove[o][0], _x));
        dw = min(dw, min(__y + kMove[o][1], _y)), lw = min(lw, min(__x + kMove[o][0], _x));
        if (u[i] < g.t) {
          _x = g.x - (g.t - u[i] - 1) * kMove[g.o][0];
          _y = g.y - (g.t - u[i] - 1) * kMove[g.o][1];
          uw = max(uw, max(g.y, _y)), rw = max(rw, max(g.x, _x));
          dw = min(dw, min(g.y, _y)), lw = min(lw, min(g.x, _x));
        }
        mn = min(mn, (uw - dw + 1) * (rw - lw + 1));
        if (u[i] == t1) {
          t1 = kInf;
        } else if (u[i] == t2) {
          t2 = kInf;
        } else {
          t3 = kInf;
        }
      } else {
        _t -= u[i], x += u[i] * kMove[o][0], y += u[i] * kMove[o][1];
        if (!_t && u[i] < g.t) {
          g.t -= u[i], q.front().t -= u[i];
          if (g.o == 0) {
            h[0].Push(g.y - g.t + 1), h[0].Push(g.y);
            h[1].Push(g.x);
          } else if (g.o == 1) {
            h[1].Push(g.x - g.t + 1), h[1].Push(g.x);
            h[0].Push(g.y);
          } else if (g.o == 2) {
            h[0].Push(g.y + g.t - 1), h[0].Push(g.y);
            h[1].Push(g.x);
          } else {
            h[1].Push(g.x + g.t - 1), h[1].Push(g.x);
            h[0].Push(g.y);
          }
        } else {
          q.pop();
        }
        break;
      }
    }
  }
  if (q.empty()) {
    Init(), mn = min(mn, (LL)n);
  } else {
    q.push({o, t, x, y});
    if (o == 0) {
      h[0].Push(y - t + 1), h[0].Push(y);
      h[1].Push(x);
    } else if (o == 1) {
      h[1].Push(x - t + 1), h[1].Push(x);
      h[0].Push(y);
    } else if (o == 2) {
      h[0].Push(y + t - 1), h[0].Push(y);
      h[1].Push(x);
    } else {
      h[1].Push(x + t - 1), h[1].Push(x);
      h[0].Push(y);
    }
    mn = min(mn, (h[0].Top(0) - h[0].Top(1) + 1) * (h[1].Top(0) - h[1].Top(1) + 1));
  }
  return mn;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  Init();
  for (int i = 1, t; i <= m; i++) {
    cin >> c >> t;
    if (c == 'L') {
      o = o - 1 & 3;
    } else if (c == 'R') {
      o = o + 1 & 3;
    }
    ans = (ans + Push(t)) % kMod;
  }
  cout << ans << '\n';
  return 0;
}
