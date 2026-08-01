//got hte core logic right but was looking at the problem from a 
// total vector array mindet didnt think that for getting the common prefix
// we can use left shift and right shift
// next time think more of left shift and right shoft first 
// to solve any problem like this.

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
#define printv(v) do { for(const auto& x : v) cout << x << " "; cout << "\n"; } while(0)
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
    int rangeBitwiseAnd(int left, int right) {
        int count = 0;
        while(left != right){    
            left >>= 1;
            right >>= 1; 
            count ++;
        }

        return (left << count);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution s;

    // Test Case 1: Standard
    cout << "Test 1 (5, 7): " << s.rangeBitwiseAnd(5, 7) << " (Expected: 4)" << endl;

    // Test Case 2: No common bits
    cout << "Test 2 (0, 1): " << s.rangeBitwiseAnd(0, 1) << " (Expected: 0)" << endl;

    // Test Case 3: Large range
    cout << "Test 3 (1, 2147483647): " << s.rangeBitwiseAnd(1, INT_MAX) << " (Expected: 1)" << endl;

    // Test Case 4: Identical
    cout << "Test 4 (10, 10): " << s.rangeBitwiseAnd(10, 10) << " (Expected: 10)" << endl;

    return 0;
}