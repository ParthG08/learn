//https://leetcode.com/problems/basic-calculator/description/
// Basic Calculator

//I solved this question using the recursion so for each bracket it calls the function making it call about as many times 
// as there is depth of the brackets in the string


// what you can do instead acutally is basically you can make the it an O(n) solution by using the stack data structure
// now submit another solution called basic calculator 2 with the stack solution.


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
    int calculateBracket(const string &s, int &idx, bool isPositive){
        string str = "";
        int bracket = 1;
        while(bracket != 0 && idx < s.size()){
            if(s[idx] == '('){
                bracket++;
            } else if(s[idx] == ')'){
                bracket--;
            }
            if(bracket != 0){
                str += s[idx++];
            }
        }
        return (isPositive ? 1 : -1) * evaluate(str, 0, true, 0);
    }

    int evaluate(const string &s, int idx, bool isPositive, int ans){
        bool isThisCharPositive = true;
        while(idx < s.size()){
            char c = s[idx];
            if(c == ' '){
                idx++;
                continue;
            } else if(c == '('){
                int newIdx = idx + 1;
                ans += calculateBracket(s, newIdx, isThisCharPositive);
                idx = newIdx + 1;
            } else if(c == '+'){
                isThisCharPositive = true;
                idx++;
            } else if(c == '-'){
                isThisCharPositive = false;
                idx++;
            } else if(isdigit(c)){
                int num = 0;
                while(idx < s.size() && isdigit(s[idx])){
                    num = num * 10 + (s[idx] - '0');
                    idx++;
                }
                bool isNetPositive = !(isThisCharPositive ^ isPositive);
                ans += (isNetPositive ? num : -num);
            } else {
                idx++;
            }
        }
        return ans;
    }

    int calculate(const string &str) {
        return evaluate(str, 0, true, 0);
    }
};


int main(){
    system("clear");
    Solution sol;
    vector<pair<string, int>> testCases = {
        {"1 + 1", 2},
        {" 2-1 + 2 ", 3},
        {"(1+(4+5+2)-3)+(6+8)", 23},
        {"42", 42},
        {"((2+3)+(4-(1+1)))", 7},
        {"5 - (3 + 2)", 0},
        {"    ", 0},           // depends on your implementation for empty input
        {"10 + (2 - 3) + 4", 13},
        {"-1 + 2", 1},
        {"3+(2-5)", 0}
    };

    for (auto& [input, expected] : testCases) {
        int output = sol.calculate(input);
        cout << "Input: \"" << input << "\"\n";
        cout << "Output: " << output << ", Expected: " << expected << " => ";
        cout << (output == expected ? "PASS" : "FAIL") << "\n\n";
    }

    return 0;
}