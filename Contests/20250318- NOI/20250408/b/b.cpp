#include <cmath>
#include <vector>

#include "lines.h"
#define LD long double

using namespace std;

const int kX = 2e4 + 1, kL = 1e4, kV = 3e8;
const LD kEps = 1e-9;
struct A {
  LD k, y;
};
vector<int> ansk, ansb;

// [x, x+1] 中点的斜率, x 的坐标
A CalcK(int x, int l = 1) {
  LD y1 = query(kX, x);
  LD y2 = query(kX, x + l);
  return {l == 1 ? y2 - y1 : (y2 - y1) / l, y1};
}

void Find(int l, int r, A lw, A rw) {
  int x = round((lw.k * l - rw.k * r - lw.y + rw.y) / (lw.k - rw.k));
  A xw = CalcK(x);
  if (abs(xw.k - lw.k) >= kEps && abs(xw.k - rw.k) >= kEps) {
    Find(l, x, lw, xw);
    Find(x, r, xw, rw);
  } else {
    int p = x + kL;
    if (p >= 0) {
      ansk.push_back(p / kX);
    } else {
      ansk.push_back((p - kX + 1) / kX);
    }
    ansb.push_back(x - ansk.back() * kX);
  }
}

void solve(int N, int u) {
  Find(-kV, kV, CalcK(-kV, 1e7), CalcK(kV, 1e7));
  report(ansk, ansb);
}
// g++ -std=c++14 -O2 -Wall b.cpp grader.cpp -o b && b
