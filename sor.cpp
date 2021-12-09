#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
     ios_base::sync_with_stdio(false);
     cin.tie(NULL);

     const int mod = 1e9;

     int n;
     cin >> n;

     vector <int> T(n);

     for (int i = 0; i < n; i++)
          cin >> T[i];

     vector< vector<int> > L(n, vector<int>(n, 0));
     vector< vector<int> > R(n, vector<int>(n, 0));

     for (int i = 0; i < n; i++) {
          L[i][i] = 1;
          R[i][i] = 1;
     }

     for (int i = 0; i < n - 1; i++) {
          L[i][i+1] = (T[i] < T[i+1]);
          R[i][i+1] = (T[i] < T[i+1]);
     }

     for (int k = 2; k < n; k++) {
          for (int i = 0; i < n - k; i++) {
               int j = i + k;
               L[i][j] = (L[i+1][j] * (T[i] < T[i+1]) + 
                         R[i+1][j] * (T[i] < T[j])) % mod;
               R[i][j] = (L[i][j-1] * (T[j] > T[i]) + 
                         R[i][j-1] * (T[j] > T[j-1])) % mod;
          }
     }

     if (n > 1)
          cout << (L[0][n-1] + R[0][n-1]) % mod << '\n';
     else
          cout << 1 << "\n";

     return 0;
}