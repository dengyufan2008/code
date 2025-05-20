#include <fstream>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 1e5 + 2, kMaxM = 26;
int n, m, a[kMaxN];
int pr[kMaxN][kMaxM], nt[kMaxN][kMaxM];
int po[kMaxN][kMaxM], no[kMaxN][kMaxM];
int sg[kMaxN][kMaxM];  // 定义域: l > 1, r < n
int gs[kMaxN];

void Input() {
  static string s;
  cin >> s, n = s.size();
  for (int i = 1; i <= n; i++) {
    a[i] = s[i - 1] - 'a';
  }
}

void Init() {
  for (int i = 0; i < kMaxM; i++) {
    pr[0][i] = 0, po[0][i] = i;
  }
  for (int i = 1, p; i <= n; i++) {
    copy(&pr[i - 1][0], &pr[i - 1][kMaxM], &pr[i][0]);
    copy(&po[i - 1][0], &po[i - 1][kMaxM], &po[i][0]);
    pr[i][a[i]] = i;
    for (p = 0; po[i][p] != a[i]; p++) {
    }
    for (int j = 0; j < p; j++) {
      swap(po[i][j], po[i][p]);
    }
  }
  for (int i = 0; i < kMaxM; i++) {
    nt[n + 1][i] = n + 1, no[n + 1][i] = i;
  }
  for (int i = n, p; i >= 1; i--) {
    copy(&nt[i + 1][0], &nt[i + 1][kMaxM], &nt[i][0]);
    copy(&no[i + 1][0], &no[i + 1][kMaxM], &no[i][0]);
    nt[i][a[i]] = i;
    for (p = 0; no[i][p] != a[i]; p++) {
    }
    for (int j = 0; j < p; j++) {
      swap(no[i][j], no[i][p]);
    }
  }
  for (int i = n; i > 1; i--) {
    for (int u1 = 0; u1 < kMaxM; u1++) {
      int j = no[i][u1], _nt = nt[i][j];
      if (_nt > n || pr[_nt - 1][a[i - 1]] >= i) {
        sg[i][j] = -1;
        continue;
      }
      static bool b[kMaxM];
      for (int u2 = 0; u2 < u1; u2++) {
        int k = no[i][u2], w = sg[pr[_nt][k] + 1][j];
        for (int p = i; nt[p][k] < _nt; p = nt[p][k] + 1) {  // 可以证明这里是均摊 O(1) 的
          w ^= sg[p][k];
        }
        b[w] = 1;
      }
      sg[i][j] = kMaxM;
      for (int k = kMaxM - 1; k >= 0; k--) {
        if (b[k]) {
          b[k] = 0;
        } else {
          sg[i][j] = k;
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    int _pr = pr[i - 1][a[i]];
    if (_pr == 0) {
      continue;
    }
    gs[i] = gs[_pr] ^ sg[_pr + 1][a[i]];
  }
}

bool Ask(int x, int y) {
  static int l[kMaxM], r[kMaxM];
  for (int u1 = 0; u1 < kMaxM; u1++) {
    int i = no[x][u1], _nt = nt[x][i];
    if (_nt > y) {
      l[i] = -1;
      continue;
    }
    static bool b[kMaxM];
    for (int u2 = 0; u2 < u1; u2++) {
      int j = no[x][u2], w = l[j] ^ sg[pr[_nt][j] + 1][i];
      w ^= gs[nt[x][j]] ^ gs[pr[_nt][j]];
      b[w] = 1;
    }
    l[i] = kMaxM;
    for (int j = kMaxM - 1; j >= 0; j--) {
      if (b[j]) {
        b[j] = 0;
      } else {
        l[i] = j;
      }
    }
  }
  for (int u1 = 0; u1 < kMaxM; u1++) {
    int i = po[y][u1], _pr = pr[y][i];
    if (_pr < x) {
      r[i] = -1;
      continue;
    }
    static bool b[kMaxM];
    for (int u2 = 0; u2 < u1; u2++) {
      int j = po[y][u2], w = r[j] ^ sg[_pr + 1][j];
      w ^= gs[nt[_pr][j]] ^ gs[pr[y][j]];
      b[w] = 1;
    }
    r[i] = kMaxM;
    for (int j = kMaxM - 1; j >= 0; j--) {
      if (b[j]) {
        b[j] = 0;
      } else {
        r[i] = j;
      }
    }
  }
  for (int i = 0; i < kMaxM; i++) {
    if (nt[x][i] > y) {
      continue;
    }
    int w = l[i] ^ r[i];
    w ^= gs[nt[x][i]] ^ gs[pr[y][i]];
    if (!w) {
      return 1;
    }
  }
  return 0;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Input(), Init();
  cin >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    cout << (Ask(x, y) ? "Alice\n" : "Bob\n");
  }
  return 0;
}
