#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

const int kInf = 1e9;
struct V {
  int v, c, t, s[2];
} v[3000001];
int n, m, k, s[4];
char o[13];
pair<int, int> a[500001];
vector<bool> l;

void Update(int p) {
  v[p].c = v[v[p].s[0]].c + v[v[p].s[1]].c + (p > 0);
}

void Turn(int &p, bool b) {
  int q = v[p].s[b];
  v[p].s[b] = v[q].s[!b], v[q].s[!b] = p;
  Update(p), Update(q);
  p = q;
}

void Rebalance(int &p) {
  if (v[p].s[0] && v[p].t > v[v[p].s[0]].t) {
    Turn(p, 0);
  } else if (v[p].s[1] && v[p].t > v[v[p].s[1]].t) {
    Turn(p, 1);
  }
}

void Insert(int &p, int x, int y) {
  if (!p) {
    v[p = ++k] = {x, 1, rand()};
  } else {
    Insert(v[p].s[x >= v[p].v], x, y);
  }
  Update(p), Rebalance(p);
}

int Replace(int &p) {
  int t = v[p].v;
  if (!v[p].s[1]) {
    p = v[p].s[0];
  } else {
    t = Replace(v[p].s[1]);
    Update(p);
  }
  return t;
}

void Delete(int &p, int x) {
  if (v[p].v == x) {
    if (!v[p].s[0] || !v[p].s[1]) {
      p = v[p].s[0] + v[p].s[1];
    } else {
      v[p].v = Replace(v[p].s[0]);
    }
  } else {
    Delete(v[p].s[x > v[p].v], x);
  }
  Update(p);
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

int FindMin(int p) {
  if (!v[p].s[0]) {
    return v[p].v;
  }
  return FindMin(v[p].s[0]);
}

int Read() {
  int x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x;
}

int main() {
  // freopen("P1110_7.in", "r", stdin);
  // freopen("P1110_7.out", "w", stdout);
  srand(time(0));
  n = Read(), m = Read();
  for (int i = 1; i <= n; i++) {
    a[i].first = Read();
    a[i].second = -kInf;
    int p = FindPast(s[1], a[i].first + 1);
    if (p != -kInf) {
      Insert(s[3], a[i].first - p, 3);
    }
    int q = FindNext(s[1], a[i].first - 1);
    if (q != kInf) {
      Insert(s[3], q - a[i].first, 3);
    }
    Insert(s[1], a[i].first, 1);
    if (i > 1) {
      Insert(s[2], abs(a[i].first - a[i - 1].first), 2);
    }
  }
  for (int i = 1, x, y; i <= m; i++) {
    scanf("%s", o);
    if (o[0] == 'I') {
      x = Read(), y = Read();
      Insert(s[2], abs(a[x + 1].first - y), 2);
      Insert(s[2], abs((a[x].second == -kInf ? a[x].first : a[x].second) - y), 2);
      if (a[x].second != -kInf) {
        Delete(s[2], abs(a[x + 1].first - a[x].second));
      }
      a[x].second = y;
      int p = FindPast(s[1], y + 1);
      if (p != -kInf) {
        Insert(s[3], y - p, 3);
      }
      int q = FindNext(s[1], y - 1);
      if (q != kInf) {
        Insert(s[3], q - y, 3);
      }
      Insert(s[1], y, 1);
    } else if (o[4] == 'G') {
      int p = FindMin(s[2]);
      cout << p << '\n';
    } else {
      int p = FindMin(s[3]);
      cout << p << '\n';
    }
  }
  return 0;
}
