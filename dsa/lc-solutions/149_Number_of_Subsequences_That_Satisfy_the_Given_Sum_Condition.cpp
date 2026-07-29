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
    int numSubseq(vector<int>& nums, int target) {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        int i = 0, j = n - 1;
        int ans = 0;

        vector<int> pow2(n);
        pow2[0] = 1;

        //precalculation kardiya caching ke liye
        for (int k = 1; k < n; k++) {\
            pow2[k] = (pow2[k - 1] * 2) % 1000000007;
        }

        while (i <= j) {
            if (nums[i] + nums[j] <= target) {
                ans = (ans + (int)pow2[j - i]) % mod;
                i++;
            } else {
                j--;
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
    vector<int> vec = {3,3,6,8};
    int ans = s.numSubseq(vec,10);

    cout << ans << endl;
    return 0;
}