#include <cmath>
#include <fstream>
#include <queue>
#include <set>
#define LL long long

using namespace std;

ifstream cin("j.in");
ofstream cout("j.out");

// const int kMaxN = 8001, kFact[5] = {1, 1, 2, 6, 24};
const int kMaxN = 105, kFact[5] = {1, 1, 2, 6, 24};
// const int kMaxN = 401, kFact[5] = {1, 1, 2, 6, 24};
int w[4];
LL ans, c[kMaxN];
struct V {
  int w[4];

  int Sum() { return w[0] + w[1] + w[2] + w[3]; }

  void Add(int o, int t) {
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
  }

  int C() {
    int s = 1;
    for (int p = 3, q = 3; p >= 0; p--) {
      for (; q >= 0 && w[p] <= ::w[q]; q--) {
      }
      s *= (p - q) * (1 + (w[p] > 0));
    }
    for (int p = 0, q = 0; p < 4; p = q) {
      for (; q < 4 && w[p] == w[q]; q++) {
      }
      s /= kFact[q - p];
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
set<V> l[kMaxN];

void Init() {
  for (int i = 0; i < 4; i++) {
    cin >> w[i];
    for (int j = 0; j < i; j++) {
      w[j] > w[i] ? swap(w[j], w[i]) : void();
    }
  }
}

void Bfs() {
  V v;
  queue<pair<V, int>> q;
  set<pair<V, int>> st;
  for (q.push({{0, 0, 0, 0}, 0}); !q.empty(); q.pop()) {
    v = q.front().first, st.insert(q.front());
    int x = q.front().second + 1;
    if (x <= 6) {
      V _v;
      for (int i = 0; i < 4; i++) {
        _v = v, _v.Add(i, x);
        if (!st.count({_v, x})) {
          q.push({_v, x});
        }
        _v = v, _v.Add(i, -x);
        if (!st.count({_v, x})) {
          q.push({_v, x});
        }
      }
    }
  }
  for (int &i = v.w[0] = 0; i <= 5; i++) {
    for (int &j = v.w[1] = i; j <= 7; j++) {
      for (int &k = v.w[2] = j; k <= 10; k++) {
        for (int &l = v.w[3] = k; l <= 21; l++) {
          int s = i + j + k + l;
          if (s <= 21) {
            for (int t = 1; t <= 6; t++) {
              if (s <= t * (t + 1) / 2 && ((s + t * (t + 1) / 2) & 1 ^ 1)) {
                if (!st.count({v, t})) {
                  ::l[t].insert(v), c[t] += v.C();
                } else {
                  break;
                }
              }
            }
          }
        }
      }
    }
  }
}

void Expand() {
  V _v, __v;
  for (int x = 7; x < kMaxN; x++) {
    for (V v : l[x - 1]) {
      for (int i = 0; i < 4; i++) {
        for (int _x : {x, -x}) {
          _v = v, _v.Add(i, _x), __v = _v, __v.Add(3, -_x);
          if (__v == v && !l[x].count(_v) && _v.C()) {
            bool flag = 1;
            for (int y = x - 1; y <= x && flag; y++) {
              for (int j = 0; j < 4 && flag; j++) {
                for (int _y : {y, -y}) {
                  __v = _v, __v.Add(j, _y);
                  int s = __v.Sum();
                  if (s <= y * (y - 1) / 2 && ((s + y * (y - 1) / 2) & 1 ^ 1)) {
                    flag &= l[y - 1].count(__v);
                  }
                }
              }
            }
            if (flag) {
              l[x].insert(_v), c[x] += _v.C();
            }
          }
        }
      }
    }
  }
}

void CalcAns() {
  LL f[kMaxN >> 1] = {}, g[kMaxN >> 1] = {};
  for (int i = 0; i < kMaxN >> 1; i++) {
    for (int j = max(i - w[1], 0); j <= min(i, w[0]); j++) {
      f[i] += ((j > 0) + 1) * ((i > j) + 1);
    }
  }
  for (int i = 0; i < kMaxN >> 1; i++) {
    for (int j = max(i - w[3], 0); j <= min(i, w[2]); j++) {
      g[i] += ((j > 0) + 1) * ((i > j) + 1);
    }
  }
  for (int i = 0; i < kMaxN; i++) {
    LL s = 0;
    for (int j = max(i - w[2] - w[3], 0); j <= min(i, w[0] + w[1]); j++) {
      s += f[j] * g[i - j];
    }
    int t = sqrt(2 * i + 0.25) + 0.499999;
    if (t * (t + 1) / 2 + i & 1) {
      t += t & 1 ? 2 : 1;
    }
    ans += s * t;
  }
  for (int i = 0; i < kMaxN; i++) {
    ans += c[i] * (i & 1 ? 1 : 3);
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init();
  Bfs();
  Expand();
  for (int i = 0; i < kMaxN; i++) {
    if (!l[i].empty()) {
      cout << i << ":\n";
      int shit = 0;
      for (V v : l[i]) {
        if (v.w[0] <= 10 && v.w[1] <= 11 && v.w[2] <= 12 && v.w[3] <= 13) {
          shit++;
          for (int o = 0; o < 4; o++) {
            cout << v.w[o] << " \n"[o == 3];
          }
        }
      }
      // cout << shit << '\n';
    }
  }
  CalcAns();
  return 0;
}
