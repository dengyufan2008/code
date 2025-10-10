#include <fstream>
#include <vector>

#include "testlib.h"
#define LL long long

using namespace std;

ifstream cin("collect.in");
ofstream cout("collect.out");

const LL kMaxN = 1e6 + 1, kInf = 1e18;
struct V {
  int o;
  LL w, t;
  vector<pair<int, int>> e;
} v[kMaxN];
int n, m, o;
LL w;
vector<int> l;

LL S(int x, int o) {
  LL w = 0;
  v[x].o = o;
  for (auto i : v[x].e) {
    if (!v[i.first].o) {
      w += i.second + S(i.first, o);
    }
  }
  return w;
}

int main(int argc, char *argv[]) {
  registerTestlibCmd(argc, argv);
  n = inf.readInt(), m = inf.readInt();
  for (int i = 1, x, y, z; i <= m; i++) {
    x = inf.readInt(), y = inf.readInt(), z = inf.readInt();
    v[x].w += z, v[x].e.push_back({y, z});
    v[y].w += z, v[y].e.push_back({x, z});
  }
  w = kInf;
  for (int i = 1; i <= n; i++) {
    if (!v[i].o) {
      LL _w = S(i, i);
      if (w > _w) {
        o = i, w = _w;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    v[i].t = ouf.readLong(0, kInf);
    v[0].t += v[i].t;
  }
  if (w < v[0].t) {
    quitf(_wa, "Worse than the answer. It's not guaranteed that your output is valid.");
  } else if (w > v[0].t) {
    quitf(_wa, "You think you can do better than the answer?");
  }
  for (int i = 1; i <= n; i++) {
    if (v[i].t >= v[i].w) {
      l.push_back(i);
    }
  }
  quitf(_ok, "Ciallo~");
}
