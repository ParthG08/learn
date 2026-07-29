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
    void swap(int &i,int &j){
        int temp = i;
        i = j;
        j = temp;
    }
    int firstMissingPositive(vector<int>& nums) {
        for (auto it = nums.begin(); it != nums.end(); ) {
            if (*it <= 0)
                it = nums.erase(it);  // erase returns next valid iterator
            else
                ++it;
        }

        // cout << "this is the array after the first iteration" << endl;
        // printv(nums);

        int n = nums.size();
        for(int i=0;i<n;i++){
            if(nums[i] > n)continue;
            
            while(nums[i] < n and nums[i] >= 0 and nums[i] != nums[nums[i]-1]){
                swap(nums[i],nums[nums[i]-1]);
            }
        } 

        // cout << "this is the array after the second iteration" << endl;
        // printv(nums);

        int idx = 0;
        while(idx < n){
            if(nums[idx] != idx+1){
                return idx+1;
            }
            idx++;
        }

        return idx+1;
    }
};

int main(){
    Solution sol;
    vector<int> nums = {100000, 3, 4000, 2, 15, 1, 99999};
    int ans = sol.firstMissingPositive(nums);

    cout << "This is the ans : " << ans << endl;
}