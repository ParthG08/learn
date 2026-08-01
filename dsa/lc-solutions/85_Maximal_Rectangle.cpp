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
#define printv(v) for(auto i:v)cout << i << " " ;cout <<endl;
#define inp(v) for(int i=0;i<v.size();i++)cin >> v[i];
#define lb cout << endl;
#define pb(i) push_back(i);
#define C continue;
#define B break;
#define t true;
#define f false;
#define Y cout << "YES" << " \n ";
#define no cout << "NO" << " \n ";
#define sp cout<<" "
#define printvv(v) fo(i,v.size()){{fo(j,v[0].size())cout<<v[i][j]<<" ";}lb}
#define printbool(flag) if(flag){Y;}else{no;}
#define printpv(vec) for(auto p:vec){cout << '{' << p.first << ',' << p.second << '}' << " ";}cout<<endl;
const int mod=1e9+7;
#define maximum_val = 3;

class Solution {
public:
    vector<int> prefixHeight(vector<char> newLayer, vector<int> height){
        int m = newLayer.size();
        for(int i=0;i<m;i++){
            if(newLayer[i] == '0')height[i] = 0;
            else{
                height[i]+=1;
            }
        }
        return height;
    }

    // vector<vector<int>> minimumVals(vector<int> row){
    //     int n = row.size();
    //     vector<vector<int>> dp(n,vector<int> (n));

    //     for(int i=0;i<n;i++){
    //         dp[i][i] = row[i];
    //     }

    //     for(int i=0;i<n;i++){
    //         for(int k=1;i+k<n;k++){
    //             dp[i][i+k] = min(dp[i][i+k-1], row[i+k]);
    //         }
    //     }

    //     return dp;
    // }

    int minimumVals(vector<int> row){
        stack<int> st;  
        int width = 0;
        int ans = row[0];
        for(int i=0;i<row.size();i++){
            if(st.empty()){
                st.push(row[i]);
                width = 1;
            }else{
                if(row[i] == 0){
                    while(!st.empty()) st.pop();
                    width = 0;
                }else if(row[i] > st.top()){
                    width ++;       
                }else{
                    st.push(row[i]);
                    width++;
                }
            }
            ans = min(ans, st.top()*width);
        }

        return ans;
    }

    int maximalRectangle(vector<vector<char>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();

        vector<int> height(m,0);

        for(int i=0;i<m;i++){
            height[i] = matrix[0][i] == '1' ? 1 : 0;
        }

        int ans = INT_MIN;
        vector<int> preHeight(m);
        for(int row=0;row<n;row++){
            if(row == 0) preHeight = height;
            else preHeight = prefixHeight(matrix[row], preHeight);

            int val = minimumVals(preHeight);
            ans = max(ans, val);
        }

        return ans;
    }
};

int main(){
system("clear");
    Solution sol;
    vector<vector<char>> rectangle = {{'1','0','1','0','0'},{'1','0','1','1','1'},{'1','1','1','1','1'},{'1','0','0','1','0'}};
    int ans = sol.maximalRectangle(rectangle);
    
    cout << ans << endl;
}