#include <iostream>
#include <cstdlib>

using namespace std;

void dfs(int vrh, int *matrica_susjedstva, int n, bool posjetio[]) {
  posjetio[vrh] = true; // krecemo od zadanog vrha
  for (int i = 0; i < n; i++) {
    if (matrica_susjedstva[vrh * n + i] != 0 && !posjetio[i]) {
      dfs(i, matrica_susjedstva, n, posjetio); // posjecujemo ostale vrhove
    }      
  }
}

bool isConnected(int *matrica_susjedstva, int n) {
   bool *vis = new bool[n];
 
   for(int i = 0; i < n; i++) {
      vis[i] = false; // svaki vrh stavimo kao neposjecen 
   }

   dfs(0, matrica_susjedstva, n, vis);
   for (int i = 0; i < n; i++) {
      if (!vis[i]) return false;
   }

   return true;
}

// Primov algoritam
// krenem od bilo kojeg vrha (npr. 0)
// nadem njemu susjedan vrh (npr. 4) s najmanjom tezinom
// u iducoj iteraciji krecem od tog (4.) vrha i pazim da ne zatvorim ciklus
int **minSpanningTree(int *mat_tezina, int n) {
   bool *vis = new bool[n];
   int **mat_minSpanTree = new int*[n];

   for (int i = 0; i < n; i++) {
      mat_minSpanTree[i] = new int[n];
      for (int j = 0; j < n; j++) {
         mat_minSpanTree[i][j] = 0;
      }
   }
 
   vis[0] = true;
   for(int i = 1; i < n; i++) {
      vis[i] = false; // svaki vrh (osim prvog) stavimo kao neposjecen 
   }

   int edge_cnt = 0;
   int row, col;

   // jer razapinjuce stablo ima n - 1 bridova
   // petlja staje nakon upisa (n - 1). = npr. 4. brida
   // mogli smo i provjeravati jesu li svi vrhovi posjeceni
   while (edge_cnt < n - 1) { 
      int min = INT_MAX;
      row = 0;
      col = 0;

      for (int i = 0; i < n; i++) { // za svaki vrh
         if (vis[i]) { // ako je vrh posjecen
            for (int j = 0; j < n; j++) {
               // gledamo ostale susjedne neposjecene vrhove (ne smijemo zatvoriti ciklus)
               if (!vis[j] && mat_tezina[i * n + j]) {  
                  if (mat_tezina[i * n + j] < min) {
                     min = mat_tezina[i * n + j];
                     row = i;
                     col = j;
                  } 
               }
            }
         }
      }
      mat_minSpanTree[row][col] = min;
      mat_minSpanTree[col][row] = min;
      vis[col] = true;
      edge_cnt++;
   }

   return mat_minSpanTree;
}

void print2DArray(int** arr, int n) {
   cout << endl;
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
         cout << arr[i][j]<<" ";
      }
       cout << endl;
   }
}

int najduljiBrid(int** arr, int n) {
   int max = 0;
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
         if (arr[i][j] > max) {
            max = arr[i][j];
         }
      }
   }
   return max;
}

void prufer(int **tree, int n) {
   int treeCopy[n][n]; // radim kopiju da ne promijenim matricu tree
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
         treeCopy[i][j] = tree[i][j];
      }
   }

   cout << "(";
   int elementCnt = 0;
   int i = 0;
   while (true) {
      int broj_susjeda = 0;
      int element; // element pruferovog koda
      for (int j = 0; j < n; j++) {
         if (treeCopy[i][j]) {
            broj_susjeda++;
            // ako vrh ima samo jednog susjeda,
            // onda ce taj susjed biti iduci element pruferovog koda
            element = j;
         }
      }

      if (broj_susjeda == 1) { // ako je vrh list
         if (elementCnt == n - 2) break; // prufer uvijek ima n - 2 elemenata
         // izbrisi brid
         treeCopy[i][element] = 0; 
         treeCopy[element][i] = 0;
         cout << element + 1; // ispisi element koda
         elementCnt++; // povecaj brojac elemenata
         if (elementCnt != n - 2) cout << ","; // zarez nakon svakog osim zadnjeg elementa
         i = 0; // resetiraj i
         continue; // preskoci ostatak iteracije i predi na iducu
      }

      i++; // pomakni se na iduci element

      // do ovog ne bi trebalo doci ako imamo stablo
      if (i == n) break; // ako smo dosli do kraja polja, izadi iz petlje
   }

   cout << ")";
}

int main() {
   int n, a, b, c;
   cout << "Unesite prirodan broj n: ";
   cin >> n;

   int mat_tezina[n][n];

   cout << "Unesite prirodan broj a: ";
   cin >> a;
   cout << "Unesite prirodan broj b: ";
   cin >> b;
   cout << "Unesite prirodan broj c: ";
   cin >> c;

   for (int i = 1; i <= n; i++) {
      for (int j = i; j <= n; j++) {
         int tezina = abs(a * i - b * j) / c;
         if (tezina == 0 || i == j) {
            mat_tezina[i - 1][j - 1] = 0;
            mat_tezina[j - 1][i - 1] = 0;
         } else {
            mat_tezina[i - 1][j - 1] = tezina;
            mat_tezina[j - 1][i - 1] = tezina;
         }
      }
   }

   // cout << endl;
   // for (int i = 0; i < n; i ++) {
   //    for (int j = 0; j < n; j++) {
   //       cout << mat_tezina[i][j] << " ";
   //    }  
   //    cout << endl;
   // }

   bool povezan = isConnected(&mat_tezina[0][0], n);
   if (!povezan) {
      cout << "Graf G nije povezan graf";
   } else {
      cout << "Graf G je povezan graf" << endl;
      int **mat_minSpanTree;
      mat_minSpanTree = minSpanningTree(&mat_tezina[0][0], n);
      print2DArray(mat_minSpanTree, n);
      int max = najduljiBrid(mat_minSpanTree, n);
      cout << "Duljina najduzeg brida: " << max << endl; 
      cout << "Pruferov kod minimalnog razapinjuceg stabla: ";
      prufer(mat_minSpanTree, n);
   }

   return 0;
}