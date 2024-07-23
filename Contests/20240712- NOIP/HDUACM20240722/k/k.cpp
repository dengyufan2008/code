// by wls
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, LA = 1e5 + 10, LC = 1e4 + 10;
int n, la, lc;
struct node {
  int nxt[26], fail;
} t[N];
int tot, bk[N];
void insert(char *s, int id) {
  int l = strlen(s), u = 0;
  for (int i = 0; i < l; i++) {
    int ch = s[i] - 'a';
    if (!t[u].nxt[ch]) t[u].nxt[ch] = ++tot;
    u = t[u].nxt[ch];
  }
  bk[id] = u;
}
int q[N];
void build_fail() {
  static int l = 0, r = 0;
  q[l = r = 0] = 0;
  while (l <= r) {
    int u = q[l++];
    for (int i = 0; i < 26; i++) {
      int v = t[u].nxt[i];
      if (!v) continue;
      q[++r] = v;
      if (u) {
        int w = t[u].fail;
        while (w && !t[w].nxt[i]) w = t[w].fail;
        t[v].fail = t[w].nxt[i];
      }
    }
  }
}
char s[N], sA[LA], sC[LC];
string s0[N];
int ans[N];
void work() {
  int l = strlen(sA), u = 0;
  for (int i = 0; i < l; i++) {
    int ch = sA[i] - 'a';
    while (u && !t[u].nxt[ch]) u = t[u].fail;
    u = t[u].nxt[ch];
    ans[u] += 1;
  }
  for (int i = tot; i >= 0; i--) ans[t[q[i]].fail] += ans[q[i]];
}

int nxt[N];
void init() {
  nxt[0] = -1;
  for (int i = 1, j = -1; i < lc; i++) {
    while (j != -1 && sC[j + 1] != sC[i]) j = nxt[j];
    if (sC[j + 1] == sC[i]) ++j;
    nxt[i] = j;
  }
}
bool kmp(const char s[]) {
  int l = strlen(s);
  for (int i = 0, j = -1; i < l; i++) {
    while (j != -1 && sC[j + 1] != s[i]) j = nxt[j];
    if (sC[j + 1] == s[i]) ++j;
    if (j == lc - 1) {
      return 1;
      // j = nxt[j];
    }
  }
  return 0;
}

void clear() {
  for (int i = 0; i <= tot; i++) ans[i] = 0;
  for (int i = 0; i <= tot; i++) t[i] = node();
  tot = 0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n;
    cin >> sA >> sC;
    la = strlen(sA), lc = strlen(sC);
    for (int i = 1; i <= n; i++) {
      cin >> s >> s0[i];
      insert(s, i);
    }
    build_fail(), work();
    init();
    for (int i = 1; i <= n; i++) {
      if (kmp(s0[i].c_str()) && ans[bk[i]]) cout << i << ' ';
    }
    cout << '\n';

    clear();
  }
  return 0;
}
