#include <iomanip>
#include <iostream>
#define CD constexpr long double

using namespace std;

constexpr bool kTeam = 1;  // 是否是队伍伤害
CD kBaseH = 15552, kBaseA = 715;
CD kA2D = 2.426;
CD kH2A = 0.0626 + 0.018;                                              // 10级E + 半血护摩1
CD kExtraH = 1.0 + kTeam * (0.25);                                     // 双水 (护摩1一般计算在面板内)
CD kExtraA = 1.0 + kTeam * (0.2 + 0.2);                                // 宗室 + 千岩
CD kExtraD = 1.0 + 0.33 + 0.466 + 0.15 + 0.075 + kTeam * (0.3 + 0.2);  // 半血加成 + 火伤杯 + 魔女2 + 魔女4 1层 + 夜兰(平均) + 芙宁娜(平均)
CD kExtraM = 1.0 + 0.15;                                               // 魔女4
CD kLS = 90;                                                           // 90级堂主
CD kLE = 86;                                                           // 怪物等级, 默认没有无视防 & 加减防 (小助手为 86 级)
CD kD = 0.1;                                                           // 小宝元素抗性为 10%
CD kOffD = kTeam * (-0.2);                                             // 钟离盾
CD kM1 = kTeam * (120);                                                // 教官 (60% 覆盖率)
CD kH = 27600;
CD kA = 1204.8;
CD kM0 = 279.7;
CD kCp = 84.3;
CD kCd = 201.9;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  double t = (kA * kExtraA + kH * kExtraH * kH2A) * kA2D * kExtraD * 1.5 * ((kM0 / (kM0 + 1400.0) * 0.4 + (kM0 + kM1) / (kM0 + kM1 + 1400.0) * 0.6) * 25.0 / 9.0 + kExtraM) * (kLS + 100.0) / (kLS + kLE + 200.0);
  if (kD + kOffD < 0) {
    t *= 1.0 - (kD + kOffD) * 0.5;
  } else if (kD + kOffD < 0.75) {
    t *= 1.0 - (kD + kOffD);
  } else {
    t /= 1.0 + (kD + kOffD) * 4.0;
  }
  cout << "Expect:   " << fixed << setprecision(6) << t * (kCp * kCd * 0.0001 + 1.0) << '\n';
  cout << "Critical: " << fixed << setprecision(6) << t * (kCd * 0.01 + 1.0) << '\n';
  return 0;
}
