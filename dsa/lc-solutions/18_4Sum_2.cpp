#include <bits/stdc++.h>
using namespace std; 
#define fo(a,b) for(int a=0;a<b;a++)
#define loop(a, b, c) for(int a=b; a<c; a++)
#define all(x) (x).begin(), (x).end()
#define vi vector<int>
#define vvi vector<vi>
#define bs binary_search
#define pii pair<int, int>
#define mem(a, b) memset(a, b, sizeof(a))
#define printv(v) for(int i=0;i<v.size();i++)cout << v[i] << " " ;cout <<endl;
#define inp(v) for(int i=0;i<v.size();i++)cin >> v[i];
#define lb cout << endl;
#define pb(i) push_back(i);
#define C continue;
#define B break;
#define f false;
#define Y cout << "YES" << endl;
#define no cout << "NO" << endl;
#define printvv(v) fo(i,v.size()){{fo(j,v[0].size())cout<<v[i][j]<<" ";}lb}
#define printbool(flag) if(flag){Y;}else{no;}
const int mod=1e9+7;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        int n = nums.size();
        sort(nums.begin(),nums.end());

        for(int i=0;i<n;i++){
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            for(int j=i+1;j<n;j++){
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;

                int k = j+1;
                int l = n-1;
                
                while(k<l){
                    long long sum = nums[i];sum += nums[j];sum += nums[k];sum += nums[l];
                    if(sum == target){
                        vector<int> ans = {nums[i],nums[j],nums[k],nums[l]};
                        res.push_back(ans);

                        k++;l--;

                        while(k<l and nums[k] == nums[k-1])k++;
                        while(k<l and nums[l] == nums[l+1])l--;
                    }else if(sum > target){
                        l--;
                    }else{
                        k++;
                    }
                }
            }
        }

        return res;
    }
};

int main(){
    Solution sol;
    vector<int> vec = {1,0,-1,0,-2,2};
    int target = 0;
    vector<vector<int>> res = sol.fourSum(vec,target);


    printvv(res);
}