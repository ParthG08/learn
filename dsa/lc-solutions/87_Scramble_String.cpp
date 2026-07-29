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

// Have done this questions once more and looked at the solutino.
// recusion (simple) 2^n (n size of the strings) time complexity
// recursion with the frequency checks (check for the frequency of each word before recusion) 
// memoization (solves the question)

// Improvements that can be made.

/*
Pruning	Done inside the loop for every split point i. --> Done once at the start of the function (O(n)).
Memo Key	s1 + "#" + s2 (String concatenation is slow). -->	Use s1_start, s2_start, length (3 integers) as key.
Substrings	s1.substr() creates new strings (Memory intensive). -->	Pass indices/pointers to the original string.
Complexity	O(n5) (due to string ops + nested loops). -->	O(n4) (Standard for Scramble String).
*/

const int mod = 1e9 + 7;

class Solution {
private:
    unordered_map<string, bool> memo;

public:
    bool isScramble(string s1, string s2) {
        if (s1 == s2) return true;
        int n = s1.size();
        if (n != (int)s2.size()) return false;

        string key = s1 + "#" + s2;
        if (memo.count(key)) return memo[key];

        for (int i = 1; i < n; i++) {
            array<int, 26> res11{}, res12{}, res21{}, res22{};
            for (int j = 0; j < i; j++) {
                res11[s1[j] - 'a']++;
                res21[s2[j] - 'a']++;
            }
            for (int j = i; j < n; j++) {
                res12[s1[j] - 'a']++;
                res22[s2[j] - 'a']++;
            }

            if (res11 == res21 && res12 == res22) {
                if (isScramble(s1.substr(0, i), s2.substr(0, i)) &&
                    isScramble(s1.substr(i), s2.substr(i))) {
                    return memo[key] = true;
                }
            }

            fill(res11.begin(), res11.end(), 0);
            fill(res12.begin(), res12.end(), 0);
            fill(res21.begin(), res21.end(), 0);
            fill(res22.begin(), res22.end(), 0);

            for (int j = 0; j < i; j++) {
                res11[s1[j] - 'a']++;
                res21[s2[n - i + j] - 'a']++;
            }
            for (int j = i; j < n; j++) {
                res12[s1[j] - 'a']++;
                res22[s2[j - i] - 'a']++;
            }

            if (res11 == res21 && res12 == res22) {
                if (isScramble(s1.substr(0, i), s2.substr(n - i)) &&
                    isScramble(s1.substr(i), s2.substr(0, n - i))) {
                    return memo[key] = true;
                }
            }
        }

        return memo[key] = false;
    }
};


int main() {
    system("clear");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution s;
    // 25-character test case for problem 87 (Scramble String)
    string s1 = "eebaacbcbcadaaedceaaacadccd"; // length=25
    string s2 = "eadcaacabaddaceacbceaabeccd"; // scrambled equivalent of s1

    auto start = chrono::high_resolution_clock::now();

    bool isScrambled = s.isScramble(s1, s2);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    printbool(isScrambled);
    cout << "Execution time: " << duration << " microseconds\n";

    return 0;
}