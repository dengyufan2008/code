#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("d.in");
// ofstream cout("d.out");

const int kMaxN = 2e6 + 2, kMod = 998244353;
struct V {
  int p, n;
} v[kMaxN], premid[kMaxN], prelr[kMaxN], sufmid[kMaxN], suflr[kMaxN];
int n, a[kMaxN];
LL fact[kMaxN] = {1}, _fact[kMaxN];
bool pre0[kMaxN], suf0[kMaxN];

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

LL C(int x, int y) { return fact[x] * _fact[y] % kMod * _fact[x - y] % kMod; }

void Solve1() {
  int l = 0, r = 0, p, s[kMaxN] = {};
  for (int i = 1; i <= n; i++) {
    s[i] = s[i - 1];
    if (a[i] < (n + 1 >> 1)) {
      s[i]--;
    } else if (a[i] > (n + 1 >> 1)) {
      s[i]++;
    } else {
      p = i;
    }
  }
  for (int i = 0; i < p; i++) {
    l += !s[i];
  }
  for (int i = p; i <= n; i++) {
    r += !s[i];
  }
  cout << 1 << ' ' << l + r - 1 - !s[p] << ' ' << C(l + r - 2, l - 1);
}

void CalcPre() {
  int c1[kMaxN] = {}, c2[kMaxN] = {};
  bool b[kMaxN];
  v[0].n = 1, v[n + 1].p = n;
  for (int i = 1; i <= n; i++) {
    v[i].p = i - 1, v[i].n = i + 1;
  }
  for (int i = n, j = n >> 1, k = j; i >= 1; i--) {
    if (i & 1) {
      premid[i].p = premid[i].n = j;
    } else {
      premid[i].p = j, premid[i].n = v[j].n;
    }
    v[v[a[i]].p].n = v[a[i]].n, v[v[a[i]].n].p = v[a[i]].p;
    if (j > a[i]) {
      k--;
    } else if (j == a[i]) {
      j = v[j].n;
    }
    for (; k < (i >> 1); k++) {
      j = v[j].n;
    }
    for (; k > (i >> 1); k--) {
      j = v[j].p;
    }
  }
  c1[1]++;
  for (int i = 1; i <= n; i++) {
    if (i & 1) {
      prelr[i].n = ++c2[premid[i].p];
    } else {
      c1[premid[i].p + 1]++, c1[premid[i].n]--;
    }
  }
  for (int i = 1; i <= n; i++) {
    c1[i] += c1[i - 1];
  }
  for (int i = 1; i < n; i += 2) {
    pre0[i] = (b[premid[i].p] |= a[i] == premid[i].p);
    prelr[i].p = c1[premid[i].p];
  }
}

void CalcSuf() {
  int c1[kMaxN] = {}, c2[kMaxN] = {};
  bool b[kMaxN];
  v[0].n = 1, v[n + 1].p = n;
  for (int i = 1; i <= n; i++) {
    v[i].p = i - 1, v[i].n = i + 1;
  }
  for (int i = 1, j = n >> 1, k = j; i <= n; i++) {
    if ((n - i + 1) & 1) {
      sufmid[i].p = sufmid[i].n = j;
    } else {
      sufmid[i].p = j, sufmid[i].n = v[j].n;
    }
    v[v[a[i]].p].n = v[a[i]].n, v[v[a[i]].n].p = v[a[i]].p;
    if (j > a[i]) {
      k--;
    } else if (j == a[i]) {
      j = v[j].n;
    }
    for (; k < ((n - i + 1) >> 1); k++) {
      j = v[j].n;
    }
    for (; k > ((n - i + 1) >> 1); k--) {
      j = v[j].p;
    }
  }
  c1[1]++;
  for (int i = n; i >= 1; i--) {
    if ((n - i + 1) & 1) {
      suflr[i].p = ++c2[sufmid[i].p];
    } else {
      c1[sufmid[i].p + 1]++, c1[sufmid[i].n]--;
    }
  }
  for (int i = 1; i <= n; i++) {
    c1[i] += c1[i - 1];
  }
  for (int i = n; i > 1; i -= 2) {
    suf0[i] = (b[sufmid[i].p] |= a[i] == sufmid[i].p);
    suflr[i].n = c1[sufmid[i].p];
  }
}

void Solve2() {
  CalcPre(), CalcSuf();
  int ans1 = 0;
  LL ans2 = 0;
  for (int i = 1; i < n; i += 2) {
    int _ans1 = prelr[i].p + prelr[i].n - 1 - pre0[i] + suflr[i + 1].p + suflr[i + 1].n - 1 - suf0[i + 1];
    LL _ans2 = C(prelr[i].p + prelr[i].n - 2, prelr[i].p - 1) * C(suflr[i + 1].p + suflr[i + 1].n - 2, suflr[i + 1].p - 1) % kMod * C(_ans1, prelr[i].p + prelr[i].n - 1 - pre0[i]) % kMod;
    if (_ans1 > ans1) {
      ans1 = _ans1, ans2 = _ans2;
    } else if (_ans1 == ans1) {
      ans2 = (ans2 + _ans2) % kMod;
    }
  }
  cout << 2 << ' ' << ans1 << ' ' << ans2;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[n] = Pow(fact[n]);
  for (int i = n; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  if (n & 1) {
    Solve1();
  } else {
    Solve2();
  }
  return 0;
}
