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
    bool compare(int val1, int val2){
        string s1 = to_string(val1) + to_string(val2);
        string s2 = to_string(val2) + to_string(val1);
        return s2 > s1;
    }
    string largestNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [this](int a, int b) {
            return compare(a, b);
        });

        reverse(nums.begin(), nums.end());

        if(nums[0] == 0){
            return "0";
        }

        // for(auto val: nums){
        //     cout << val << "\t";
        // }cout << endl;
        
        string ans = "";
        for(int num: nums){
            ans += to_string(num);
        }

        return ans;
    }
};

int main() {
    system("clear");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto start = chrono::high_resolution_clock::now();

    Solution s;
    vector<int> vec = {3,30,34,5,9};
    string ans = s.largestNumber(vec);

    cout << ans << endl;

    vector<vector<int>> testCases;
    testCases.push_back({0,0});
    testCases.push_back({3,34});
    testCases.push_back({1,9,1000,10000});
    testCases.push_back({22,220,2201,221});

    for(auto testCase: testCases){
        cout << "Result of the vector is : ";
        printv(testCase);

        string ans = s.largestNumber(testCase);
        cout << ans << endl;
    }


    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Execution time: " << duration << " microseconds\n";

    return 0;
}

/*

example test cases:
30 and 3
3 and 31
3 and 34

// edge cases
[0,0,0] --> result should be 0 and not 00
[0,0]

if there are any other characters rather than just 0 then the 0 will be 
significant other wise they are insignificant.

so this case will only arise when there are all zeros. 
(even one single non zero will return a good string)

*/