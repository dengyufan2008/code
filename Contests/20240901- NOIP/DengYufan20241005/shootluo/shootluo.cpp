#include <fstream>
#include <queue>
#define LL long long

using namespace std;

ifstream cin("shootluo.in");
ofstream cout("shootluo.out");

const int kMaxN = 2e5 + 1;
struct V {
  LL w, mx, ans;
  vector<int> e;
} v[kMaxN];
struct Q {
  int m;
  LL s;
  priority_queue<LL> p1, p2;
  priority_queue<LL, vector<LL>, greater<LL>> q1, q2;
  vector<pair<LL, bool>> l;

  void Insert(LL x) {
    l.push_back({x, 1});
    s += x, q1.push(x);
    if (q1.size() - q2.size() > m) {
      p1.push(q1.top()), s -= q1.top(), q1.pop();
    }
  }

  void Delete(LL x) {
    l.push_back({x, 0});
    if (x >= q1.top()) {
      s -= x, q2.push(x);
      while (!q2.empty() && q1.top() == q2.top()) {
        q1.pop(), q2.pop();
      }
      if (!p1.empty()) {
        s += p1.top(), q1.push(p1.top()), p1.pop();
      }
    } else {
      p2.push(x);
      while (!p2.empty() && p1.top() == p2.top()) {
        p1.pop(), p2.pop();
      }
    }
  }

  void Undo(int x) {
    while (x--) {
      if (l.back().second) {
        Delete(l.back().first);
      } else {
        Insert(l.back().first);
      }
      l.pop_back(), l.pop_back();
    }
  }
} q;
int n, r;
LL w;

void S(int f, int x) {
  if (v[x].e.size() == 1) {
    v[x].mx = v[x].w;
    return;
  }
  int mx = 0;
  for (int i : v[x].e) {
    if (i != f) {
      S(x, i), v[x].w += v[i].w, w += v[i].w;
      if (!mx || v[mx].mx < v[i].mx) {
        q.Insert(v[mx].mx), mx = i;
      } else {
        q.Insert(v[i].mx);
      }
    }
  }
  if (f) {
    v[x].mx = v[mx].mx + v[x].w;
  } else {
    v[x].mx = v[mx].mx, q.Insert(v[x].mx);
  }
}

void T(int f, int x, LL w, LL mx) {
  v[x].ans = w - q.s;
  LL mx1 = mx, mx2 = 0;
  for (int i : v[x].e) {
    if (i != f) {
      if (mx1 < v[i].mx) {
        mx2 = mx1, mx1 = v[i].mx;
      } else {
        mx2 = max(mx2, v[i].mx);
      }
    }
  }
  for (int i : v[x].e) {
    if (i != f) {
      q.Delete(v[i].mx), q.Insert(v[i].mx - v[i].w);
      if (v[i].mx == mx1) {
        q.Delete(mx2), q.Insert(mx2 + v[r].w - v[i].w);
        T(x, i, w + v[r].w - v[i].w * 2, mx2 + v[r].w - v[i].w);
      } else {
        q.Delete(mx1), q.Insert(mx1 + v[r].w - v[i].w);
        T(x, i, w + v[r].w - v[i].w * 2, mx1 + v[r].w - v[i].w);
      }
      q.Undo(4);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> q.m;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].w;
  }
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  if (n <= 2) {
    for (int i = 1; i <= n; i++) {
      cout << 0 << '\n';
    }
    return 0;
  }
  for (r = 1; v[r].e.size() == 1; r++) {
  }
  S(0, r), T(0, r, w, 0);
  for (int i = 1; i <= n; i++) {
    cout << v[i].ans << '\n';
  }
  return 0;
}
