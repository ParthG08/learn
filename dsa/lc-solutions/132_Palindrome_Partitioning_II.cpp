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
#define printv(v) for(const auto& x:(v)) cout<<x<<" "; cout<<"\n";
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
    int minCut(string s) {
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n,false));
        vector<int> jump(n,0);

        for(int i=0;i<n;i++){
            dp[i][i] = true;
            jump[i] = 1;
        }

        for(int i=0;i<n-1;i++){
            if(s[i] == s[i+1]) {
                dp[i][i+1] = true;
                jump[i] = 2;
            }
        }

        for(int len=3; len<=n; len++){
            for(int i=0; i<=n-len; i++){
                int j = i + len - 1;
                if(dp[i+1][j-1] && s[i] == s[j]){
                    dp[i][j] = true;
                    jump[i] = len;  
                }
            }
        }

        vector<int> cuts(n+1, INT_MAX);
        cuts[0] = 0;
        
        for(int i=0; i<n; i++){
            for(int j=i; j<n; j++){
                if(dp[i][j]){
                    cuts[j+1] = min(cuts[j+1], cuts[i] + 1);
                }
            }
        }

        return cuts[n] - 1;
    }
};

int main() {
    system("clear");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto start = chrono::high_resolution_clock::now();

    Solution sol;
    string s = "ababbbabbababa";

    int ans = sol.minCut(s);

    cout << ans << endl;
    // TODO: add code to invoke solution and print output

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Execution time: " << duration << " microseconds\n";

    

    return 0;
}