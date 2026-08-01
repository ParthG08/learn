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
    bool search(vector<int>& nums, int target) {
        if(nums.size() == 0)return false;
        if(nums.size() == 1 && nums[0] == target) return true;

        int left=0,right=nums.size()-1;
        int mid = left + (right-left)/2;

        while(left<=right){
            mid = left + (right-left)/2;
            if(nums[mid] == target) return true;

            if( (nums[left] == nums[mid]) && (nums[right] == nums[mid]) ) {++left; --right;}
            else if(nums[left] <= nums[mid])
            {
                if( (nums[left]<=target) && (nums[mid] > target)) right = mid-1;
                else left = mid + 1; 
            }
            else
            {
                if((nums[mid] < target) &&  (nums[right] >= target)) left = mid+1;
                else right = mid-1;
            }
        }
    }
};


int main() {
    system("clear");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution s;
    return 0;
}