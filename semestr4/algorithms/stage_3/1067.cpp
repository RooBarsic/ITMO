/*
problem : 1067. Disk Tree
http://acm.timus.ru/problem.aspx?space=1&num=1067
Построим структуру данных на подобие Бора
в каждой вершине будет название этой вершины и
указатели на другие подкаталоги этого каталога

Time complexitu O(M) where M - number of directories
*/
# include <bits/stdc++.h>
# define sz(s) int(s.size())
# define ll long long
  using namespace std;
  struct DiskNode{
      string name;
      map< string, DiskNode* > subdirectories;
  };
  void print_directories(DiskNode *node, string indent){
      cout << indent << node->name << '\n';
      indent += " ";
      for(auto it = node->subdirectories.begin(); it != node->subdirectories.end(); it++){
          print_directories(it->second, indent);
      }
  }
  void solve(){
      int n;
      string s, t;
      cin >> n;
      DiskNode *tree = new DiskNode();
      tree->name = "";
      for(int i = 1; i <= n; i++){
          cin >> s;
          s += "\\";
          t = "";
          DiskNode *node = tree;
          for(int j = 0, kpf = sz(s); j < kpf; j++){
              if(s[j] == '\\'){
                  auto it = node->subdirectories.find(t);
                  if(it == node->subdirectories.end()){
                      DiskNode *new_node = new DiskNode();
                      new_node->name = t;
                      node->subdirectories[t] = new_node;
                      it = node->subdirectories.find(t);
                  }
                  node = it->second;
                  t = "";
              }
              else t += s[j];
          }
      }
      for(auto it = tree->subdirectories.begin(); it != tree->subdirectories.end(); it++){
        print_directories(it->second, "");
      }
  }
  int main()
  {
      int t = 1;
      while(t > 0){
          solve();
          t--;
          cout << '\n';
      }
      return 0;
  }
