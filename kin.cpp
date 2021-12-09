#include <iostream>
#include <vector>
using namespace std;

int mod = 1e9;

class IntervalTree {
     int size;
     vector<long long> tab;

     public: 
          IntervalTree(int n) {
               int i = 1;
               while (i < 2 * n)
                    i *= 2;

               tab.resize(i);
               size = i;
          }

          void clear() {
               for (int i = 0; i < size; i++)
                    tab[i] = 0;
          }

          void add(int i, int val) {
               int pos = size / 2 + i - 1;
               for (int k = pos; k > 0; k /= 2 ) {
                    tab[k] += val;
                    tab[k] = tab[k] % mod;
               }
          }

          int sum(int i) {
               long long sum = 0;
               int l = size / 2 + i - 1;
               int r = size - 1;

               if (l < r) {
                    sum += tab[l];
                    sum += tab[r];
                   while (l/2 != r/2) {
                         

                         if (l % 2 == 0)
                              sum += tab[l + 1];

                         sum += tab[r - 1];

                         l /= 2;
                         r /= 2; 
                         sum = sum % mod;
                    }
               }
               else if (l == r)
                    sum = tab[l];

               return sum % mod; 
          }
};

int main(void)
{
     ios_base::sync_with_stdio(false);
     cin.tie(NULL);

     int n, k;
     cin >> n >> k;

     vector<int> A(n);

     for (int i = 0; i < n; i++) {
          cin >> A[i];
     }

     vector<int> T(n, 1);
     IntervalTree Tree(n);
     for (int i = 2; i <= k; i++) {
          for (int j = 0; j < n; j++) {
               Tree.add(A[j], T[j]);
               T[j] = Tree.sum(A[j] + 1);
          }
          Tree.clear();
     }

     long long sum = 0;
     for (int i = 0; i < n; i++) {
          sum += (T[i] % mod);
          sum = sum % mod;
     }

     cout << sum % mod;
     return 0;
}