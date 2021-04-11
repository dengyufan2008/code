#include <cstdio>
using namespace std;
int main() {
  freopen("game.in", "r", stdin);
  freopen("game.out", "w", stdout);
  double best = 0, play = 0, temp, ans = 0;
  for (int i = 1; i <= 30; i++) {
    scanf("%lf", &temp);
    best = best + temp;
  }
  for (int i = 1; i <= 10; i++) {
    scanf("%lf", &temp);
    play = play + temp;
  }
  ans = (best + play) / 40.0;
  printf("%.2lf", ans);
  fclose(stdin);
  fclose(stdout);
  return 0;
}
/*
ans=(best/30.0*3.0+play/10.0)/4.0
   =(best/10.0+play/10.0)/4.0
   =(best+play)/40.0
*/
