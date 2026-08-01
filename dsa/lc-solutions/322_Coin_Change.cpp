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

// This is the top down approach
// give me the bottom up approach instead.

class Solution {
public:
    int recur(int amount, vector<int>& denominations, int i){
        if(amount < 0) return INT_MAX;
        if(amount > 0 && i==denominations.size()) return INT_MAX;
        if(amount == 0) return 0;

        int sameCoin = recur(amount-denominations[i],denominations,i);
        if(sameCoin != INT_MAX) sameCoin += 1;   // FIX

        int changeCoin = recur(amount,denominations,i+1);

        return min(sameCoin, changeCoin);
    }

    int coinChange(vector<int>& coins, int amount) {
        sort(coins.begin(), coins.end(), greater<int>());

        int ans = recur(amount, coins, 0);
        return (ans == INT_MAX ? -1 : ans);   // FIX
    }
};

int main() {
    system("clear");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto start = chrono::high_resolution_clock::now();

    Solution s;
    vector<int> coins = {1,2,5};
    int amount = 11;

    int ans = s.coinChange(coins, amount);
    cout << ans << endl;

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Execution time: " << duration << " microseconds\n";

    return 0;
}