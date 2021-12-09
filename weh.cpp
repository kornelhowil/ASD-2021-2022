#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int BFS(vector< vector<int> > graph, int n, vector<int> &min_path)
{
     int source = 1;
     int destination = n;

     vector<int> distance(n + 1, -1);
     vector<int> parent(n + 1, -1);
     distance[source] = 1;
     queue<int> q;
     q.push(source);
     while(!q.empty()) {
          int v = q.front();
          q.pop();

          for (int u: graph[v]) {
               if (distance[u] == -1) {
                    q.push(u);
                    distance[u] = distance[v] + 1;
                    parent[u] = v;
               }
          }
     }
     if (distance[destination] != -1) {
          int u = destination;
          while (u != -1) {
               min_path.push_back(u);
               u = parent[u];
          }
          reverse(min_path.begin(), min_path.end());
     }
     return distance[destination];
}

int charging(vector<int> forbidden, vector<int> energy, int p, int k, int z, int distance, vector<int> &charge_loc) {
     vector<bool> allowed(p + 1, true);

     for (int i = 0; i < z; i++)
          allowed[forbidden[i]] = false;
     // dp[i][j] oznacza czy mogę być w odległości j mając energię i
     vector< vector<bool> > dp(p + 1, vector<bool>(distance, false));
     // zaczynam w odległości 0 mając energię p, więc dp[p][0] = true
     dp[p][0] = true;
     // dla mniejszych energii oczywiście false
     for (int i = 0; i < p; i++)
          dp[i][0] = false;

     for (int j = 1; j < distance; j++) {
          for (int i = 0; i <= p; i++) {
               int e = i + k; // jeśli nie ładujemy
               int e_add = i + k - energy[j]; // jeśli ładujemy

               if (allowed[i]) {
                    if (e_add <= p and e_add >= k)
                         dp[i][j] = dp[i][j] or dp[e_add][j - 1];
                    if (e <= p and e > 0)
                         dp[i][j] = dp[i][j] or dp[e][j - 1];
               }
               else if (e <= p and e > 0)
                    dp[i][j] = dp[e][j - 1];
          }
     }
     int power = -1;
     for (int i = p; i >= 0; i--) {
          if (dp[i][distance - 1]) {
               power = i;
               break;
          }
     }
     int i = power;
     if (i != -1) {
          for (int j = distance - 1; j > 0; j--) {
               int e = i + k;
               int e_add = i + k - energy[j];

               if (e <= p and dp[e][j - 1])
                    i = e;
               else {
                    charge_loc.push_back(j);
                    i = e_add;
               }
          }
          if (!charge_loc.empty())
               reverse(charge_loc.begin(), charge_loc.end());
     }
     return power;
}

int main(void)
{
     ios_base::sync_with_stdio(false);
     cin.tie(NULL);

//   Wczytywanie
     
     int p, k, z;
     cin >> p >> k >> z;

     vector<int> forbidden(z);
     for (int i = 0; i < z; i++)
          cin >> forbidden[i];
     
     int n, m;
     cin >> n >> m;

     vector< vector<int> > graph(n + 1);

     for (int i = 0; i < m; i++) {
          int u, v;
          cin >> u >> v;
          graph[u].push_back(v);
          graph[v].push_back(u);
     }
     
     vector<int> energy(n);
     for (int i = 0; i < n; i++)
          cin >> energy[i];
     
//   Najkrótsza ścieżka
     vector<int> min_path;
     int distance = BFS(graph, n, min_path);
//   Jeśli nie znalezniono ścieżki wypisujemy -1
     if (distance == -1)
          cout << -1 << "\n";
     else {
//   Szukamy maksymalnej energii i stacji ładowania
          vector<int> charge_loc;
          int final_energy = charging(forbidden, energy, p, k, z, distance, charge_loc);
//   Jeśli nie znaleniono ścieżki spełniającej warunki energii wypisujemy -1
          if (final_energy == -1)
               cout << -1 << "\n";
          else {
               cout << distance << " " << final_energy << " " <<  charge_loc.size() <<"\n";
               for (int i = 0; i < distance; i++)
                    cout << min_path[i] << " ";
               cout << "\n";
               for (int u: charge_loc)
                    cout << min_path[u] << " ";
               cout << "\n";
          }
     }
     return 0;
}