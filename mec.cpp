#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int main(void)
{
     ios_base::sync_with_stdio(false);
     cin.tie(NULL);

     int n;
     int m;

     cin >> n >> m;

     vector<vector<int> > Gracze(n, vector<int>(m, 0));

     for (int i = 0; i < m; i++) {
          for (int j = 0; j < n; j++) {
               int a;
               cin >> a;

               if (j < n/2)
                    Gracze[a - 1][i] = 0;
               else
                    Gracze[a - 1][i] = 1;
          }
     }

     vector<long long> Liczby(n, 0);

     for (int i = 0; i < n; i++) {
          for (int j = 0; j < m; j++) {
               Liczby[i] += Gracze[i][j] * pow(2, j);
          }
     }

     sort(Liczby.begin(), Liczby.begin() + n);

     bool czy = true;
     for (int i = 0; i < n - 1; i++)
          if (Liczby[i] == Liczby[i + 1])
               czy = false;

     if (czy)
          cout << "TAK\n";
     else
          cout << "NIE\n"; 

     return 0;
}