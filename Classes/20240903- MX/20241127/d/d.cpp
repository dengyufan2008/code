#include <fstream>
#include <vector>

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

const int kMaxN = 40001, kMaxM = 20001, kMaxV = 16384, kInf = 1e9;
struct H {
  int f[kMaxV];
  H() { f[0] = 0, fill(&f[1], &f[kMaxV], kInf); }
  void Access(int s, int w) {
    static int g[kMaxV];
    for (int i = 0; i < kMaxV; i++) {
      g[i] = min(f[i] + w, f[i ^ s]);
    }
    for (int i = 0; i < kMaxV; i++) {
      f[i] = g[i];
    }
  }
  int Ask() { return f[0]; }
};
struct V {
  int s, w;
  vector<int> e, q;
} v[kMaxM];
int n, m, ans[kMaxN];
string s;
vector<int> r;
vector<H> h;

int Init(int x) {
  int s = 1, mx = 0;
  for (int &i : v[x].e) {
    int c = Init(i);
    s += c;
    mx < c ? swap(v[x].e[0], i), mx = c : 0;
  }
  return s;
}

void Dp(int x) {
  for (int i : v[x].q) {
    ans[i] = h.back().Ask();
  }
  if (v[x].e.empty()) {
    return h.pop_back();
  }
  int y = v[x].e[0];
  for (int i : v[x].e) {
    if (i != y) {
      static H _h;
      _h = h.back(), _h.Access(v[i].s, v[i].w);
      h.emplace_back(_h), Dp(i);
    }
  }
  h.back().Access(v[y].s, v[y].w), Dp(y);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n, r.emplace_back();
  for (int i = 1; i <= n; i++) {
    cin >> s;
    if (s == "ADD") {
      m++, v[r.back()].e.push_back(m), r.push_back(m);
      cin >> v[m].s >> v[m].w;
    } else {
      r.pop_back();
    }
    v[r.back()].q.push_back(i);
  }
  Init(0), h.emplace_back(), Dp(0);
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
