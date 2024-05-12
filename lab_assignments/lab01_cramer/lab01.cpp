#include <iostream>

using namespace std;

int main() {

  double bn;
  double b[3], c[3];
  double lambda1, lambda2;
  int n;

  do {
    cout << "Unesite nenegativan cijeli broj: ";
    cin >> n;
  } while (n < 0);

  for (int i = 0; i < 3; i++) {
    cout << "Unesite vrijednost broja b_" << i << ": ";
    cin >> b[i];
  }

  for (int i = 0; i < 3; i++) {
    cout << "Unesite vrijednost broja c_" << i << ": ";
    cin >> c[i];
  }

  if (n <= 2) {
    bn = b[n];
    cout << fixed << "Vrijednost broja b_n: " << bn;

  } else {

    // bn = lambda1 * bnminus1 + lambda2 * bnminus2
    // cn = lambda1 * cnminus1 + lambda2 * cnminus2
    double bnminus2 = b[0], bnminus1 = b[1], bn = b[2];
    double cnminus2 = c[0], cnminus1 = c[1], cn = c[2];

    // cramer
    double determinant = bnminus1 * cnminus2 - bnminus2 * cnminus1;
    if (determinant != 0) {
      lambda1 = (bn * cnminus2 - cn * bnminus2) / determinant;
      lambda2 = (bnminus1 * cn - bn * cnminus1) / determinant;
      // cout << "lambda1 = " << lambda1 << endl;
      // cout << "lambda2 = " << lambda2 << endl;

      for (int i = 1; i < n ; i++) {
        bn = lambda1 * bnminus1 + lambda2 * bnminus2;
        bnminus2 = bnminus1; // prevprev = prev;
        bnminus1 = bn;       // prev = curr;
      }

      cout << fixed << "Vrijednost broja b_n: " << bn;

    } else {
      cout << "Ima ili 0 ili beskonacno rjesenja za lambde" << endl;
    }
  }

  return 0;
}