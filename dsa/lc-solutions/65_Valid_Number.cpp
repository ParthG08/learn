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

class Solution {
public:
    bool isNumber(string s) {
        while(!s.empty() && s[0] == ' ') s = s.substr(1);
        while(!s.empty() && s[s.size()-1] == ' ') s = s.substr(0, s.size()-1);
        
        int i = 0;
        while(s[i] == '+' || s[i] == '-')i++;
        
        int digits_before_decimal = 0;
        int digits_after_decimal = 0;
        int digits_after_exponent = 0;
        int index_of_e = -1;
        bool isAfterExponent = false;
        bool isAfterDecimal = false;
        
        int n = s.size();
        for(int i=0;i<n;i++){
            if(s[i] == '-' || s[i] == '+'){
                if(i == 0 || (isAfterExponent && i == index_of_e+1))continue;
                else return false;
            }
            else if(isdigit(s[i])){
                if(isAfterExponent){
                    digits_after_exponent ++;
                }
                else if(isAfterDecimal){
                    digits_after_decimal ++;
                }else{
                    digits_before_decimal ++;
                }
            }else if(s[i] == '.'){
                if(isAfterExponent)return false;

                if(isAfterDecimal)return false;
                else isAfterDecimal = true;
            }else if(s[i] == 'e' || s[i] == 'E'){
                if(isAfterExponent) return false;
                else isAfterExponent = true;
                index_of_e = i;
            }else{
                return false;
            }
        }

        if((digits_after_decimal == 0 && digits_before_decimal == 0) || (digits_after_exponent == 0 && isAfterExponent))return false;
        else return true;
    }
};

int main() {
    system("clear"); // optional
    Solution sol;

    // Test cases for LeetCode valid number problem
    vector<pair<string, bool>> testCases = {
        {"+1.123", true},
        {"0", true},
        {" 0.1 ", true},
        {"abc", false},
        {"1 a", false},
        {"2e10", true},
        {" -90e3   ", true},
        {" 1e", false},
        {"e3", false},
        {" 6e-1", true},
        {" 99e2.5 ", false},
        {"53.5e93", true},
        {" --6 ", false},
        {"-+3", false},
        {"95a54e53", false},
        {".1", true},
        {".", false},
        {"3.", true},
        {"+.8", true},
        {" 005047e+6", true}
    };

    // Run test cases
    for (auto &[input, expected] : testCases) {
        bool ans = sol.isNumber(input);
        cout << "Input: \"" << input << "\" | Output: ";
        printbool(ans);
        cout << " | Expected: ";
        printbool(expected);
        cout << "--------------------------" << endl;
    }

    return 0;
}
