#include <iostream>
using namespace std;

int main(void)
{
     ios_base::sync_with_stdio(false);
     cin.tie(NULL);

     int n; // liczba produktów dostępnych na bazarku
     cin >> n;

     int* price = new int[n]; // tablica cen
     for (int i = 0; i < n; i++)
          cin >> price[i];

     int m; // liczba dni, które Bajtek spędzi u babci
     cin >> m;
     
     int* no_prod = new int[m]; // tablica ilości produktów
     for (int i = 0; i < m; i++)
          cin >> no_prod[i];
     
     long long* sums = new long long[n]; // tablica sum cen
     sums[n - 1] = price[n - 1];
     for (int i = n - 2; i >= 0; i--)
          sums[i] = sums[i + 1] + price[i];

     
     int* maxle = new int[n]; // maksymalny parzysty element od lewej
     int* maxlo = new int[n]; // maksymalny nieparzysty element od lewej

     if (price[0] % 2 == 0) {
          maxle[0] = price[0];
          maxlo[0] = -1;
     }
     else {
          maxle[0] = -1;
          maxlo[0] = price[0];
     }
     for (int i = 1; i < n; i++) {
          if (price[i] % 2 == 0){
               maxle[i] = price[i];
               maxlo[i] = maxlo[i - 1];
          }
          else {
               maxle[i] = maxle[i - 1];
               maxlo[i] = price[i];
          }
     }

     int* minre = new int[n]; // minimalny parzysty element od prawej
     int* minro = new int[n]; // minimalny nieparzysty element od prawej

     if (price[n - 1] % 2 == 0) {
          minre[n - 1] = price[n - 1];
          minro[n - 1] = -1;
     }
     else {
          minre[n - 1] = -1;
          minro[n - 1] = price[n - 1];
     }
     for (int i = n - 2; i >= 0; i--) {
          if (price[i] % 2 == 0){
               minre[i] = price[i];
               minro[i] = minro[i + 1];
          }
          else {
               minre[i] = minre[i + 1];
               minro[i] = price[i];
          }
     }

     // iterujemy po dniach
     for (int i = 0; i < m; i++) {
          int beg = n - no_prod[i];

          if (no_prod[i] > n) {
               cout << -1 << '\n';
          }
          else {
               if (sums[beg] % 2 == 1) {
                    cout << sums[beg] << '\n';
               }
               else {
                    if (n == no_prod[i]) {
                         cout << -1 << '\n';
                    }
                    else {
                         if ((minre[beg] != -1 && maxlo[beg - 1] != -1) || (minro[beg] != -1 && maxle[beg - 1] != -1)) {
                              long long sum1;
                              long long sum2;
                              if (minre[beg] != -1 && maxlo[beg - 1] != -1)
                                   sum1 = sums[beg] - minre[beg] + maxlo[beg - 1];
                              else
                                   sum1 = -1;

                              if (minro[beg] != -1 && maxle[beg - 1] != -1)
                                   sum2 = sums[beg] - minro[beg] + maxle[beg - 1];
                              else
                                   sum2 = -1;

                              cout << max(sum1, sum2) << '\n';
                         }
                         else {
                              cout << -1 << '\n';
                         }
                    }
               }
          }
     }

     delete[] price;
     delete[] no_prod;
     delete[] sums;
     delete[] maxle;
     delete[] maxlo;
     delete[] minre;
     delete[] minro;
     return 0;
}