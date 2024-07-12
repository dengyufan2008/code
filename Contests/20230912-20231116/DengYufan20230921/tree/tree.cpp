#include <fstream>
#include <set>
#include <vector>

using namespace std;

ifstream cin("tree.in");
ofstream cout("tree.out");

const int kMaxN = 1e5 + 1;
struct V {
  int w, c;
  vector<int> e;
  multiset<int> s;
} v[kMaxN];
int n;

void S(int f, int x) {
  v[x].c = 1;
  for (int &i : v[x].e) {
    S(x, i);
    v[x].c += v[i].c;
    if (v[v[x].e[0]].c < v[i].c) {
      swap(v[x].e[0], i);
    }
  }
}

void T(int f, int x, int s) {
  if (!v[x].e.empty()) {
    T(x, v[x].e[0], s);
  }
  for (int i = 1; i < v[x].e.size(); i++) {
    T(x, v[x].e[i], v[x].e[i]);
    v[s].s.insert(v[v[x].e[i]].s.begin(), v[v[x].e[i]].s.end());
  }
  auto p = v[s].s.lower_bound(v[x].w);
  if (p != v[s].s.end()) {
    v[s].s.erase(p);
  }
  v[s].s.insert(v[x].w);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1, x; i <= n; i++) {
    cin >> v[i].w >> x;
    v[x].e.push_back(i);
  }
  S(0, 1), T(0, 1, 1);
  cout << v[1].s.size();
  return 0;
}
