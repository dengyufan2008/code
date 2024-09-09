#include <fstream>
#include <queue>

using namespace std;

ifstream cin("tks.in");
ofstream cout("tks.out");

const int kMaxN = 5e5 + 1;
struct V {
  int c, f, g;
  vector<int> i, o;
} v[kMaxN];
int n, m, k, ansp, answ, a[kMaxN];
struct Q {
  priority_queue<int> q1, q2;

  void Update() {
    while (!q2.empty() && q1.top() == q2.top()) {
      q1.pop(), q2.pop();
    }
  }

  void Push(int x) { q1.push(x); }
  void Erase(int x) { q2.push(x); }
  int Top() { return Update(), q1.top(); }
  bool Empty() { return q1.size() == q2.size(); }
} q;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y, v[x].o.push_back(y), v[y].i.push_back(x);
  }
  for (int i = 1; i <= n; i++) {
    v[i].c = v[i].i.size();
    if (!v[i].c) {
      a[++k] = i;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j : v[a[i]].o) {
      if (!--v[j].c) {
        a[++k] = j;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j : v[a[i]].i) {
      v[a[i]].f = max(v[a[i]].f, v[j].f + 1);
    }
  }
  for (int i = n; i >= 1; i--) {
    for (int j : v[a[i]].o) {
      v[a[i]].g = max(v[a[i]].g, v[j].g + 1);
    }
  }
  for (int i = 1; i <= n; i++) {
    q.Push(v[i].g);
  }
  answ = n;
  for (int i = 1; i <= n; i++) {
    int x = a[i];
    q.Erase(v[x].g);
    for (int j : v[x].i) {
      q.Erase(v[j].f + v[x].g + 1);
    }
    if (!q.Empty() && (answ > q.Top() || answ == q.Top() && ansp > x)) {
      answ = q.Top(), ansp = x;
    }
    q.Push(v[x].f);
    for (int j : v[x].o) {
      q.Push(v[x].f + v[j].g + 1);
    }
  }
  cout << answ << '\n' << ansp << '\n';
  return 0;
}
