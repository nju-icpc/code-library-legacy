#include <stdio.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

struct QuadraticResidue {
  typedef long long int64;
  typedef pair<int64, int64> QuadraticNum;

  inline int64 Sqr(int64 a) {
    return a * a;
  }

  int64 Exp(int64 a, int64 n, int64 mod) {
    if (n == 0) return 1;
    if (n & 1) return Sqr(Exp(a, n >> 1, mod)) % mod * a % mod;
    else return Sqr(Exp(a, n >> 1, mod)) % mod;
  }

  int64 inx;
  QuadraticNum QuadraticMul(const QuadraticNum a, const QuadraticNum b, const int mod) {
    QuadraticNum ans;
    ans.first = (a.first * b.first % mod + a.second * b.second % mod * inx % mod) % mod;
    ans.second = (a.first * b.second % mod + a.second * b.first % mod) % mod;
    return ans;
  }

  QuadraticNum Sqr(QuadraticNum a, int mod) {
    return QuadraticMul(a, a, mod);
  }

  QuadraticNum Exp(QuadraticNum a, int n, int mod) {
    if (n == 0) return QuadraticNum(1, 0);
    if (n & 1) return QuadraticMul(Sqr(Exp(a, n >> 1, mod), mod), a, mod);
    else return Sqr(Exp(a, n >> 1, mod), mod);
  }

  int GetRoot(int n, int m) {
    n = (n % m + m) % m;
    if (n == 0) return 0;
    if (m == 2) return 1;
    if ((Exp(n, (m - 1) / 2, m) + m) % m == m - 1) return -1;
    // x does not exist.
    while (true) {
      int i = rand() % m;
      inx = ((int64)i * i - n) % m;
      if ((Exp(inx, (m - 1) / 2, m) + m) % m == m - 1) {
        int x = (Exp(QuadraticNum(i, 1), (m + 1) / 2, m).first + m) % m;
        int y = m - x;
        if (x > y) swap(x, y);
        return x;
      }
    }
  }
};

// This shows how to use it. 
// You can submit on http://acm.timus.ru/problem.aspx?space=1&num=1132
int main() {
  int t, n, m;
  QuadraticResidue quadratic_residue;
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &m);
    int root = quadratic_residue.GetRoot(n, m);
    if (root == -1)
      printf("No root\n");
    else {
      if (root + root == m) printf("%d\n", root);
      else printf("%d %d\n", root, m - root);
    }
  }
  return 0;
}
