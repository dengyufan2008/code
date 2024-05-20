#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <vector>
#define ULL unsigned long long

using namespace std;

ifstream cin("h.in");
ofstream cout("h.out");

const int kMaxN = 3e5 + 1, kMaxL = 19, kBase = 15553;
struct A {
  string s;
  int w, d;
};
int n, m, p[kMaxN], a[kMaxN], r[kMaxN];
int l[kMaxL][kMaxN], lg[kMaxN];
string s[kMaxN], t = "~";
unordered_map<ULL, int> q;
vector<A> v;

void Init() {
  for (int i = 2; i < kMaxN; i++) {
    lg[i] = lg[i >> 1] + 1;
  }
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> s[i], m += s[i].size();
  }
  for (int i = n; i >= 1; i--) {
    static ULL h;
    h = s[i][0];
    for (int j = 1; j < s[i].size(); j++) {
      if (q.count(h)) {
        v.push_back({s[i].substr(j), q[h], 0});
        v.back().d = v.size();
        p[v.back().d] = t.size();
        t += v.back().s;
      }
      h = h * kBase + s[i][j];
    }
    !q.count(h) && (q[h] = 0), q[h]++;
  }
}

void Sort() {
  static int b[kMaxN] = {}, c[kMaxN] = {};
  for (int i = 1; i <= m; i++) {
    a[i] = i;
  }
  sort(a + 1, a + m + 1, [](int i, int j) {
    return t[i] < t[j];
  });
  for (int i = 1; i <= m; i++) {
    r[a[i]] = r[a[i - 1]] + (t[a[i]] != t[a[i - 1]]);
  }
  for (int h = 1; h < m; h <<= 1) {
    fill(&b[1], &b[m] + 1, 0);
    fill(&c[1], &c[m] + 1, 0);
    for (int i = 1; i <= h; i++) {
      b[i] = m - h + i;
    }
    for (int i = 1, j = h; i <= m; i++) {
      if (a[i] > h) {
        b[++j] = a[i] - h;
      }
    }
    for (int i = 1; i <= m; i++) {
      c[r[i]]++;
    }
    for (int i = 1; i <= m; i++) {
      c[i] += c[i - 1];
    }
    for (int i = m; i >= 1; i--) {
      a[c[r[b[i]]]--] = i;
    }
    for (int i = 1; i <= m; i++) {
      b[a[i]] = b[a[i - 1]];
      if (r[a[i]] != r[a[i - 1]] || r[a[i] + h] != r[a[i - 1] + h]) {
        b[a[i]]++;
      }
    }
    copy(&b[1], &b[m] + 1, &r[1]);
  }
}

void CalcL() {
  for (int i = 1; i <= m; i++) {
    if (r[i] < m) {
      l[0][r[i]] = max(l[0][r[i - 1]] - 1, 0);
      for (int &j = l[0][r[i]]; t[i + j] == t[a[r[i] + 1] + j]; j++) {
      }
    }
  }
  for (int i = 1; i < kMaxL; i++) {
    for (int j = 1; j < m; j++) {
      l[i][j] = l[i - 1][j];
      if (j + (1 << i - 1) < m) {
        l[i][j] = min(l[i][j], l[i - 1][j + (1 << i - 1)]);
      }
    }
  }
}

int Lcp(int x, int y) {
  x = r[x], y = r[y];
  x > y ? swap(x, y) : void();
  int o = lg[y - x];
  return min(l[o][x], l[o][y - (1 << o)]);
}

int Lcp(int x, int xl, int y, int yl) {
  return Lcp(p[x] + xl, p[y] + yl);
}

bool Less(int x, int y) {
  if ()
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init(), Sort(), CalcL();
  return 0;
}
