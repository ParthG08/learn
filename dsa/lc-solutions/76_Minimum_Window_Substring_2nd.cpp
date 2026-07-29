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
#define Y cout<<"YES\n"
#define no cout<<"NO\n"
#define sp cout<<" "
#define printvv(v) fo(i,v.size()){fo(j,v[0].size()) cout<<v[i][j]<<" "; lb;}
#define printbool(flag) if(flag){Y;}else{no;}
#define printpv(vec) do{for(auto p:vec) cout<<'{'<<p.first<<','<<p.second<<"} "; cout<<"\n";}while(0)

const int mod = 1e9 + 7;

class Solution {
public:
    string minWindow(string s, string t) {
        if(s.size() < t.size()) return "";

        unordered_map<char,int> targetCount;
        unordered_map<char,int> windowCount;

        // FIX 1: Map the target string 't'
        for(char c: t) targetCount[c]++;

        int formed = 0; 
        int right = 0, left = 0;
        int required = targetCount.size(); 
        int minLength = INT_MAX;
        int bestLeft = 0;

        

        while(right < s.size()){
            char c = s[right];
            windowCount[c]++;

            if(targetCount.count(c) && windowCount[c] == targetCount[c]){
                formed++;
            }

            while(left <= right && formed == required){
                if(right - left + 1 < minLength){
                    minLength = right - left + 1;
                    bestLeft = left;
                }

                char remChar = s[left];
                windowCount[remChar]--;

                // FIX 2 & 3: Compare values, not .count()
                if(targetCount.count(remChar) && windowCount[remChar] < targetCount[remChar]){
                    formed--;
                }
                left++;
            }
            right++;
        }

        return (minLength == INT_MAX) ? "" : s.substr(bestLeft, minLength);
    }
};

int main() {
    system("clear");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution s;
    string str = "ADOBECODEBANC", t = "ABC";
    string ans = s.minWindow(str,t);

    cout << ans << endl;
    return 0;
}