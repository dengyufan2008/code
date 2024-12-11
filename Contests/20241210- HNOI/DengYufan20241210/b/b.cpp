#include <algorithm>
#include <fstream>
#include <queue>
#include <set>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 1e5 + 1, kMaxL = 17, kV = 2e9;
struct Q {
  int l, r, k, o;
} q[kMaxN];
struct E {
  int w, x;
  bool o;  // 1:insert 0:delete
  bool operator<(const E &e) const {
    return w > e.w || w == e.w && x > e.x;
  }
  bool operator==(const E &e) const {
    return w == e.w && x == e.x;
  }
};
int n, m, a[kMaxN], b[kMaxN], ans[kMaxN];

class ST {
  int d[kMaxL][kMaxN], lg[kMaxN];

 public:
  void Init() {
    for (int i = 2; i <= n; i++) {
      lg[i] = lg[i >> 1] + 1;
    }
    for (int i = 1; i <= n; i++) {
      d[0][i] = a[i];
    }
    for (int i = 1; i < kMaxL; i++) {
      for (int j = 1; j <= n; j++) {
        d[i][j] = d[i - 1][j];
        if (j + (1 << i - 1) <= n) {
          d[i][j] = min(d[i][j], d[i - 1][j + (1 << i - 1)]);
        }
      }
    }
  }

  int Ask(int l, int r) {
    if (l > r) {
      return kV;
    } else {
      int o = lg[r - l + 1];
      return min(d[o][l], d[o][r - (1 << o) + 1]);
    }
  }
} mn;

class Bit {
  int d[kMaxN];

 public:
  void Add(int x, int y) {
    for (int i = x; i <= n; i += i & -i) {
      d[i] += y;
    }
  }

  int Ask(int x) {
    int ans = 0;
    for (int i = x; i >= 1; i -= i & -i) {
      ans += d[i];
    }
    return ans;
  }

  int Ask(int l, int r) { return Ask(r) - Ask(l - 1); }
};
Bit delw;        // 减号的贡献
Bit addw;        // 加号的贡献 (放在段首的前一个)
set<int> dels;   // 减号的贡献位置
set<int> adds;   // 加号的贡献位置 (放在段首的前一个)
vector<E> dele;  // 减号的贡献变化位置
vector<E> adde;  // 加号的贡献变化位置
class PQ {
  priority_queue<E> q1, q2;

 public:
  bool Empty() { return q1.size() == q2.size(); }
  void Push(E x) { q1.push(x); }
  void Erase(E x) { q2.push(x); }

  void Pop() {
    while (!q2.empty() && q1.top() == q2.top()) {
      q1.pop(), q2.pop();
    }
    q1.pop();
  }

  E Top() {
    while (!q2.empty() && q1.top() == q2.top()) {
      q1.pop(), q2.pop();
    }
    return q1.top();
  }
};
PQ pq;  // 加法段贡献的时机与位置

int FindPre(set<int> &s, int x) {
  auto p = s.upper_bound(x);
  return p != s.begin() ? *--p : 0;
}

int FindNxt(set<int> &s, int x) {
  auto p = s.lower_bound(x);
  return p != s.end() ? *p : n + 1;
}

int FindBegin(set<int> &s, int l, int r) {
  int x = FindNxt(s, l);
  return x <= r ? x : n + 1;
}

int FindEnd(set<int> &s, int l, int r) {
  int x = FindPre(s, r);
  return x >= l ? x : 0;
}

