#include <bits/stdc++.h>
#define printv(v) for(auto i:v)cout << i << " " ;cout <<endl;
using namespace std;

class Solution {
public:
    int actWithSign(int val1, char c, int val2){
        if(c == '-') return val1 - val2;
        else if(c == '+') return val1 + val2;
        else if(c == '*') return val1 * val2;
        else if(c == '/') return val1 / val2;

        return 0;
    }
    bool isSign(string s) {
        if (s.size() > 1) return false; // It's a negative number like "-11"
        char c = s[0];
        return (c == '-' || c == '+' || c == '/' || c == '*');
    }
    int recur(vector<string> &tokens,int l, int r){
        if (l == r) {
            if (tokens[l].size() > 1 || isdigit(tokens[l][0])) {
                return stoi(tokens[l]);
            }
            return 0; 
        }

        if(tokens[l].size() < 1 || !isSign(tokens[l]))return 0;

        char c = tokens[l][0];
        int idx = l+1;
        int numbers = 0,signs = 0;

        while(idx+1 <= r){
            if(isSign(tokens[idx])) signs ++;
            else numbers ++;

            if(numbers >= signs + 1) break;

            idx ++;
        }

        // cout << l+1 << " " << idx << endl;
        // cout << idx+1 << " " << r << endl;

        // cout << "---------\n" << endl;

        int val1 = recur(tokens,l+1,idx);
        int val2 = recur(tokens,idx+1,r);

        int ans = actWithSign(val2,c,val1);
        printf("%d %c %d = %d\n", val1, c, val2, ans);
        return ans;
    }
    int evalRPN(vector<string>& tokens) {
        int n = tokens.size();
        reverse(tokens.begin(), tokens.end());
        printv(tokens);cout<< endl;
        return recur(tokens, 0, n-1);
    }
};  


void run_test(int test_num, vector<string> tokens, int expected) {
    Solution s;
    int result = s.evalRPN(tokens);
    cout << "Test " << test_num << ": ";
    if (result == expected) {
        cout << "PASSED";
    } else {
        cout << "FAILED (Expected " << expected << ", got " << result << ")";
    }
    cout << endl;cout << endl;
}


int main() {
    // 1. Basic operations
    run_test(1, {"2", "1", "+", "3", "*"}, 9);

    // 2. Division truncation (13/5 = 2)
    run_test(2, {"4", "13", "5", "/", "+"}, 6);

    // 3. Complex negative result
    run_test(3, {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"}, 22);

    // 4. Single operand
    run_test(4, {"18"}, 18);

    // 5. Handling negative numbers
    run_test(5, {"3", "-4", "+"}, -1);

    // 6. Subtraction order (5 - 3)
    run_test(6, {"5", "3", "-"}, 2);

    return 0;
}