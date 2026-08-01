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
    bool checkIfValid(string& s, unordered_map<string,int> need, int& m){
        for(int j=0;j<s.size();j+=m){
            string part = s.substr(j,m);

            if(need.find(part) != need.end()){
                if(--need[part] < 0){
                    return false;
                }
            }else{
                return false;
            }
        }
        
        return true;
    }
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        int n = words.size();
        int m = words[0].size();      
        int len = s.size();

        unordered_map<string,int> need;
        for(auto word:words){
            need[word]++;
        }
        
        for(int i=0;i<=len-(n*m);i++){
            string str = s.substr(i,m*n);
            bool ans = checkIfValid(str,need,m);
            
            if(ans){
                res.push_back(i);
            }
        }
        return res;
    }
};


int main(){
    system("clear");
    Solution sol;
    string s = "barfoofoobarthefoofoobarthefoobarthe";
    vector<string> res = {"bar","foo","the"};

    auto ans = sol.findSubstring(s,res);
    for(int i:ans){
        cout << i << endl;
    }
}