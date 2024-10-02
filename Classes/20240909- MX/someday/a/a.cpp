#include <fstream>
#include <vector>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 2e5 + 1, kInf = 1e9;
struct V {
  int f1, g1, f2, g2;  // 0.5, 1, 1.5, 2 条链
  vector<int> e;
} v[kMaxN];
int t, n, mx, ans;

void Update(int &x, int y) { x = max(x, y); }

void T(int x) {
  for (int i : v[x].e) {
    T(i), v[i].f1++, v[i].f2++;

    Update(v[x].g2, v[i].f1 + v[x].f2);
    // Update(v[x].g2, v[i].g1 + v[x].g1);
    Update(v[x].g2, v[i].f2 + v[x].f1);
    Update(v[x].g2, v[i].g2);

    Update(v[x].f2, v[i].f1 + v[x].g1);  // CHICK
    Update(v[x].f2, v[i].g1 + v[x].f1);
    Update(v[x].f2, v[i].f2);

    // Update(v[x].g1, v[i].f1 + v[x].f1);
    Update(v[x].g1, v[i].g1);

    Update(v[x].f1, v[i].f1);

    v[i].f1--, v[i].f2--;
  }
  v[x].f1 = v[x].g1 = -kInf;
  for (int i : v[x].e) {
    v[i].f1++;
    Update(v[x].g2, v[i].g1 + v[x].g1);

    Update(v[x].g1, v[i].f1 + v[x].f1);
    Update(v[x].g1, v[i].g1);

    Update(v[x].f1, v[i].f1);
    v[i].f1--;
  }
  Update(v[x].f2, v[x].f1 - 1);
  Update(v[x].g2, v[x].f2);
  Update(v[x].f1, 0);
  Update(v[x].g1, v[x].f1);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t, fill(&v[0].f1, &v[0].g2 + 1, -kInf);
  while (t--) {
    cin >> n, fill(&v[1], &v[n] + 1, v[0]);
    for (int i = 2, x; i <= n; i++) {
      cin >> x, v[x].e.push_back(i);
    }
    mx = -kInf, ans = 0;
    for (int i : v[1].e) {
      T(i);
      Update(ans, v[i].g1 + mx);
      Update(ans, v[i].g2);
      Update(mx, v[i].g1);
    }
    cout << min(ans + 2, n - 1) << '\n';  // n = 2
  }
  return 0;
}
