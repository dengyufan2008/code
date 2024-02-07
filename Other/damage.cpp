#include <iomanip>
#include <iostream>
#define CD constexpr double

using namespace std;

CD kA2D = 2.426;
CD kH2A = 0.0626 + 0.018;                                    // 10级E + 半血护摩1
CD kExtraA = 0;                                              // 应该胡桃队里目前没有直接加倍率区数值的拐
CD kExtraD = 1.0 + 0.33 + 0.466 + 0.15 + 0.075 + 0.3 + 0.2;  // 半血加成 + 火伤杯 + 魔女2 + 魔女4 1层 + 夜兰(平均) + 芙宁娜(平均)
CD kExtraM = 1.0 + 0.15;                                     // 魔女4
CD kLS = 90;                                                 // 90级堂主
CD kLE = 90;                                                 // 90级怪, 默认没有无视防 & 加减防
CD kD = 0.1;                                                 // 小宝元素抗性为 10%
CD kOffD = -0.2;                                             // 钟离盾
CD kM1 = 120;                                                // 教官 (60%)
CD kH = 34120.969760;
CD kA = 1354.715000;
CD kM0 = 267.345200;
CD kCP = 88.986058;
CD kCD = 177.837493;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  double t = (kA + kH * kH2A) * kA2D * kExtraD * 1.5 * ((kM0 / (kM0 + 1400.0) * 0.4 + (kM0 + kM1) / (kM0 + kM1 + 1400.0) * 0.6) * 25.0 / 9.0 + kExtraM) * (kLS + 100.0) / (kLS + kLE + 200.0);
  if (kD + kOffD < 0) {
    t *= 1.0 - (kD + kOffD) * 0.5;
  } else if (kD + kOffD < 0.75) {
    t *= 1.0 - (kD + kOffD);
  } else {
    t /= 1.0 + (kD + kOffD) * 4.0;
  }
  cout << "Expect:   " << fixed << setprecision(6) << t * (kCP * kCD * 0.0001 + 1.0) << '\n';
  cout << "Critical: " << fixed << setprecision(6) << t * (kCD * 0.01 + 1.0) << '\n';
  return 0;
}
