#include <iostream>
#include <cstdlib>

using namespace std;

void dfs(int vrh, int *matrica_susjedstva, int n, bool posjetio[]) {
  posjetio[vrh] = true; // krecemo od zadanog vrha
  for (int i = 0; i < n; i++) {
    if (matrica_susjedstva[vrh * n + i] == 1 && !posjetio[i]) {
      dfs(i, matrica_susjedstva, n, posjetio); // posjecujemo ostale vrhove
    }      
  }
}

bool isConnected(int *matrica_susjedstva, int n) {
   bool *vis = new bool[n];
 
   for(int j = 0; j < n; j++) {
      vis[j] = false; // svaki vrh stavimo kao neposjecen 
   }

   dfs(0, matrica_susjedstva, n, vis);
   for (int i = 0; i < n; i++) {
      if (!vis[i]) return false;
   }

   return true;
}

// gledamo moze li vrh biti dodan u put
bool isSafe(int vrh, int *matrica_susjedstva, int n, int put[], int pos) {
   // provjera je li vrh susjedan prethodno dodanom vrhu
   if (matrica_susjedstva[put[pos - 1] * n + vrh] == 0) return false;
   // provjera imamo li vec vrh u putu
   for (int i = 0; i < pos; i++) {
      if (put[i] == vrh) return false;
   }   
   return true;
}

bool ham_cycle(int *matrica_susjedstva, int n, int put[], int pos) {
   // ako prodemo sve vrhove
   if (pos == n) {
      // ako je zadnji vrh u ciklusu susjedan prvom, imamo ham cikl
      if (matrica_susjedstva[put[pos - 1] * n + put[0]] == 1)
         return true;
      else
         return false;
   }

   // provjera (za svaki vrh) moze li u ciklus
   for (int vrh = 1; vrh < n; vrh++) {
      if (isSafe(vrh, matrica_susjedstva, n, put, pos)) {
         put[pos] = vrh; // ako je "safe", dodajemo vrh u put
         if (ham_cycle(matrica_susjedstva, n, put, pos + 1)) return true;
         // u slucaju da smo prosli cijelu for petlju i nismo nasli ham
         put[pos] = -1; // ako vrh ne vodi do ham ciklusa, makni ga
      }
   }

   // ako smo prosli sve vrhove i nismo dobili ham ciklus
   return false;
}

bool isHamiltonian(int *matrica_susjedstva, int n) {
   if (n <= 2 || !isConnected(matrica_susjedstva, n)) return false;

   int *put = new int[n];
   for (int i = 0; i < n; i++) {
      put[i] = -1;
   }
   put[0] = 0; // prvi vrh u putu je vrh 0

   if(ham_cycle(matrica_susjedstva, n, put, 1)) return true;
   return false;
}


int main() {
   int n, k[4];
   cout << "Unesite prirodan broj n: ";
   cin >> n;

   int mat_sus[n][n];
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
         mat_sus[i][j] = 0;
      }
   }


   for (int i = 0; i < 4; i++) {
      cout << "Unesite vrijednost prirodnog broja k_" << i + 1 << ": ";
      cin >> k[i];
   }

   for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int razlika = abs(i - j);
      for (int p = 0; p < 4; p++) {
        if (razlika == k[p] && i != j) {
          mat_sus[i - 1][j - 1] = 1;
        }
      }
    }
   } 

   cout << endl;
   // for (int i = 0; i < n; i ++) {
   //    for (int j = 0; j < n; j++) {
   //       cout << mat_sus[i][j] << " ";
   //    }  
   //    cout << endl;
   // }

  bool povezan = isConnected(&mat_sus[0][0], n);
  cout << "Graf G ";
  if (!povezan) {
    cout << "ni";
  }
  cout << "je povezan graf" << endl;

  bool hamiltonovski = isHamiltonian(&mat_sus[0][0], n);
  cout << "Graf G ";
  if (!hamiltonovski) {
    cout << "ni";
  }
  cout << "je hamiltonovski graf" << endl;
  if (hamiltonovski) {
   cout << "Duljina ciklusa je " << n;
  }

  return 0;
}