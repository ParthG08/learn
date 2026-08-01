// https://leetcode.com/problems/gray-code/

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

class Solution {
public:
    vector<int> grayCode(int n) {
        int size = 1 << n;
        vector<int> v;
        v.reserve(size);

        for (int i = 0; i < size; i++) {
            v.push_back(i ^ (i >> 1));
        }

        return v;
    }
};



int main() {
    system("clear");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;
    vector<int> ans = sol.grayCode();

    printv(ans);
    return 0;
}

