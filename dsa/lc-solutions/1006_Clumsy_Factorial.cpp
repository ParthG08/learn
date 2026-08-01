// https://leetcode.com/problems/clumsy-factorial/description/
// This was pretrty easy just using mathematics made a little bit of silly mistakes and didnt rdry run all the test cases
// dry run all the test cases that will point out the mistakes in your solution.

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
    int clumsy(int n) { 
        long long int ans = 0;
        bool first = true;
        while(n>4){
            int val = n-2;
            ans += (first ? (val*2+2) : -4);

            if(first)first = false;
            n-=4;
        }

        if(n==4){
            ans += (first ? 7 : -5);
        }else if(n==3){
            ans += (first ? 6 : -6);
        }else if(n==2){
            ans += (first ? 2 : -2);
        }else {
            ans += (first ? 1 : -1);
        }

        return ans;
    }
};

int main(){
    Solution sol;
}