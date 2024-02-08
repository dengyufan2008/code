#include <iomanip>
#include <iostream>
#include <vector>
#define CD constexpr double

using namespace std;

CD kEps = 1e-4;
CD kBaseH = 15552, kBaseA = 715;
CD kH2A = 0.0626;                   // 10级E
CD kExtraH2A = 0.018;               // 半血护摩1
CD kH = 1.0 + 0.2;                  // 护摩1
CD kExtraH = 1.0 + 0.2 + 0.25;      // 护摩1 + 双水
CD kA = 1.0;                        // 啥都没有
CD kExtraA = 1.0 + 0.2 + 0.2;       // 宗室 + 千岩
CD kExtraM0 = 120;                  // 教官 (60% 覆盖率)
CD kExtraM1 = 1.0 + 0.15;           // 魔女4
CD kExtraCp = 0.05;                 // 基础
CD kExtraCd = 0.5 + 0.384 + 0.662;  // 基础 + 突破 + 护摩
const bool kSet = 1;                // 是否需要四件套
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

  void Print(string s) {
    cout << s << '\n';
    if (H > kEps) {
      cout << fixed << setprecision(1) << "H:  " << H * 100.0 << "%\n";
    }
    if (h > kEps) {
      cout << fixed << setprecision(0) << "h:  " << h << '\n';
    }
    if (A > kEps) {
      cout << fixed << setprecision(1) << "A:  " << A * 100.0 << "%\n";
    }
    if (a > kEps) {
      cout << fixed << setprecision(0) << "a:  " << a << '\n';
    }
    if (m > kEps) {
      cout << fixed << setprecision(1) << "m:  " << m << '\n';
    }
    if (Cp > kEps) {
      cout << fixed << setprecision(1) << "Cp: " << Cp * 100.0 << "%\n";
    }
    if (Cd > kEps) {
      cout << fixed << setprecision(1) << "Cd: " << Cd * 100.0 << "%\n";
    }
    cout << c << "\n\n";
  }

  void Print() {
    cout << "Total\n";
    cout << fixed << setprecision(1) << "H:  " << kBaseH * (kH + H) + h << '\n';
    cout << fixed << setprecision(1) << "A:  " << kBaseA * (kA + A) + a << '\n';
    cout << fixed << setprecision(1) << "M:  " << m << '\n';
    cout << fixed << setprecision(1) << "Cp: " << (Cp + kExtraCp) * 100.0 << "%\n";
    cout << fixed << setprecision(1) << "Cd: " << (Cd + kExtraCd) * 100.0 << "%\n";
  }
} ansa, ansb, ansc, ansd, anse;
double ans;
vector<T> flower = {
    T(1, "h", 4778.6, "Cp", 17.9, "H", 5.8, "Cd", 5.4, "A", 4.1),
    T(0, "h", 4778.6, "Cp", 10.5, "m", 23, "Cd", 12.4),
    T(0, "h", 4778.6, "Cp", 10.5, "Cd", 14.8, "m", 16),
    T(0, "h", 4778.6, "Cp", 5.8, "Cd", 11.7, "m", 61),
    T(0, "h", 4778.6, "A", 9.9, "Cp", 6.6, "Cd", 14.0),
    T(0, "h", 4778.6, "A", 8.2, "m", 33, "Cd", 14.8, "Cp", 6.6),
    T(0, "h", 4778.6, "m", 21, "H", 14.0, "Cd", 20.2, "Cp", 3.1),
    T(1, "h", 4778.6, "Cd", 20.2, "Cp", 9.3, "H", 4.7),
    T()};
vector<T> feather = {
    T(0, "a", 310.8, "Cp", 9.7, "Cd", 7.8, "H", 21.0),
    T(1, "a", 310.8, "Cd", 5.4, "m", 68, "Cp", 10.9),
    T(1, "a", 310.8, "H", 9.3, "Cp", 10.5, "A", 13.4, "Cd", 5.4),
    T(1, "a", 310.8, "Cp", 10.1, "h", 299, "Cd", 14.8, "A", 15.7),
    T(1, "a", 310.8, "Cd", 25.7, "H", 5.3, "Cp", 9.3),
    T(1, "a", 310.8, "Cd", 14.0, "Cp", 8.9, "h", 687, "m", 16),
    T()};
vector<T> sand = {
    T(0, "m", 186.5, "h", 478.0, "H", 9.3, "a", 13.6, "Cp", 13.6),
    T(1, "m", 186.5, "Cp", 3.9, "Cd", 15.5, "h", 418),
    T(0, "H", 46.6, "A", 5.8, "Cd", 28.8, "a", 33),
    T(1, "H", 46.6, "Cp", 10.1, "Cd", 15.5, "m", 19, "a", 33),
    T(1, "H", 46.6, "Cp", 7.4, "a", 33, "Cd", 21.8),
    T()};
vector<T> cup = {  // 都给我去带火伤杯 !!!
    T(0, "h", 567.6, "Cp", 7.4, "H", 9.9),
    T(0, "a", 14, "Cp", 9.3, "m", 21),
    T(1, "m", 35, "Cd", 27.2, "H", 4.7),
    T()};
vector<T> head = {
    T(0, "Cp", 31.1, "h", 1045.6, "m", 16.3, "Cd", 19.4),
    T(0, "Cp", 31.1, "Cd", 21.1, "h", 747),
    T(1, "Cp", 31.1, "a", 31, "Cd", 21.8),
    T(1, "Cp", 31.1, "Cd", 14.8, "h", 807, "a", 19, "m", 40),
    T(1, "Cp", 31.1, "A", 5.3, "Cd", 14.0, "m", 86),
    T(0, "Cd", 62.2, "Cp", 6.6, "h", 269, "a", 72),
    T(1, "Cd", 62.2, "a", 29, "A", 4.1, "h", 299, "Cp", 16.7),
    T()};
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
            if (t.c <= 1 || !kSet) {
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
  ansa.Print("Flower");
  ansb.Print("Feather");
  ansc.Print("Sand");
  ansd.Print("Cup");
  anse.Print("Head");
  (ansa + ansb + ansc + ansd + anse).Print();
  return 0;
}
