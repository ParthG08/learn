// https://leetcode.com/problems/4sum/description/


// This is the solution that i thought of of this question 
// the approach was that similiar to what we did for the 3 pointer approach we will ues a hash set to store the
// last unique element use 3 for loops for the other three elements.


// But there is another approach one that eliminates the hash set
// the approach will acutally be to use two fixed elements and two moving elements

// this way there is no memory usage that is extra and also there is no set that you will use to finally 
// get the unique answers as you can actually skip for two same elements

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
        map<long long int,int> mp;
        set<vector<int>> st;

        int n = nums.size();

        vector<vector<int>> res;
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                for(int k=j+1;k<n;k++){
                    long long int targetFind = target - (nums[i] + nums[j] + nums[k]);
                    if(mp.find(targetFind) != mp.end()){
                        vector<int> ans;
                        ans.push_back(int(targetFind));
                        ans.push_back(nums[i]);
                        ans.push_back(nums[j]);
                        ans.push_back(nums[k]);
                        sort(ans.begin(),ans.end());

                        st.insert(ans);
                    }
                }
            }
            mp[nums[i]] = i;
        }

        for(auto it = st.begin();it != st.end(); it++){
            res.push_back(*it);
        }

        return res;
    }
};


int main(){
    Solution sol;
    vector<int> vec =  {1000000000,1000000000,1000000000,1000000000};
    int target = 0;
    vector<vector<int>> res = sol.fourSum(vec,target);

    printvv(res);
}