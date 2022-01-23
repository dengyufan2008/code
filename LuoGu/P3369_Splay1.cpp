#include <iostream>
#define LL long long

using namespace std;

const int kInf = 1e9;
struct V {
  int c, v, s[2];
} v[100001];
int n, m, s;

void Update(int p) {
  v[p].c = v[v[p].s[0]].c + v[v[p].s[1]].c + (p > 0);
}

void Insert(int &p, int x) {
  if (!p) {
    v[p = ++m] = {1, x};
    return;
  }
  Insert(v[p].s[x >= v[p].v], x);
}

int Replace(int &p) {
  if (!v[p].s[1]) {
    int t = v[p].v;
    p = v[p].s[0];
    return t;
  }
  return Replace(v[p].s[1]);
}

void Delete(int &p, int x) {
  if (v[p].v == x) {
    v[p].v = Replace(v[p].s[0]);
    return;
  }
  Delete(v[p].s[x > v[p].v], x);
}

int FindRank(int p, int x) {
  if (v[p].v == x) {
    return v[v[p].s[0]].c;
  }
  bool t = x > v[p].v;
  return FindRank(v[p].s[t], x) + t * (v[v[p].s[0]].c + 1);
}

int FindVal(int p, int x) {
  if (x == 1) {
    return v[p].v;
  }
  int t = v[v[p].s[0]].c + 1;
  return FindVal(v[p].s[x > t], x - (x > t) * t);
}

int FindPast(int p, int x) {
  if (!p) {
    return -kInf;
  }
  return v[p].v < x ? max(FindPast(v[p].s[1], x), v[p].v) : FindPast(v[p].s[0], x);
}

int FindNext(int p, int x) {
  if (!p) {
    return kInf;
  }
  return v[p].v > x ? min(FindNext(v[p].s[0], x), v[p].v) : FindNext(v[p].s[1], x);
}

int main() {
  cin >> n;
  for (int i = 1, o, x; i <= n; i++) {
    cin >> o >> x;
    if (o == 1) {
      Insert(s, x);
    } else if (o == 2) {
      Delete(s, x);
    } else if (o == 3) {
      cout << FindRank(s, x) + 1 << '\n';
    } else if (o == 4) {
      cout << FindVal(s, x) << '\n';
    } else if (o == 5) {
      cout << FindPast(s, x) << '\n';
    } else {
      cout << FindNext(s, x) << '\n';
    }
  }
  return 0;
}
