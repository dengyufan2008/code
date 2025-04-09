#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 7.5e4 + 1, kMaxM = 26;
class SAM {
  struct V {
    int f, l, e[kMaxM];
    int g[kMaxM];  // 需要跳 fail 到哪里才能匹配字符 c
    LL s;          // 往后扩展的方案数, 包含空串
    LL w;          // fail 链上所有点往后扩展的方案数之和, 包括根
  } v[kMaxN << 1];
  int m;

  void Insert(string &s) {
    int r = m = 1;
    for (char c : s) {
      int x = c - 'a', p = r;
      v[++m].l = v[p].l + 1;
      for (; p && !v[p].e[x]; p = v[p].f) {
        v[p].e[x] = m;
      }
      if (p) {
        int q = v[p].e[x];
        if (v[p].l + 1 == v[q].l) {
          v[m].f = q, r = m;
        } else {
          v[++m] = v[q], v[m].l = v[p].l + 1;
          for (; p && v[p].e[x] == q; p = v[p].f) {
            v[p].e[x] = m;
          }
          v[q].f = v[m - 1].f = m, r = m - 1;
        }
      } else {
        v[m].f = 1, r = m;
      }
    }
  }

  void CalcS() {
    static int q[kMaxN << 1], in[kMaxN << 1];
    for (int i = 1; i <= m; i++) {
      for (int j = 0; j < kMaxM; j++) {
        v[i].e[j] && in[v[i].e[j]]++;
      }
    }
    int h = 1, t = 1;
    q[1] = 1;
    for (; h <= t; h++) {
      int x = q[h];
      for (int i = 0; i < kMaxM; i++) {
        if (!--in[v[x].e[i]]) {
          q[++t] = v[x].e[i];
        }
      }
    }
    for (int i = m; i >= 1; i--) {
      int x = q[i];
      v[x].s = 1;
      for (int j = 0; j < kMaxM; j++) {
        v[x].s += v[v[x].e[j]].s;
      }
    }
  }

  void CalcWG() {
    static int l[kMaxN << 1];
    for (int i = 1; i <= m; i++) {
      l[i] = i;
    }
    sort(l + 1, l + m + 1, [&](int i, int j) {
      return v[i].l < v[j].l;
    });
    for (int i = 1; i <= m; i++) {
      int x = l[i];
      v[x].w = x == 1 ? v[x].s : v[v[x].f].w + v[x].s * (v[x].l - v[v[x].f].l);
      for (int j = 0; j < kMaxM; j++) {
        if (v[x].e[j]) {
          v[x].g[j] = x;
        } else {
          v[x].g[j] = x == 1 ? 0 : v[v[x].f].g[j];
        }
      }
    }
  }

 public:
  V &operator[](int x) { return v[x]; }

  void Build(string &s) {
    Insert(s), CalcS(), CalcWG();
  }
};

class DS {
  struct A {
    int x, l;
    bool o;  // 是否可以接受下一个字符
  };
  SAM s1, s2;
  vector<A> p;  // 在 s 串中匹配的最长前缀
  vector<A> q;  // 在 t 串中匹配的最长后缀
  vector<A> r;  // s 串匹配不了的部分在 t 串匹配的结果

  bool Try(SAM &s, vector<A> &p, int x) {
    A _p = p.back();
    if (_p.o && s[_p.x].e[x]) {
      p.push_back({s[_p.x].e[x], _p.l + 1, 1});
      return 1;
    } else {
      p.push_back({_p.x, _p.l, 0});
      return 0;
    }
  }

  LL AskCurrent(int x, int l) {
    return s2[x].w - s2[x].s * (s2[x].l - l);
  }

  LL AskFather(int x, int l) {
    if (x != 1) {
      if (l == s2[s2[x].f].l + 1) {
        return AskCurrent(s2[x].f, l - 1);
      } else {
        return AskCurrent(x, l - 1);
      }
    } else {
      return 0;
    }
  }

 public:
  void Init(string &s, string &t) {
    s1.Build(s), s2.Build(t);
    p.push_back({1, 0, 1}), q.push_back({1, 0, 1}), r.push_back({1, 0, 1});
  }

  void Push(char c) {
    int x = c - 'a';
    if (Try(s1, p, x)) {
      r.push_back({1, 0, 1});
    } else {
      Try(s2, r, x);
    }
    A _q = q.back();
    if (s2[_q.x].e[x]) {
      q.push_back({s2[_q.x].e[x], _q.l + 1, 1});
    } else {
      int __q = s2[_q.x].g[x];
      if (__q) {
        q.push_back({s2[__q].e[x], s2[__q].l + 1, 1});
      } else {
        q.push_back({1, 0, 1});
      }
    }
  }

  void Pop() { p.pop_back(), q.pop_back(), r.pop_back(); }

  LL Ask() {
    if (p.size() == 1) {
      return (s1[1].s - 1) * (s2[1].s - 1);
    } else if (!r.back().o) {
      return 0;
    }
    LL ans = p.back().o ? s1[p.back().x].s * (s2[1].s - 1) : 0;  // t 串中选的不能是空串
    if (q.back().l + 1 == q.size()) {
      ans += AskFather(q.back().x, q.back().l);  // s 串中选的不能是空串
    } else {
      ans += AskCurrent(q.back().x, q.back().l);
    }
    if (r.back().x == 1) {  // t 串中选的不能是空串
      ans -= s2[1].s;
    } else {
      ans -= AskFather(r.back().x, r.back().l);
    }
    return ans;
  }
} ds;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  LL n;
  string s, t, ans;
  cin >> s >> t >> n, ds.Init(s, t);
  for (;;) {
    static LL c[kMaxM];
    LL s = ds.Ask();
    for (int i = 0; i < kMaxM; i++) {
      ds.Push('a' + i), c[i] = ds.Ask(), ds.Pop(), s -= c[i];
    }
    if (n <= s) {
      cout << ans << '\n';
      break;
    }
    n -= s;
    for (int i = 0; i < kMaxM; i++) {
      if (n <= c[i]) {
        ans += 'a' + i, ds.Push('a' + i);
        break;
      } else {
        n -= c[i];
      }
    }
  }
  return 0;
}
