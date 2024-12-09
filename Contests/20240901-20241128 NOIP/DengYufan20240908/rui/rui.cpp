#include <fstream>
#include <queue>

using namespace std;

ifstream cin("rui.in");
ofstream cout("rui.out");

const int kMaxN = 3e5 + 1, kInf = 1e9;
struct Q {
  int w, x;
  bool operator<(const Q &q) const {
    return w > q.w || w == q.w && x > q.x;
  }
  bool operator==(const Q &q) const {
    return w == q.w && x == q.x;
  }
};
struct F {
  int f, l, r, w;
} f[kMaxN];
int n, m, ans[kMaxN];
bool a[kMaxN];
vector<int> v;
priority_queue<Q> q1, q2;

void Calc1() {
  int s0[kMaxN] = {}, s1[kMaxN] = {};
  for (int i = 1; i <= n; i++) {
    s0[i] = s0[i - 1], s1[i] = s1[i - 1];
    a[i] ? s1[i]++ : s0[i]++;
  }
  for (int i = 0; i <= n; i++) {
    ans[1] = max(ans[1], s0[i] - s1[i] + s1[n]);
  }
}

int GetRoot(int x) { return f[x].f == x ? x : f[x].f = GetRoot(f[x].f); }

void Update() {
  while (!q2.empty() && q1.top() == q2.top()) {
    q1.pop(), q2.pop();
  }
}

void Push(Q x) { q1.push(x); }
void Erase(Q x) { q2.push(x); }
void Pop() { Update(), q1.pop(); }
bool Empty() { return q1.size() == q2.size(); }
Q Top() { return Update(), q1.top(); }

void Calc(int l, int r, int o, int w) {
  if (m - o <= 1) {
    return;
  }
  while (!Empty()) {
    Pop();
  }
  f[l] = {l, l, l, v[l]}, Push({v[l], l});
  for (int i = l + 1; i <= r; i++) {
    f[i] = {i, i, i, v[i]}, Push({v[i], i});
  }
  ans[m - o] = max(ans[m - o], n - w);
  for (int i = 1; i * 2 <= m - o - 2; i++) {
    Q t = Top();
    Pop(), w += t.w;
    if (f[t.x].l == l) {
      int y = GetRoot(f[t.x].r + 1);
      Erase({f[y].w, y}), l = f[y].r + 1;
    } else if (f[t.x].r == r) {
      int y = GetRoot(f[t.x].l - 1);
      Erase({f[y].w, y}), r = f[y].l - 1;
    } else {
      int y = GetRoot(f[t.x].l - 1), z = GetRoot(f[t.x].r + 1);
      Erase({f[y].w, y}), Erase({f[z].w, z});
      f[y].f = f[z].f = t.x;
      f[t.x].w = f[y].w + f[z].w - f[t.x].w;
      f[t.x].l = min(f[t.x].l, min(f[y].l, f[z].l));
      f[t.x].r = max(f[t.x].r, max(f[y].r, f[z].r));
      Push({f[t.x].w, t.x});
    }
    ans[m - o - i * 2] = max(ans[m - o - i * 2], n - w);
  }
}

void CalcAll() {
  for (int i = 1, j = 0; i <= n; i++) {
    if (i == n || a[i] != a[i + 1]) {
      v.push_back(i - j), j = i;
    }
  }
  m = v.size();
  for (int s : {0, 1}) {
    for (int t : {0, 1}) {
      Calc(1 + s, m - 2 - t, s + t + 1, s * v.front() + t * v.back());
    }
  }
  for (int i = 1; i <= n; i++) {
    ans[i] = max(ans[i], ans[i - 1]);
    cout << ans[i] << " \n"[i == n];
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    static char c;
    cin >> c, a[i] = c == '1';
  }
  Calc1(), CalcAll();
  return 0;
}
