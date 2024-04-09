#include <fstream>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 3e5 + 1;
int n, m, k, p[kMaxN], s[kMaxN], v[kMaxN * 48];

void Init() {
  int a[kMaxN], d[kMaxN];
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  fill(&d[1], &d[n] + 1, n + 1);
  for (int i = n; i >= 1; i--) {
    p[i] = d[a[i]], d[a[i]] = i;
  }
}

void Copy(int &p, int q1, int q2, int l, int r, int x) {
  ;
}

void Add(int &p, int l, int r, int _l, int _r, int x) {
  ;
}

int Ask(int p, int l, int r, int x) {
  ;
}

void Calc() {
  for (int i = n; i >= 1; i--) {
    Copy(s[i], s[i + 1], s[p[i] + 1], 1, n, p[i] - 1);
    Add(s[i], 1, n, i, p[i] - 1, 1);
  }
}

void Ans() {
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    cout << Ask(s[x], 1, n, y) << '\n';
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init(), Calc(), Ans();
  return 0;
}