void CalcE() {
  for (int i = 1; i <= n; i++) {  // + -> -
    int x = b[i];                 // mid >= a[x] << 1
    for (; !pq.Empty() && pq.Top().w <= a[x] << 1; pq.Pop()) {
      adds.insert(pq.Top().x);
      adde.push_back({pq.Top().w, pq.Top().x, 1});
    }
    int y = FindPre(dels, x), z = FindNxt(dels, x);
    if (y >= 1 && z <= n) {
      int w = mn.Ask(y + 1, z - 1) + max(a[y], a[z]);
      if (w <= a[x] << 1) {
        adds.erase(y), adde.push_back({a[x] << 1, y, 0});
      } else {
        pq.Erase({w, y});
      }
    }
    if (y >= 1 && y + 1 < x) {
      int w = mn.Ask(y + 1, x - 1) + max(a[y], a[x]);
      if (w <= a[x] << 1) {
        adds.insert(y), adde.push_back({a[x] << 1, y, 1});
      } else {
        pq.Push({w, y});
      }
    }
    if (z <= n && x + 1 < z) {
      int w = mn.Ask(x + 1, z - 1) + max(a[x], a[z]);
      if (w <= a[x] << 1) {
        adds.insert(x), adde.push_back({a[x] << 1, x, 1});
      } else {
        pq.Push({w, x});
      }
    }
    dels.insert(x), dele.push_back({a[x] << 1, x, 1});
  }
  dels.clear(), adds.clear();
}

void Divide(int ql, int qr, int vl, int vr, int delg, int addg) {  // <g: 执行完了
  static vector<Q> tl, tr;
  if (ql > qr || vl == vr) {
    for (int i = ql; i <= qr; i++) {
      ans[q[i].o] = vl;
    }
    return;
  }

  int mid = (unsigned)vl + vr >> 1;
  for (; delg < dele.size() && dele[delg].w <= mid; delg++) {
    if (dele[delg].o) {
      delw.Add(dele[delg].x, 1), dels.insert(dele[delg].x);
    } else {
      delw.Add(dele[delg].x, -1), dels.erase(dele[delg].x);
    }
  }
  for (; addg < adde.size() && adde[addg].w <= mid; addg++) {
    if (adde[addg].o) {
      addw.Add(adde[addg].x, 1), adds.insert(adde[addg].x);
    } else {
      addw.Add(adde[addg].x, -1), adds.erase(adde[addg].x);
    }
  }

  for (int i = ql; i <= qr; i++) {
    int k = delw.Ask(q[i].l, q[i].r) + addw.Ask(q[i].l, q[i].r);

    int x = FindEnd(adds, q[i].l, q[i].r);
    k -= x != 0 && FindNxt(dels, x + 1) > q[i].r;  // 减去最右端加号段误算的贡献

    if (a[q[i].l] << 1 > mid || a[q[i].r] << 1 > mid) {
      int y = FindBegin(dels, q[i].l, q[i].r);
      int z = FindEnd(dels, q[i].l, q[i].r);
      if (y != n + 1 && z != 0) {
        int w = min(mn.Ask(q[i].l, y - 1), mn.Ask(z + 1, q[i].r));
        k += a[y] + w <= mid && a[z] + w <= mid;  // 加上首尾相连的加号段的贡献
      }
    }

    k >= q[i].k ? tl.push_back(q[i]) : tr.push_back(q[i]);
  }

  int qmid = ql + tl.size();
  for (int i = 0; i < tl.size(); i++) {
    q[ql + i] = tl[i];
  }
  for (int i = 0; i < tr.size(); i++) {
    q[qmid + i] = tr[i];
  }
  tl.clear(), tr.clear();
  Divide(qmid, qr, mid + 1, vr, delg, addg);

  for (delg--; delg >= 0 && dele[delg].w >= vl; delg--) {
    if (dele[delg].o) {
      delw.Add(dele[delg].x, -1), dels.erase(dele[delg].x);
    } else {
      delw.Add(dele[delg].x, 1), dels.insert(dele[delg].x);
    }
  }
  for (addg--; addg >= 0 && adde[addg].w >= vl; addg--) {
    if (adde[addg].o) {
      addw.Add(adde[addg].x, -1), adds.erase(adde[addg].x);
    } else {
      addw.Add(adde[addg].x, 1), adds.insert(adde[addg].x);
    }
  }

  Divide(ql, qmid - 1, vl, mid, ++delg, ++addg);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], b[i] = i;
  }
  for (int i = 1; i <= m; i++) {
    cin >> q[i].l >> q[i].r >> q[i].k, q[i].o = i;
  }
  sort(b + 1, b + n + 1, [](int i, int j) {
    return a[i] < a[j];
  });
  mn.Init(), CalcE(), Divide(1, m, 0, kV, 0, 0);
  for (int i = 1; i <= m; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
