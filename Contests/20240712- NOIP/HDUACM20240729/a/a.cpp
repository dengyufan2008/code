#include <fstream>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 15;
struct V {
  LL x, y, z;
  V operator-(V v) {
    return {x - v.x, y - v.y, z - v.z};
  }
  LL operator*(V v) {
    return x * v.x + y * v.y + z * v.z;
  }
  LL Mod() {
    return x * x + y * y + z * z;
  }
} v[kMaxN];
int u, n, m, ans, c[kMaxN];
bool b[1 << kMaxN];

int PopCount(int s) {
  int ans = 0;
  for (; s; s ^= s & -s) {
    ans++;
  }
  return ans;
}

V Cross(int x, int y, int z) {
  V p = v[y] - v[x], q = v[z] - v[x];
  return {p.y * q.z - p.z * q.y,
          p.z * q.x - p.x * q.z,
          p.x * q.y - p.y * q.x};
}

LL Det(V x, V y, V z) {
  return x.x * y.y * z.z - x.x * z.y * y.z -
         y.x * x.y * z.z + y.x * z.y * x.z +
         z.x * x.y * y.z - z.x * y.y * x.z;
}

LL Volumn(int w, int x, int y, int z) {
  return Det(v[x] - v[w], v[y] - v[w], v[z] - v[w]);
}

bool Volumn(int s) {
  for (int i = 0; i < n; i++) {
    if (s >> i & 1) {
      for (int j = i + 1; j < n; j++) {
        if (s >> j & 1) {
          for (int k = j + 1; k < n; k++) {
            if (s >> k & 1) {
              for (int l = k + 1; l < n; l++) {
                if (s >> l & 1) {
                  if (Volumn(i, j, k, l)) {
                    return 1;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return 0;
}

bool Area(int s) {
  for (int i = 0; i < n; i++) {
    if (s >> i & 1) {
      for (int j = i + 1; j < n; j++) {
        if (s >> j & 1) {
          for (int k = j + 1; k < n; k++) {
            if (s >> k & 1) {
              if (Cross(i, j, k).Mod()) {
                return 1;
              }
            }
          }
        }
      }
    }
  }
  return 0;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> u;
  while (u--) {
    ans = 0;
    for (int i = 0; i < 1 << n; i++) {
      b[i] = 0;
    }
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> v[i].x >> v[i].y >> v[i].z;
      v[i] = v[i] - (V){-1, -1, -1};
    }
    for (int s = 1; s < 1 << n; s++) {
      if (PopCount(s) <= 2) {
        ans++;
      } else if (Volumn(s)) {
        m = 0;
        for (int i = 0; i < n; i++) {
          c[i] = 0;
        }
        for (int i = 0; i < n; i++) {
          if (s >> i & 1) {
            for (int j = i + 1; j < n; j++) {
              if (s >> j & 1) {
                for (int k = j + 1; k < n; k++) {
                  if (s >> k & 1) {
                    V o = Cross(i, j, k);
                    if (o.Mod()) {
                      int d = 0;
                      for (int l = 0; l < n; l++) {
                        if (s >> l & 1) {
                          LL w = o * (v[l] - v[i]);
                          if (w < 0) {
                            d |= 1;
                          } else if (w > 0) {
                            d |= 2;
                          }
                        }
                      }
                      if (d < 3) {
                        m++;
                        for (int l = 0; l < n; l++) {
                          LL w = o * (v[l] - v[i]);
                          c[l] += w < 0 && (d & 1) || w > 0 && (d & 2) || w == 0;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
        int t = 0;
        for (int i = 0; i < n; i++) {
          t |= (c[i] == m) << i;
        }
        ans += !b[t], b[t] = 1;
      } else if (Area(s)) {
        m = 0;
        for (int i = 0; i < n; i++) {
          c[i] = 0;
        }
        for (int i = 0; i < n; i++) {
          if (s >> i & 1) {
            for (int j = i + 1; j < n; j++) {
              if (s >> j & 1) {
                int k = -1;
                for (int l = 0; l < n; l++) {
                  if (i != l && j != l && (s >> l & 1)) {
                    k = l;
                    break;
                  }
                }
                bool able = 1;
                V o = Cross(i, j, k);
                for (int l = 0; l < n; l++) {
                  if ((s >> l & 1) && o * Cross(i, j, l) < 0) {
                    able = 0;
                    break;
                  }
                }
                if (able) {
                  m++;
                  for (int l = 0; l < n; l++) {
                    if (!Volumn(i, j, k, l) && o * Cross(i, j, l) >= 0) {
                      c[l]++;
                    }
                  }
                }
              }
            }
          }
        }
        int t = 0;
        for (int i = 0; i < n; i++) {
          t |= (c[i] == m) << i;
        }
        ans += !b[t], b[t] = 1;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
