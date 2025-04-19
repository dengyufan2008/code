#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 3001, kMod = 998244353;
struct A {
  int x, y;
  int u;  // 与自己 x 相同的 y 的后继的值
  int r;  // 与自己 y 相同的 x 最大的值
  int p;  // i 之前第一个 jx > ix 的 j
  int q;  // i 之后第一个 jx > ix 的 j
} a[kMaxN];
int n, c, d;
LL ans;

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

const LL kInv2 = Pow(2), kInv3 = Pow(3), kInv5 = Pow(5), kInv30 = Pow(30);

// sum_{i=1}^{n-1} i^1
LL Sum1(int n) {
  return 1LL * (n - 1) * n % kMod * kInv2 % kMod;
}

// sum_{i=1}^{n-1} i^2
LL Sum2(int n) {
  return Sum1(n) * (n * 2 - 1) % kMod * kInv3 % kMod;
}

// sum_{i=1}^{n-1} i^3
LL Sum3(int n) {
  return Pow(Sum1(n), 2);
}

// sum_{i=1}^{n-1} i^4
LL Sum4(int n) {
  return (Pow(n - 1, 5) * kInv5 + Pow(n - 1, 4) * kInv2 + Pow(n - 1, 3) * kInv3 - (n - 1) * kInv30) % kMod;
}

// [1, n] * [1, m] 的边界内的正方形面积和
LL Calc(int n, int m) {
  if (n <= 1 || m <= 1) {
    return 0;
  }
  n > m ? swap(n, m) : void();
  // sum_{i=1}^{n-1} (n-i)(m-i)i^2
  return (Sum2(n) * n % kMod * m - Sum3(n) * (n + m) + Sum4(n)) % kMod;
}

// [1, n] * [1, m] 的边界内, 左边界在 [1, l], 右边界在 [n-r+1, n] 的正方形面积和
LL Calc(int n, int m, int l, int r) {
  return (Calc(n, m) - Calc(n - l, m) - Calc(n - r, m) + Calc(n - l - r, m)) % kMod;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> c >> d >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].x >> a[i].y;
  }
  sort(a + 1, a + n + 1, [](A i, A j) {
    return i.x < j.x || i.x == j.x && i.y < j.y;
  });

  // 定义合法正方形的关键点为上边界线段 (不算线段的左端点) 往上扫到 (包括自己所在的 y) 的第一个最靠右的点 (没有则为正无穷), \
     与下边界线段 (不算线段的左端点) 往下扫到 (包括自己所在的 y) 的第一个最靠右的点 (没有则为负无穷),                     \
     两点的铅垂线段 (不算线段的上下端点) 往左扫到 (包括自己所在的 y) 的第一个最靠上的点 (没有则关键点不存在)

  ans = Calc(a[1].x + 1, d + 1);
  for (int i = 1; i <= n; i++) {  // 统计右边界在 (a[i].x, a[i + 1].x] 的正方形
    int l = a[i].x + 1, r = i == n ? c : a[i + 1].x;

    {
      a[i].u = l > r ? a[i + 1].y : d + 1;
      for (int j = 1; j < i; j++) {  // y 为第一关键字, x 为第二关键字 插入排序
        if (a[j].y > a[i].y || a[j].y == a[i].y && a[j].x > a[i].x) {
          swap(a[j], a[i]);
        }
      }
      if (l > r) {
        continue;
      }
    }

    for (int j = i; j >= 1; j--) {
      a[j].r = a[j].x;
      if (j < i && a[j].y == a[j + 1].y) {
        a[j].r = a[j + 1].r;
      }
    }

    {
      static vector<int> v;
      v.clear();
      for (int j = 1; j <= i; j++) {
        for (; !v.empty() && a[v.back()].x <= a[j].x; v.pop_back()) {
        }
        a[j].p = v.empty() ? 0 : v.back();
        v.push_back(j);
      }
      v.clear();
      for (int j = i; j >= 1; j--) {
        for (; !v.empty() && a[v.back()].x <= a[j].x; v.pop_back()) {
        }
        a[j].q = v.empty() ? i + 1 : v.back();
        v.push_back(j);
      }
    }

    for (int j = 1; j <= i; j++) {  // 关键点存在, 枚举关键点
      if (a[j].r != a[j].x) {
        continue;
      }
      int px, py, qx, qy;
      if (a[j].p == 0) {
        px = r + 1, py = 0;
      } else {
        px = a[a[j].p].r, py = a[a[j].p].y;
      }
      if (a[j].q == i + 1) {
        qx = r + 1, qy = d;
      } else {
        qx = a[a[j].q].r, qy = a[a[j].q].y;
      }
      if (a[j].u < qy) {
        continue;
      }
      ans = (ans + Calc(r - a[j].x + 1, qy - py + 1, min(px, qx) - a[j].x, r - l + 1)) % kMod;
    }

    {  // 关键点不存在, 枚举上下找到的点, 必然是 y 相邻的两点
      static vector<A> v;
      v.clear(), v.push_back({c + 1, 0});
      for (int j = 1, k = 1; j <= i; j = k) {
        for (; k <= i && a[j].y == a[k].y; k++) {
        }
        v.push_back(a[k - 1]);
      }
      v.push_back({c + 1, d});
      for (int j = 1; j < v.size(); j++) {
        ans = (ans + Calc(r + 1, v[j].y - v[j - 1].y + 1, min(v[j - 1].x, v[j].x), r - l + 1)) % kMod;
      }
    }
  }
  cout << (ans + kMod) % kMod << '\n';
  return 0;
}
