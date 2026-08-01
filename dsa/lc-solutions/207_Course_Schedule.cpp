#include <bits/stdc++.h>
using namespace std;

#define fo(a,b) for(int a=0;a<b;a++)
#define loop(a,b,c) for(int a=b;a<c;a++)
#define all(x) (x).begin(),(x).end()
#define vi vector<int>
#define vvi vector<vi>
#define bs binary_search
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))
#define printv(v) for(const auto& x:(v)) cout<<x<<" "; cout<<"\n";}
#define inp(v) for(int i=0;i<(int)v.size();i++) cin>>v[i]
#define lb cout<<"\n"
#define pb push_back
#define C continue
#define B break
#define t true
#define f false
#define Y cout<<"YES\n"
#define no cout<<"NO\n"
#define sp cout<<" "
#define printvv(v) fo(i,v.size()){fo(j,v[0].size()) cout<<v[i][j]<<" "; lb;}
#define printbool(flag) if(flag){Y;}else{no;}
#define printpv(vec) do{for(auto p:vec) cout<<'{'<<p.first<<','<<p.second<<"} "; cout<<"\n";}while(0)

const int mod = 1e9 + 7;

class Solution {
public:
    bool dfs(vector<vector<int>> &graph, int node, vector<bool>& visited){
        if(visited[node]) return true;

        visited[node] = true;

        bool cycle = false;
        for(int nb: graph[node]){
            cycle |= dfs(graph, nb, visited);
        }

        return cycle;
    }
    bool canFinish(int numCourses, vector<vector<int>>& pre) {
        int n = numCourses;
        vector<bool> visited(n,false);

        vector<vector<int>> graph(n);
        for(int i=0;i<pre.size();i++){
            graph[pre[i][1]].push_back(pre[i][0]);
        }

        for(int i=0;i<n;i++){   
            if(!visited[i] && dfs(graph, i, visited)){
                return false;
            }
        }

        return true;
    }
};

int main(){
    Solution s;
    vector<vector<int>> v = {{0,1}};
    bool ans = s.canFinish(2, v);

    printbool(ans);
}