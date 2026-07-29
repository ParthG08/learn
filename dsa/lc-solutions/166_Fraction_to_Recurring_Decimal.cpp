// first attempt miss the right dry run errors
// second attempt missed the edge cases
// fourth attemp missed the edge cases


// tips: write the edge cases yourself one dry run it and then run it in the solution
// each time you make the changes in the code after final touch ups see the impact on the code.


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
#define printv(v) for(const auto& x:(v)) cout<<x<<" "; cout<<"\n";}
#define inp(v) for(int i=0;i<(int)v.size();i++) cin>>v[i]
#define lb cout<<"\n"
#define pb push_back
#define C continue
#define B break
#define Y cout<<"YES\n"
#define no cout<<"NO\n"
#define sp cout<<" "
#define printvv(v) fo(i,v.size()){fo(j,v[0].size()) cout<<v[i][j]<<" "; lb;}
#define printbool(flag) if(flag){Y;}else{no;}
#define printpv(vec) do{for(auto p:vec) cout<<'{'<<p.first<<','<<p.second<<"} "; cout<<"\n";}while(0)

const int mod = 1e9 + 7;

class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if(numerator == 0 || denominator == 0) return "0";
        string integer_part = "";
        string decimal_part = "";
        decimal_part.reserve(1000);

        bool isNegative = false;
        string sign = "";

        if(numerator<0 ^ denominator<0) isNegative = true;
        if(isNegative) sign = "-";

        
        long long n = abs((long long)numerator);
        long long d = abs((long long)denominator);
        long long rem = n % d;

        long long integer_val = n/d;

        integer_part += std::to_string(integer_val);

        if(rem == 0){
            cout << sign << "   " <<  integer_part << endl;
            return sign + integer_part;
        }

        map<int,int> index;
        int idx = 0;

        bool foundLoop = false;
        while(rem != 0){
            if(index.find(rem) != index.end()){
                foundLoop = true;
                break;
            }

            index[rem] = idx;
            rem*=10;

            int decimal_val = rem / d;
            rem = rem % d;
            
            decimal_part += ('0' + decimal_val);
            idx++;
            // cout << rem << " " << decimal_part << endl;
        }

        if(foundLoop) {
            int break_pt = index[rem];
            decimal_part.insert(break_pt, "(");
            decimal_part += ")";
        }

        return sign + integer_part + "." + decimal_part;
    }
};


int main() {
    system("clear");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution s;

    struct TestCase {
        int num;
        int den;
        string expected;
    };

    vector<TestCase> tests = {
        {1, -1, "-1"},
        {2, 1, "2"},
        {0, 3, "0"},
        {1, 3, "0.(3)"},
        {1, 6, "0.1(6)"},
        {4, 333, "0.(012)"},
        {1, 7, "0.(142857)"},
        {-50, 8, "-6.25"},
        {-2147483648, -1, "2147483648"}, // Large denominator
        {2147483647, -1, "-2147483647"}
    };

    cout << "Running Tests:\n----------------\n";
    for (const auto& t : tests) {
        string result = s.fractionToDecimal(t.num, t.den);
        cout << "In: " << t.num << "/" << t.den << "\n";
        cout << "Out: " << result << "\n";
        cout << (result == t.expected ? "✅ PASS" : "❌ FAIL (Expected: " + t.expected + ")") << "\n\n";
    }

    return 0;
}