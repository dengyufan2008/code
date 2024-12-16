#include <fstream>
#include <vector>

using namespace std;

ifstream cin("g.in");
ofstream cout("g.out");

const int kMaxN = 2e5 + 1;
int n, a[kMaxN];
bool b[kMaxN];
vector<pair<int, int>> ans;

void Swap(int x, int y) {
  swap(a[x], a[y]), a[x] = -a[x], a[y] = -a[y];
  ans.push_back({min(x, y), max(x, y)});
}

void SolveRing() {
  int x = a[1], y = a[x];
  Swap(1, x), Swap(x, y);
  for (; a[x] != -1;) {
    Swap(x, -a[x]);
  }
  Swap(1, y), Swap(1, x);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1, j = 0, p;;) {
    for (i = j + 1; i <= n && b[i]; i++) {
    }
    if (i > n) {
      break;
    }
    b[i] = 1;
    for (p = a[i]; p != i; p = a[p]) {
      b[p] = 1;
    }
    for (j = i + 1; j <= n && b[j]; j++) {
    }
    if (j > n) {
      if (i > 1) {
        j = 1;
      } else {
        SolveRing();
        break;
      }
    }
    b[j] = 1;
    for (p = a[j]; p != j; p = a[p]) {
      b[p] = 1;
    }
    Swap(i, j);
    for (; a[i] != -j;) {
      Swap(i, -a[i]);
    }
    for (; a[j] != -i;) {
      Swap(j, -a[j]);
    }
    Swap(i, j);
  }
  cout << ans.size() << '\n';
  for (auto i : ans) {
    cout << i.first << ' ' << i.second << '\n';
  }
  return 0;
}
