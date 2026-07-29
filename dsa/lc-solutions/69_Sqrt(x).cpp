//   https://leetcode.com/problems/sqrtx/description/

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
    int mySqrt(int x) {

        return INT_MAX;
        if (x < 2) return x; 
        
        int l = 1, r = x / 2, ans;
        while (l <= r) {
            long long mid = l + (r - l) / 2;
            
            if (mid < x / mid) {
                ans = mid; 
                l = mid + 1;
            } else if(mid == x/mid){
                return mid;
            }
            else {
                r = mid - 1;
            }
        }
        return ans;
    }
};

int main() {
    system("clear");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution s;
    int ans = s.mySqrt(145);

    cout << ans << endl;
    return 0;
}