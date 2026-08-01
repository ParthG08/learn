// /https://leetcode.com/problems/minimum-window-substring/description/

//THis solution didnt work
// i made the prefix array of each of the 52 characters in the string
// a-Z from small a to capital Z so the space required is 52
// Now what is did was i searched for the prefix that is required subtracting the final string that we need
// i search for the goal in a backward manner and only before the index i
// id doubt weather the code was right for this or not and also the GPT told me that hte index is one off when calculating 
//using the distance function so that anotherm thing so make sure you are able to do this correctly the next time


// also look for what others did in this question i think that my approach is a bit straight forward.



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


//ADOBECODEBANC

class Solution {
public:
    string minWindow(string s, string t) {
        int n = s.size();
        vector<vector<int>> pre(n+1,vector<int>(60));
        unordered_set<char> st;

        vector<int> wf(60);
        int m = t.size();
        for(int i=0;i<m;i++){
            wf[t[i]-'A']++;
            st.insert(t[i]);
        }

        // for(int i=0;i<60;i++){
        //     cout << wf[i] << " ";
        // }cout << endl;

        int min_ans = n;
        pair<int,int> ans = {-1,-1}; 

        for(int i=1;i<=n;i++){
            for(int j=0;j<60;j++){
                pre[i][j] = pre[i-1][j];
            }
            
            if(st.find(s[i-1]) != st.end()){
                pre[i][s[i-1]-'A']++;
            }
            
            // for(auto z=0;z<60;z++){
            //     cout << pre[i][z] << " ";
            // }cout << endl;

            vector<int> goal(60);
            bool possible = true;

            for(int j=0;j<60;j++){
                int val = pre[i][j] - wf[j];
                if(val < 0){
                    possible = false;
                    break;
                }

                goal[j]= val;
            }

            // cout << "\n\n\n this is the" << i << "th index" << "\n\n\n";
            // cout << "this is the pre" << endl;
            // for(auto y=0;y<60;y++){
            //     cout << pre[i][y] << " ";
            // }cout << endl;

            // cout << "this is the goal" << endl;
            // for(auto z=0;z<60;z++){
            //     cout << goal[z] << " ";
            // }cout << endl;cout << possible << endl;;

            if(possible){
                auto it = std::find(pre.rbegin() + (pre.size() - i - 1), pre.rend(), goal);
                int index = -1;
                if(it != pre.rend()){
                    index = std::distance(pre.begin(), it.base());
                    index -=1;
                    cout << "this is the index at which the vector was found : " << index << " this is the value of the i:" << i << endl;
                    // for(auto i=0;i<60;i++){
                    //     cout << pre[index][i] << " ";
                    // }cout << endl;
                    // cout << "this wasnt" << endl;
                    // printv(goal);cout << i << "   |   " << index << endl;

                    if(index == n){
                        continue;
                    }else if(index >= i){
                            return s.substr(i,1);
                    }else if((i-index) <= min_ans){
                        min_ans = i-index;
                        ans = {index,i};

                        cout << ans.first <<  " " << ans.second << endl;
                    }
                }
            }
        }

        if(ans.first== -1){
            return "";
        }else{
            return s.substr(ans.first,ans.second-ans.first+1);
        }
    }
};


int main(){
    Solution sol;
    string minWindow = sol.minWindow("ab","a");


    cout << minWindow << endl;
}