#include <fstream>
#include <vector>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 1e5 + 1, kMaxL = 17;
struct V {
  int w1, w2, d1, d2, f1[kMaxL], f2[kMaxL];
} v[kMaxN];
int n, m;

void Move(int &x1, int &x2, int t) {  // 一共跳 t 次父亲
  for (int i = kMaxL - 1; i >= 0; i--) {
    while (1 << i + 1 <= t) {
      int w1 = v[x1].d1 > 1 << i ? v[v[x1].f1[i]].w1 : 0;
      int w2 = v[x2].d2 > 1 << i ? v[v[x2].f2[i]].w2 : 0;
      if (w1 > w2) {
        x1 = v[x1].f1[i];
      } else {
        x2 = v[x2].f2[i];
      }
      t -= 1 << i;
    }
  }
  while (t--) {
    if (v[x1].w1 > v[x2].w2) {
      x1 = v[x1].f1[0];
    } else {
      x2 = v[x2].f2[0];
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    static vector<int> l;
    cin >> v[i].w1;
    for (; !l.empty() && v[l.back()].w1 > v[i].w1; l.pop_back()) {
    }
    v[i].f1[0] = l.empty() ? 0 : l.back();
    for (int j = 1; j < kMaxL; j++) {
      v[i].f1[j] = v[v[i].f1[j - 1]].f1[j - 1];
    }
    v[i].d1 = v[v[i].f1[0]].d1 + 1, l.push_back(i);
  }
  for (int i = 1; i <= n; i++) {
    static vector<int> l;
    cin >> v[i].w2;
    for (; !l.empty() && v[l.back()].w2 > v[i].w2; l.pop_back()) {
    }
    v[i].f2[0] = l.empty() ? 0 : l.back();
    for (int j = 1; j < kMaxL; j++) {
      v[i].f2[j] = v[v[i].f2[j - 1]].f2[j - 1];
    }
    v[i].d2 = v[v[i].f2[0]].d2 + 1, l.push_back(i);
  }
  cin >> m;
  for (int i = 1, x1, x2, y1, y2, z1, z2; i <= m; i++) {
    int _x1, _x2, _y1, _y2, ans;
    cin >> x1 >> x2 >> y1 >> y2, ans = x1 + x2 + y1 + y2;
    if (v[x1].d1 + v[x2].d2 < v[y1].d1 + v[y2].d2) {
      swap(x1, y1), swap(x2, y2);
    }
    z1 = x1, z2 = x2;
    Move(x1, x2, v[x1].d1 + v[x2].d2 - v[y1].d1 - v[y2].d2);
    if (x1 == y1 && x2 == y2) {
      cout << ans - (x1 + x2 << 1) << '\n';
      continue;
    }
    int d = v[x1].d1 + v[x2].d2, l = 2, r = d - 1;
    while (l <= r) {  // 二分重合时深度和
      int mid = l + r >> 1;
      _x1 = x1, _x2 = x2, _y1 = y1, _y2 = y2;
      Move(_x1, _x2, d - mid), Move(_y1, _y2, d - mid);
      if (_x1 == _y1 && _x2 == _y2) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    _x1 = x1, _x2 = x2, _y1 = y1, _y2 = y2;
    Move(_x1, _x2, d - l), Move(_y1, _y2, d - l);
    if (_x1 + _x2 < _y1 + _y2) {
      swap(x1, y1), swap(x2, y2);
      swap(_x1, _y1), swap(_x2, _y2);
    } else {
      z1 = y1, z2 = y2;
    }
    if (_x1 == _y1 && v[_x2].f2[0] < _y2 || _x2 == _y2 && v[_x1].f1[0] < _y1) {
      // 可能上一步就能够在途中重合了
      int _d = v[z1].d1 + v[z2].d2, _l = l, _r = _d;
      while (_l <= _r) {  // 深度和
        int mid = _l + _r >> 1;
        _y1 = z1, _y2 = z2;
        Move(_y1, _y2, _d - mid);
        if (_x1 == _y1 && _y2 < _x2 || _x2 == _y2 && _y1 < _x1) {
          _l = mid + 1;
        } else {
          _r = mid - 1;
        }
      }
      _y1 = z1, _y2 = z2;
      Move(_y1, _y2, _d - _r);
      cout << ans - (_y1 + _y2 << 1) << '\n';
    } else {
      Move(_x1, _x2, 1), Move(_y1, _y2, 1);
      cout << ans - (_x1 + _x2 << 1) << '\n';
    }
  }
  return 0;
}
