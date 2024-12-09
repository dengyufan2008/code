// Author : HeRaNO
// Modified by YunQian

#include "testlib.h"
#define MAXN 105

const int testCase = 100;
const int changeTime = 5;
const int swapTime = 5;

int N[] = {0, 8, 13, 16, 32, 53, 64, 73, 82, 91, 100};
int T[11][3] = {
    {0, 0, 0},
    {28, 9, 6},
    {78, 14, 10},
    {120, 17, 10},
    {496, 33, 15},
    {1378, 54, 21},
    {2016, 65, 21},
    {2628, 74, 28},
    {3321, 83, 28},
    {4095, 92, 29},
    {4950, 101, 30}};

int n;

bool isdigit(std::string &s) {
  for (char i : s)
    if (!(i >= '0' && i <= '9'))
      return false;
  return true;
}

std::vector<std::pair<int, int>> valid(int line, std::vector<std::string> &instructions) {
  std::vector<bool> vis(n + 1, false);
  std::vector<std::pair<int, int>> res;
  quitif(instructions.size() % 3 != 0, _wa, "wrong parameters format (line #%d)", line);
  for (int i = 0; i < instructions.size() / 3; i++) {
    std::string instruction = instructions[3 * i];
    std::string R1 = instructions[3 * i + 1];
    std::string R2 = instructions[3 * i + 2];
    quitif(instruction != "CMPSWP", _wa, "wrong instruction name: %s (line #%d - instruction #%d)", instruction.c_str(), line, i + 1);
    quitif(R1.front() != 'R', _wa, "wrong register Ri name: %s (line #%d - instruction #%d)", R1.c_str(), line, i + 1);
    quitif(R2.front() != 'R', _wa, "wrong register Rj name: %s (line #%d - instruction #%d)", R2.c_str(), line, i + 1);
    int r1, r2;
    R1 = R1.substr(1);
    R2 = R2.substr(1);
    quitif(!isdigit(R1), _wa, "wrong register Ri format: R%s (line #%d - instruction #%d)", R1.c_str(), line, i + 1);
    quitif(!isdigit(R2), _wa, "wrong register Rj format: R%s (line #%d - instruction #%d)", R2.c_str(), line, i + 1);
    try {
      r1 = std::stoi(R1);
      r2 = std::stoi(R2);
    } catch (std::exception &err) {
      quitf(_wa, "wrong register format: %s (line #%d - instruction #%d)", err.what(), line, i + 1);
    }
    quitif(!(1 <= r1 && r1 <= n), _wa, "wrong register Ri format: i < 1 or i > n (line #%d - instruction #%d)", line, i + 1);
    quitif(!(1 <= r2 && r2 <= n), _wa, "wrong register Ri format: i < 1 or i > n (line #%d - instruction #%d)", line, i + 1);
    quitif(r1 == r2, _wa, "R%d is used twice in line #%d", r1, line);
    quitif(vis[r1], _wa, "R%d is used twice in line#%d", r1, line);
    quitif(vis[r2], _wa, "R%d is used twice in line#%d", r2, line);
    vis[r1] = vis[r2] = true;
    res.push_back({r1, r2});
  }
  return res;
}

void cmpswp(int &a, int &b) {
  if (a > b) std::swap(a, b);
  return;
}

bool canSwap(std::vector<int> rs, const std::vector<std::pair<int, int>> &allSwapR) {
  for (auto [r1, r2] : allSwapR)
    cmpswp(rs[r1 - 1], rs[r2 - 1]);
  return std::is_sorted(rs.begin(), rs.end());
}

void testSort(const std::vector<std::pair<int, int>> &allSwapR, bool isRandom = true, bool desc = false) {
  for (int change = 1; change <= changeTime; change++) {
    std::vector<int> rs(n, 0);
    for (int i = 0; i < n; i++)
      rs[i] = rnd.next(n);
    if (!isRandom) {
      if (desc)
        std::sort(rs.begin(), rs.end(), std::greater<int>());
      else
        std::sort(rs.begin(), rs.end());
    }
    for (int i = 1; i <= testCase; i++) {
      if (!canSwap(rs, allSwapR))
        quitf(_wa, "the commands are wrong - test case %d (random: %s, desc: %s)", i, isRandom ? "true" : "false", desc ? "true" : "false");
      int swapT = rnd.next(1, swapTime);
      while (swapT--) {
        // std::vector<int> swapPos = rnd.distinct(2, 0, n - 1);
        // int a = swapPos.front();
        // int b = swapPos.back();
        int a = rnd.next(n), b = rnd.next(n - 1);
        if (b >= a) b++;
        std::swap(rs[a], rs[b]);
      }
    }
  }
  return;
}

void registerGenForTest(int argc, char *argv[]) {
  random_t::version = 1;
  rnd.setSeed(argc, argv);
  return;
}

int main(int argc, char *argv[]) {
  registerTestlibCmd(argc, argv);
  registerGenForTest(argc, argv);
  n = inf.readInt();
  int testCase = 0;
  for (int i = 1; i <= 10; i++)
    if (N[i] == n)
      testCase = i;
  quitif(!testCase, _fail, "didn't found the testcase which n = %d", n);
  std::vector<std::pair<int, int>> allSwapR;
  int t1 = T[testCase][0];
  int t2 = T[testCase][1];
  int t3 = T[testCase][2];
  int t = ouf.readInt();
  ouf.nextLine();
  quitif(t > t1, _wa, "t > t1");
  for (int i = 1; i <= t; i++) {
    std::string program;
    std::vector<std::string> instructions;
    std::vector<std::pair<int, int>> swapR;
    ouf.readLineTo(program);
    instructions = split(trim(program), ' ');
    swapR = valid(i, instructions);
    for (auto item : swapR)
      allSwapR.push_back(item);
  }
  testSort(allSwapR);
  testSort(allSwapR, false);
  testSort(allSwapR, false, true);
  if (t1 >= t && t > t2)
    quitp(round(10.0 + 20.0 / (t - t2)) / 100.0, "correct answer with t1 = %d >= t = %d > t2 = %d", t1, t, t2);
  if (t2 >= t && t > t3)
    quitp(round(30.0 + 70.0 * (t2 - t + 1) / (t2 - t3)) / 100.0, "correct answer with t2 = %d >= t = %d > t3 = %d", t2, t, t3);
  quitf(_ok, "correct answer with t = %d <= t3 = %d", t, t3);
  return 0;
}
