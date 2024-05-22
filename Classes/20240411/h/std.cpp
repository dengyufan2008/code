#include <bits/stdc++.h>

typedef long long LL;

const int N = 3e5 + 5;

int n;
int st[N], len[N];
int L;
char s[2 * N];

int sa[2 * N << 1], rk[2 * N << 1], tot[2 * N], tp[2 * N], ht[2 * N];
void get_SA() {
  int m = std::max('z', '#');
  auto basic_sort = [&]() {
    for (int i = 1; i <= m; i++) tot[i] = 0;
    for (int i = 1; i <= L; i++) tot[rk[i]]++;
    for (int i = 1; i <= m; i++) tot[i] += tot[i - 1];
    for (int i = L; i >= 1; i--) sa[tot[rk[tp[i]]]--] = tp[i];
  };
  for (int i = 1; i <= L; i++) rk[i] = s[i], tp[i] = i;
  basic_sort();
  for (int i = 1, p = 0; p < L; i <<= 1, m = p) {
    p = 0;
    for (int j = 1; j <= i; j++) tp[++p] = L - i + j;
    for (int j = 1; j <= L; j++)
      if (sa[j] > i) tp[++p] = sa[j] - i;
    basic_sort();
    for (int j = 1; j <= L; j++) tp[j] = rk[j];
    p = rk[sa[1]] = 1;
    for (int j = 2; j <= L; j++)
      rk[sa[j]] = (tp[sa[j - 1]] == tp[sa[j]] && tp[sa[j - 1] + i] == tp[sa[j] + i] ? p : ++p);
  }
  for (int i = 1, k = 0; i <= L; i++) {
    if (rk[i] == 1) {
      ht[rk[i]] = 0;
      continue;
    }
    if (k) k--;
    int j = sa[rk[i] - 1];
    while (i + k <= L && j + k <= L && s[i + k] == s[j + k]) k++;
    ht[rk[i]] = k;
  }
}

struct SparseTable {
  int go[21][2 * N];
  void init() {
    for (int i = 1; i <= L; i++) go[0][i] = ht[i];
    for (int j = 1; j <= 20; j++)
      for (int i = 1; i + (1 << j) - 1 <= L; i++)
        go[j][i] = std::min(go[j - 1][i], go[j - 1][i + (1 << (j - 1))]);
  }
  int get(int l, int r) {
    if (l == r) return std::min(L - sa[l] + 1, L - sa[r] + 1);
    if (l > r) std::swap(l, r);
    int k = 31 ^ __builtin_clz(r - l);
    return std::min(go[k][l + 1], go[k][r - (1 << k) + 1]);
  }
} ST;

int trie[2 * N][26], dep[2 * N], sz[2 * N];
std::vector<int> end[2 * N];
int ctrie;

struct String {
  int l, r;
};
int comp(int i, int j, int k) {
  int lc = ST.get(rk[i], rk[j]);
  if (lc >= k)
    return 0;
  else
    return s[i + lc] < s[j + lc] ? -1 : 1;
}
bool operator<(String x, String y) {
  int lenx = x.r - x.l + 1, leny = y.r - y.l + 1;
  int ret = comp(x.l, y.l, std::min(lenx, leny));
  if (ret) return ret == -1;
  ret = comp(lenx > leny ? x.l + leny : y.l, leny > lenx ? y.l + lenx : x.l, std::max(lenx, leny) - std::min(lenx, leny));
  if (ret) return ret == -1;
  ret = comp(lenx > leny ? y.l : y.l + (leny - lenx), leny > lenx ? x.l : x.l + (lenx - leny), std::min(lenx, leny));
  return ret == -1;
}
int lcp(int i, int j, int k) {
  int lc = ST.get(rk[i], rk[j]);
  if (lc >= k)
    return -1;
  else
    return lc;
}
int lcp(String x, String y) {
  int lenx = x.r - x.l + 1, leny = y.r - y.l + 1;
  int ret = lcp(x.l, y.l, std::min(lenx, leny));
  if (ret != -1) return ret;
  ret = lcp(lenx > leny ? x.l + leny : y.l, leny > lenx ? y.l + lenx : x.l, std::max(lenx, leny) - std::min(lenx, leny));
  if (ret != -1) return ret + std::min(lenx, leny);
  ret = lcp(lenx > leny ? y.l : y.l + (leny - lenx), leny > lenx ? x.l : x.l + (lenx - leny), std::min(lenx, leny));
  if (ret != -1)
    return ret + std::max(lenx, leny);
  else
    return -1;
}

std::vector<int> stk;
std::vector<std::pair<String, LL>> vct;
void dfs(int x) {
  if (!end[x].empty()) {
    for (int y : stk) {
      int j = st[end[x].front()] + len[end[x].front()] - 1;
      vct.push_back({{j - (dep[x] - dep[y]) + 1, j}, 0});
      for (int i : end[x]) {
        auto it = std::lower_bound(end[y].begin(), end[y].end(), i);
        vct.back().second += it - end[y].begin();
        vct.back().second -= end[y].end() - it;
      }
    }
    stk.emplace_back(x);
  }
  for (int i = 0; i < 26; i++)
    if (trie[x][i]) dep[trie[x][i]] = dep[x] + 1, dfs(trie[x][i]);
  if (!end[x].empty()) stk.pop_back();
}

int main() {
  freopen("h.in", "r", stdin);
  freopen("h.ans", "w", stdout);
  scanf("%d", &n);
  st[1] = 1;
  LL base = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%s", s + st[i]);
    len[i] = strlen(s + st[i]);
    s[st[i] + len[i]] = '#';
    st[i + 1] = st[i] + len[i] + 1;
    int now = 0;
    for (int j = st[i]; j <= st[i] + len[i] - 1; j++) {
      for (int k = s[j] - 'a' + 1; k < 26; k++) base += sz[trie[now][k]];
      if (!trie[now][s[j] - 'a']) trie[now][s[j] - 'a'] = ++ctrie;
      now = trie[now][s[j] - 'a'];
      sz[now]++;
    }
    for (int k = 0; k < 26; k++) base += sz[trie[now][k]];
    end[now].emplace_back(i);
  }
  L = st[n] + len[n] - 1;
  get_SA();
  ST.init();
  dfs(0);
  std::sort(vct.begin(), vct.end());
  LL ans = base, sum = 0;
  for (int i = 0; i < (int)vct.size() - 1; i++) {
    sum += vct[i].second;
    int val = lcp(vct[i].first, vct[i + 1].first);
    if (val != -1) ans = std::min(ans, base + sum + val + 1);
  }
  if (!vct.empty()) {
    sum += vct.back().second;
    int val = 0;
    while (vct.back().first.l + val <= vct.back().first.r && s[vct.back().first.l + val] == 'z') val++;
    if (vct.back().first.l + val <= vct.back().first.r) ans = std::min(ans, base + sum + val + 1);
  }
  printf("%lld\n", ans);
  return 0;
}
