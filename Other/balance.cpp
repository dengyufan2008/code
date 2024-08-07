#include <iomanip>
#include <iostream>
#define CD constexpr long double

using namespace std;

CD kBaseH = 15552, kBaseA = 715;
CD kH2A = 0.0626;  // 10级E
CD kHPerC = 0.04955, kMPerC = 19.815, kCpPerC = 0.03305, kCdPerC = 0.06605;
CD kMaxCC = 26.183;                 // 能百暴还能配平? 去死吧你
CD kCC = 19.515152;                 // 0 为无限制
CD kExtraH0 = 1.0 + 0.2;            // 护摩1
CD kExtraH1 = 0.25;                 // 双水
CD kExtraH2 = 4778.6;               // 花
CD kExtraH3 = 2091.3;               // 小生命
CD kExtraA0 = 1.0 + 0.041;          // 大攻击
CD kExtraA1 = 0.2 + 0.2;            // 宗室 + 千岩
CD kExtraA2 = 310.8;                // 羽
CD kExtraA3 = 13.6;                 // 小攻击
CD kExtraM0 = 186.5;                // 沙
CD kExtraM1 = 120;                  // 教官(按持续时间为 E 的 60% 计)
CD kExtraM2 = 1.0 + 0.15;           // 魔女4
CD kExtraCp = 0.05 + 0.311;         // 基础 + 头
CD kExtraCd = 0.5 + 0.384 + 0.662;  // 基础 + 突破 + 护摩
CD kExtraH2A = 0.018;               // 半血护摩1
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
        double h = kBaseH * (kExtraH0 + kExtraH1 + kHPerC * ch) + kExtraH2 + kExtraH3;
        double a = kBaseA * (kExtraA0 + kExtraA1) + kExtraA2 + kExtraA3 + h * (kH2A + kExtraH2A);
        double m0 = (kExtraM0 + kMPerC * cm) / (kExtraM0 + kMPerC * cm + 1400.0);
        double m1 = (kExtraM0 + kExtraM1 + kMPerC * cm) / (kExtraM0 + kExtraM1 + kMPerC * cm + 1400.0);
        double m = (m0 * 0.4 + m1 * 0.6) * 25.0 / 6.0 + kExtraM2 * 1.5;
        double c = Sqr(kCpPerC * kCdPerC * cc + kCpPerC * kExtraCd + kCdPerC * kExtraCp) / (kCpPerC * kCdPerC * 4.0) + 1.0;
        double s = a * m * c;
        if (s > ans) {
          ans = s, ansch = ch, anscm = cm;
        }
      }
    }
  }
  double anscc = kN - ansch - anscm;
  double t = (kCpPerC * kCdPerC * anscc + kCpPerC * kExtraCd + kCdPerC * kExtraCp) * 0.5;
  cout << "Self:\n";
  cout << fixed << setprecision(6) << "H:  " << kBaseH * (kExtraH0 + kHPerC * ansch) + kExtraH2 + kExtraH3 << '\n';
  cout << fixed << setprecision(6) << "A:  " << kBaseA * kExtraA0 + kExtraA2 + kExtraA3 << '\n';
  cout << fixed << setprecision(6) << "M:  " << kExtraM0 + kMPerC * anscm << '\n';
  cout << fixed << setprecision(6) << "CP: " << t / kCdPerC * 100.0 << "%\n";
  cout << fixed << setprecision(6) << "CD: " << t / kCpPerC * 100.0 << "%\n";
  cout << "Team:\n";
  cout << fixed << setprecision(6) << "H:  " << kBaseH * (kExtraH0 + kExtraH1 + kHPerC * ansch) + kExtraH2 + kExtraH3 << '\n';
  cout << fixed << setprecision(6) << "A:  " << kBaseA * (kExtraA0 + kExtraA1) + kExtraA2 + kExtraA3 << '\n';
  cout << fixed << setprecision(6) << "M:  " << kExtraM0 + kExtraM1 + kMPerC * anscm << '\n';
  cout << fixed << setprecision(6) << "CP: " << t / kCdPerC * 100.0 << "%\n";
  cout << fixed << setprecision(6) << "CD: " << t / kCpPerC * 100.0 << "%\n";
  return 0;
}
