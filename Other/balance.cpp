#include <iomanip>
#include <iostream>
#define CD const double

using namespace std;

CD kBaseH = 15552, kBaseA = 715, kH2A = 0.0626;
CD kHPerC = 0.04955, kMPerC = 19.815, kCPPerC = 0.03305, kCDPerC = 0.06605;
CD kMaxCC = 26.183835327556961445009856507587;
CD kCC = 19.515152;    // 0 为无限制
CD kExtraH1 = 1.45;    // 护摩1
CD kExtraH2 = 4778.6;  // 花
CD kExtraH3 = 2091.3;  // 小生命
CD kExtraA1 = 1.4;     // 宗室 + 千岩
CD kExtraA2 = 0.041;   // 大攻击
CD kExtraA3 = 310.8;   // 羽
CD kExtraA4 = 13.6;    // 小攻击
CD kExtraM0 = 186.5;   // 沙
CD kExtraM1 = 306.5;   // 沙 + 教官(按持续时间为 E 的一半计)
CD kExtraM2 = 1.15;    // 魔女
CD kExtraCP = 0.361;   // 基础 + 头
CD kExtraCD = 1.546;   // 基础 + 突破 + 护摩
CD kExtraH2A = 0.018;  // 护摩1
CD kN = 29.7, kEps = 1e-2;
double ansch, anscm, ans;

double Sqr(double x) { return x * x; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (double ch = 0.0; ch <= 30.0; ch += kEps) {
    for (double cm = max(kN - ch - kMaxCC, 0.0); cm <= min(kN - ch, 30.0); cm += kEps) {
      double cc = kN - ch - cm;
      if (abs(kCC) < 0.0001 || abs(cc - kCC) < 0.005) {
        double h = kBaseH * (kExtraH1 + kHPerC * ch) + kExtraH2 + kExtraH3;
        double a = kBaseA * (kExtraA1 + kExtraA2) + kExtraA3 + kExtraA4 + h * (kH2A + kExtraH2A);
        double m0 = (kExtraM0 + kMPerC * cm) / (kExtraM0 + kMPerC * cm + 1400.0);
        double m1 = (kExtraM1 + kMPerC * cm) / (kExtraM1 + kMPerC * cm + 1400.0);
        double m = (m0 + m1) * 25.0 / 12.0 + kExtraM2 * 1.5;
        double c = Sqr(kCPPerC * kCDPerC * cc + kCPPerC * kExtraCD + kCDPerC * kExtraCP) / (kCPPerC * kCDPerC * 4.0) + 1.0;
        double s = a * m * c;
        if (s > ans) {
          ans = s, ansch = ch, anscm = cm;
        }
      }
    }
  }
  double anscc = kN - ansch - anscm;
  double t = (kCPPerC * kCDPerC * anscc + kCPPerC * kExtraCD + kCDPerC * kExtraCP) * 0.5;
  cout << fixed << setprecision(6) << "H:  " << kBaseH * (kExtraH1 + kHPerC * ansch) + kExtraH2 + kExtraH3 << '\n';
  cout << fixed << setprecision(6) << "M:  " << kExtraM0 + kMPerC * anscm << '\n';
  cout << fixed << setprecision(6) << "CP: " << t / kCDPerC * 100.0 << "%\n";
  cout << fixed << setprecision(6) << "CD: " << t / kCPPerC * 100.0 << "%\n";
  return 0;
}
