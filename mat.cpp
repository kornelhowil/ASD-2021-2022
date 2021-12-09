#include <iostream>
using namespace std;

int main(void)
{
     ios_base::sync_with_stdio(false);
     cin.tie(NULL);

     string str;

     cin >> str;
     if (str.length() == 1) {
          cout << 1 << '\n';
     }
     else {
          int min_gw = 1000001;
          int last_index = -1;

          for (int i = 0; i < str.length(); i++) {
               if (str[i] != '*') {
                    if (last_index != -1 && str[i] != str[last_index]) {
                         min_gw = min(min_gw, i - 1 - last_index);
                    }
                    last_index = i;
               }
          }
          if (last_index != -1 && min_gw < 1000001)
               cout << str.length() - min_gw << '\n';
          else
               cout << 1 << '\n';
     }
     return 0;
}