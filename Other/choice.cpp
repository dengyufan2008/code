#include <iomanip>
#include <iostream>
#include <vector>
#define CD constexpr double

using namespace std;

CD kEps = 1e-4;
CD kBaseH = 15552, kBaseA = 715;
CD kH2A = 0.0626;                   // 10级E
CD kExtraH2A = 0.018;               // 半血护摩1
CD kExtraH = 1.0 + 0.2 + 0.25;      // 护摩1 + 双水
CD kExtraA = 1.0 + 0.2 + 0.2;       // 宗室 + 千岩
CD kExtraM0 = 120;                   // 教官 (60% 覆盖率)
CD kExtraM1 = 1.0 + 0.15;           // 魔女4
CD kExtraCp = 0.05;                 // 基础
CD kExtraCd = 0.5 + 0.384 + 0.662;  // 基础 + 突破 + 护摩
struct T {
  double H, h, A, a, m, Cp, Cd;
  int c;  // 是否是散件

  T() : H(0.0), h(0.0), A(0.0), a(0.0), m(0.0), Cp(0.0), Cd(0.0), c(0) {}

  T(double _H, double _h, double _A, double _a, double _m, double _Cp, double _Cd, int _c)
      : H(_H), h(_h), A(_A), a(_a), m(_m), Cp(_Cp), Cd(_Cd), c(_c) {}

  void Init() {}

  template <typename... Args>
  void Init(string s, double t, Args... args) {
    if (s == "H") {
      H = t * 0.01;
    } else if (s == "h") {
      h = t;
    } else if (s == "A") {
      A = t * 0.01;
    } else if (s == "a") {
      a = t;
    } else if (s == "m") {
      m = t;
    } else if (s == "Cp") {
      Cp = t * 0.01;
    } else if (s == "Cd") {
      Cd = t * 0.01;
    } else {
      cout << "Issue Found\n";
      cout << "\"" << s << "\" Read\n\n";
    }
    Init(args...);
  }

  template <typename... Args>
  T(int _c, string s, double t, Args... args)
      : H(0.0), h(0.0), A(0.0), a(0.0), m(0.0), Cp(0.0), Cd(0.0), c(_c) {
    Init(s, t, args...);
  }

  T operator+(T &t) {
    return T(H + t.H, h + t.h, A + t.A, a + t.a, m + t.m, Cp + t.Cp, Cd + t.Cd, c + t.c);
  }

  double Calc() {
    double ansh = kBaseH * (kExtraH + H) + h;
    double ansa = kBaseA * (kExtraA + A) + a + ansh * (kExtraH2A + kH2A);
    double ansm = (m / (m + 1400.0) * 0.4 + (m + kExtraM0) / (m + kExtraM0 + 1400.0) * 0.6) * 25.0 / 6.0 + kExtraM1 * 1.5;
    double ansc = (kExtraCp + Cp) * (kExtraCd + Cd) + 1.0;
    return ansa * ansm * ansc;
  }

  void Print() {
    if (H > kEps) {
      cout << "H:  " << H * 100.0 << "%\n";
    }
    if (h > kEps) {
      cout << "h:  " << h << '\n';
    }
    if (A > kEps) {
      cout << "A:  " << A * 100.0 << "%\n";
    }
    if (a > kEps) {
      cout << "a:  " << a << '\n';
    }
    if (m > kEps) {
      cout << "m:  " << m << '\n';
    }
    if (Cp > kEps) {
      cout << "Cp: " << Cp * 100.0 << "%\n";
    }
    if (Cd > kEps) {
      cout << "Cd: " << Cd * 100.0 << "%\n";
    }
    cout << c << "\n\n";
  }
} ansa, ansb, ansc, ansd, anse;
double ans;
vector<T> flower = {
    T(1, "h", 4778.6, "Cp", 17.9, "H", 5.8, "Cd", 5.4, "A", 4.1)};
vector<T> feather = {
    T(0, "a", 310.8, "Cp", 9.7, "Cd", 7.8, "H", 21.0)};
vector<T> sand = {
    T(0, "m", 186.5, "h", 478.0, "H", 9.3, "a", 13.6, "Cp", 13.6)};
vector<T> cup = {  // 都给我去带火伤杯 !!!
    T(0, "h", 567.6, "Cp", 7.4, "H", 9.9)};
vector<T> head = {
    T(0, "Cp", 31.1, "h", 1045.6, "m", 16.3, "Cd", 19.4)};
// 主词条也要写上

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (T a : flower) {
    for (T b : feather) {
      for (T c : sand) {
        for (T d : cup) {
          for (T e : head) {
            T t = a + b + c + d + e;
            if (t.c <= 1) {
              double w = t.Calc();
              if (w > ans) {
                ans = w, ansa = a, ansb = b, ansc = c, ansd = d, anse = e;
              }
            }
          }
        }
      }
    }
  }
  cout << "Flower\n";
  ansa.Print();
  cout << "Feather\n";
  ansb.Print();
  cout << "Sand\n";
  ansc.Print();
  cout << "Cup\n";
  ansd.Print();
  cout << "Head\n";
  anse.Print();
  return 0;
}
