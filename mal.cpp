#include <iostream>
#include <set>
#include <utility>

using namespace std;

int add_to_set(set<pair<int, int>> &autostrada, int sum, int a, int b, char c)
{
     if (autostrada.empty()) {
          if (c == 'B') {
              autostrada.insert(make_pair(a, b));
               sum += (b - a + 1);  
          }
     }
     else {
          auto start = autostrada.lower_bound(make_pair(a, -1));
          auto end = autostrada.lower_bound(make_pair(b, -1));

          if (start == autostrada.end())
               start = autostrada.begin();

          if (start != autostrada.begin())
               start--;

          if (end != autostrada.end())
               end++;

          for (auto it = start; it != end;) {
               int x = it->first;
               int y = it->second;
               if (x >= a and y <= b) {
                    sum -= (y - x + 1);
                    it = autostrada.erase(it);
               }
               else if (x < a and y > b) {
                    autostrada.insert(make_pair(x, a - 1));
                    autostrada.insert(make_pair(b + 1, y));
                    sum -= (b - a + 1);
                    it = autostrada.erase(it);
               }
               else if (x < a and y >= a) {
                    autostrada.insert(make_pair(x, a - 1));
                    sum -= (y - a + 1);
                    it = autostrada.erase(it);
               }
               else if (x <= b and y > b) {
                    autostrada.insert(make_pair(b + 1, y));
                    sum -= (b - x + 1);
                    it = autostrada.erase(it);
               }
               else {
                    it++;
               }
          }
          if (c == 'B') {
               autostrada.insert(make_pair(a, b));
               sum += (b - a + 1);
          }
     }

     return sum;
}

int main(void)
{
     ios_base::sync_with_stdio(false);
     cin.tie(NULL);

     int n; // Długość autostrady
     cin >> n; 
     int m; // Suma dni
     cin >> m;

     set<pair<int, int>> autostrada;
     int sum = 0;

     for (int i = 0; i < m; i++) {
          int a, b;
          char c;
          cin >> a >> b >> c;
          sum = add_to_set(autostrada, sum, a, b, c);
          cout << sum << "\n";
     }
     
     return 0;
}