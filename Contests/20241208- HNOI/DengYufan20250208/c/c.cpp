#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const LL kMaxN = 3e5 + 1, kMaxM = 1 << 19, kInf = 1e18;
struct Q {
  int u;  // 询问编号
  LL x;   // 值
  LL d;   // 要跳跃的次数
  int o;  // 链的编号
  LL c;   // 到链尾的距离
} q[kMaxN];
int n, m, k;
LL a[kMaxN], ans[kMaxN];

class Bit {
  int c[kMaxM + 1];

 public:
  void Init() {
    for (int i = 1; i <= kMaxM; i++) {
      c[i] = min(i, n) - min(i & i - 1, n);
    }
  }

  int AskVal(int x) {
    int ans = kMaxM;
    for (int i = kMaxM >> 1; i >= 1; i >>= 1) {
      if (c[ans - i] >= x) {
        ans -= i;
      } else {
        x -= c[ans - i];
      }
    }
    return ans;
  }

  int AskRank(int x) {
    int ans = 0;
    for (int i = x; i >= 1; i -= i & -i) {
      ans += c[i];
    }
    return ans;
  }

  void EraseRank(int x) {
    int ans = kMaxM;
    c[ans]--;
    for (int i = kMaxM >> 1; i >= 1; i >>= 1) {
      if (c[ans - i] >= x) {
        ans -= i, c[ans]--;
      } else {
        x -= c[ans - i];
      }
    }
  }

  int Size() { return c[kMaxM]; }
} bit;

void Change() {  // 值 转 链编号和到链尾距离
  sort(q + 1, q + k + 1, [](Q i, Q j) {
    return i.x < j.x;
  });
  int t = k;
  LL c = 0, x = kInf;  // 块内最大的点到链尾距离和值
  bit.Init();
  for (int i = n; i >= 1;) {
    int s = bit.Size();
    LL _c = c + (x - a[i]) / s + 1;
    LL _x = a[i] + (x - a[i]) % s - s;
    for (; t >= 1 && q[t].x > _x; t--) {
      q[t].o = bit.AskVal(s - (x - q[t].x) % s);
      q[t].c = c + (x - q[t].x) / s;
    }
    for (; i >= 1 && a[i] > _x; i--) {
      bit.EraseRank(s - (x - a[i]) % s);
    }
    c = _c, x = _x;
  }
}

void Reflect() {  // 链编号和到链尾距离 转 值
  sort(q + 1, q + k + 1, [](Q i, Q j) {
    return i.c > j.c;
  });
  int t = k;
  LL c = 0, x = kInf;
  bit.Init();
  for (int i = n; i >= 1;) {
    int s = bit.Size();
    LL _c = c + (x - a[i]) / s + 1;
    LL _x = a[i] + (x - a[i]) % s - s;
    for (; t >= 1 && q[t].c < _c; t--) {
      q[t].x = x - (q[t].c - c) * s - s + bit.AskRank(q[t].o);
    }
    for (; i >= 1 && a[i] > _x; i--) {
      bit.EraseRank(s - (x - a[i]) % s);
    }
    c = _c, x = _x;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; i++) {
    static LL x, d;
    cin >> x >> d;
    if (x < a[1]) {
      ans[i] = x;
    } else {
      q[++k] = {i, x, d};
    }
  }
  Change();
  for (int i = 1; i <= k; i++) {
    q[i].c -= q[i].d;
  }
  Reflect();
  for (int i = 1; i <= k; i++) {
    ans[q[i].u] = q[i].x;
  }
  for (int i = 1; i <= m; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
