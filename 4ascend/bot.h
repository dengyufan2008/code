#include <algorithm>
#include <vector>

typedef __int128_t LLL;

int PopCount(auto x) {
  int ans = 0;
  for (; x; x &= x - 1, ans++) {
  }
  return ans;
}

class Bot {
  static const int kInf = 1e9;

  LLL CheckAscend(int coor, LLL alice_chess, LLL bob_chess) {
    int coor_x = coor / 9, coor_y = coor % 9;
    LLL tmp = 0;
    for (auto [delta_x, delta_y] : {std::make_pair(0, 1), std::make_pair(1, -1),
                                    std::make_pair(1, 0), std::make_pair(1, 1)}) {
      int neg = 0, pos = 0;
      for (int now_x = coor_x - delta_x, now_y = coor_y - delta_y;;) {
        if (now_x < 0 || now_x >= 9 || now_y < 0 || now_y >= 9) {
          break;
        } else if (alice_chess >> now_x * 9 + now_y & 1 ^ 1) {
          break;
        }
        now_x -= delta_x, now_y -= delta_y, neg++;
      }
      for (int now_x = coor_x + delta_x, now_y = coor_y + delta_y;;) {
        if (now_x < 0 || now_x >= 9 || now_y < 0 || now_y >= 9) {
          break;
        } else if (alice_chess >> now_x * 9 + now_y & 1 ^ 1) {
          break;
        }
        now_x += delta_x, now_y += delta_y, pos++;
      }
      if (neg + pos >= 3) {
        for (int i = -neg; i <= pos; i++) {
          tmp |= (LLL)1 << (coor_x + i * delta_x) * 9 + (coor_y + i * delta_y);
        }
      }
    }
    return tmp;
  }

  /// @return pos:bob_life decrease neg:alice_life decrease
  int Fight(LLL magic, LLL attack_chess, LLL defend_chess) {
    int attack_strength = PopCount(attack_chess);
    int attack_extra = PopCount(attack_chess & magic);
    int defend_strength = PopCount(defend_chess);
    int defend_extra = PopCount(defend_chess & magic);

    int tmp = std::min(attack_extra, defend_extra);
    attack_extra -= tmp, defend_extra -= tmp;

    if (attack_extra) {
      tmp = std::min(attack_extra, defend_strength);
      attack_extra -= tmp, defend_strength -= tmp;
    } else {
      tmp = std::min(defend_extra, attack_strength);
      defend_extra -= tmp, attack_strength -= tmp;
    }

    tmp = std::min(attack_strength, defend_strength);
    attack_strength -= tmp, defend_strength -= tmp;

    if (attack_strength) {
      return -attack_strength;
    } else {
      return defend_strength;
    }
  }

  void Operate(int coor, int &alice_life, int &bob_life,
               LLL &alice_chess, LLL &bob_chess,
               LLL &magic, LLL &attack_chess) {
    alice_chess |= (LLL)1 << coor;
    LLL tmp = CheckAscend(coor, alice_chess, bob_chess);
    alice_chess ^= tmp;
    if (attack_chess) {
      attack_chess ^= attack_chess & (LLL)1 << coor;
      int delta = Fight(magic, attack_chess, tmp);
      if (delta >= 0) {
        bob_life -= delta;
      } else {
        alice_life -= delta;
      }
      magic ^= magic & (attack_chess | tmp);
      attack_chess = 0;
    } else {
      attack_chess = tmp;
    }
  }

  int CalcValue(int alice_life, int bob_life,
                LLL alice_chess, LLL bob_chess,
                LLL magic, LLL attack_chess) {
    ;
  }

  /// @brief decision of alice, maximize value
  int AlphaBeta(int alice_life, int bob_life,
                LLL alice_chess, LLL bob_chess,
                LLL magic, LLL attack_chess,
                int &alpha, int &beta, int loop = 3) {
    if (!loop) {
      alpha = std::max(alpha, CalcValue(alice_life, bob_life,
                                        alice_chess, bob_chess,
                                        magic, attack_chess));
      return -1;
    }
    static std::vector<int> chess_list;
    std::vector<std::pair<int, int>> coor_list;  // sum dis, number
    for (int i = 0; i < 9 * 9; i++) {
      if ((alice_chess | bob_chess | attack_chess) >> i & 1) {
        chess_list.push_back(i);
      }
    }
    for (int i = 0; i < 9 * 9; i++) {
      if ((alice_chess | bob_chess | attack_chess) >> i & 1 ^ 1) {
        int sum = 0;
        for (int j : chess_list) {
          sum += abs(i / 9 - j / 9) + abs(i % 9 - j % 9);
        }
        coor_list.push_back({sum, i});
      }
    }
    chess_list.clear(), sort(coor_list.begin(), coor_list.end());
    int ans_coor = -1;
    for (auto i : coor_list) {
      int _alice_life = alice_life, _bob_life = bob_life;
      LLL _alice_chess = alice_chess, _bob_chess = bob_chess;
      LLL _magic = magic, _attack_chess = attack_chess;
      int _alpha = -beta, _beta = -alpha;
      Operate(i.second,
              _alice_life, _bob_life,
              _alice_chess, _bob_chess,
              _magic, _attack_chess);
      if (_alice_life > 0) {
        if (_bob_life <= 0) {
          alpha = kInf, ans_coor = i.second;
          return ans_coor;
        } else {
          AlphaBeta(_bob_life, _alice_life,
                    _bob_chess, _alice_chess,
                    _magic, _attack_chess,
                    _alpha, _beta, loop - 1);
          if (alpha < -_alpha) {
            alpha = -_alpha, ans_coor = i.second;
            if (alpha >= beta) {
              return ans_coor;
            }
          }
        }
      }
    }
    return ans_coor;
  }

 public:
  /// @param now 0:alice 1:bob
  int Decision(int alice_life, int bob_life,
               LLL alice_chess, LLL bob_chess,
               LLL magic, LLL attack_chess,
               bool now) {
    int alpha = -kInf, beta = kInf;
    if (!now) {
      return AlphaBeta(alice_life, bob_life,
                       alice_chess, bob_chess,
                       magic, attack_chess,
                       alpha, beta);
    } else {
      return AlphaBeta(bob_life, alice_life,
                       bob_chess, alice_chess,
                       magic, attack_chess,
                       alpha, beta);
    }
  }
};