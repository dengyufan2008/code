#include <fstream>
#include <queue>
#include <set>
#define LL long long

using namespace std;

ifstream cin("j.in");
ofstream cout("j.out");

int n, w[4], c[8001];
LL ans;
struct V {
  int w[4];

  int Sum() { return w[0] + w[1] + w[2] + w[3]; }

  V Add(int o, int t) {
    V ans = *this;
    w[o] = abs(w[o] + t);
    for (int i = o; i < 3; i++) {
      if (w[i] > w[i + 1]) {
        swap(w[i], w[i + 1]);
      } else {
        break;
      }
    }
    for (int i = o; i > 0; i--) {
      if (w[i] < w[i - 1]) {
        swap(w[i], w[i - 1]);
      } else {
        break;
      }
    }
    return ans;
  }

  int C() {
    int s = 1;
    for (int p = 3, q = 3; p >= 0; p--) {
      for (; q >= 0 && w[p] <= ::w[q]; q--) {
      }
      s *= (p - q) * (1 + (w[p] > 0));
    }
    return s;
  }

  bool operator<(const V &v) const {
    for (int i = 0; i < 4; i++) {
      if (w[i] != v.w[i]) {
        return w[i] < v.w[i];
      }
    }
    return 0;
  }

  bool operator==(const V &v) const {
    for (int i = 0; i < 4; i++) {
      if (w[i] != v.w[i]) {
        return 0;
      }
    }
    return 1;
  }
};
set<V> l[8001];

void Init() {
  for (int i = 0; i < 4; i++) {
    cin >> w[i];
    for (int j = 0; j < i; j++) {
      w[j] > w[i] ? swap(w[j], w[i]) : void();
    }
  }
}

void Bfs() {
  queue<pair<V, int>> q;
  set<V> s;
  for (q.push({{0, 0, 0, 0}, 0}); !q.empty(); q.pop()) {
    V v = q.front().first, _v;
    int x = q.front().second + 1;
    if (v.w[3] > 6 || s.count(v)) {
      continue;
    }
    s.insert(v);
    for (int i = 0; i < x - 1; i++) {
      int s = v.Sum(), t = i * (i - 1) / 2;
      if (s <= t && (s + t & 1 ^ 1)) {
        s = v.C();
        if (s) {
          l[i].insert(v), c[i] += s;
        }
      }
    }
    for (int i = 0; i < 4; i++) {
      _v = v, _v.Add(i, x), q.push({_v, x});
      _v = v, _v.Add(i, -x), q.push({_v, x});
    }
  }
}

void Expand() {
  V _v;
  for (int &x = n = 7; !l[x - 1].empty(); x++) {
    for (V v : l[x - 1]) {
      for (int i = 0; i < 4; i++) {
        for (int y : {x, -x}) {
          _v = v, _v.Add(i, y);
          if (_v.Add(3, -y) == v && !l[y].count(_v)) {
            int s = _v.C();
            if (s) {
              l[y].insert(_v), c[y] += s;
            }
          }
        }
      }
    }
  }
  n -= 2;
}

void CalcAns() {
  ;
}

void CalcDelta() {
  ;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init(), Bfs(), Expand(), CalcAns(), CalcDelta();
  return 0;
}
