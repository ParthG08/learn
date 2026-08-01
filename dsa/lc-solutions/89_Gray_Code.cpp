// https://leetcode.com/problems/gray-code/

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


/*
To solve the Gray Code problem, the core intuition lies in understanding how to generate a sequence where each number differs from the previous one by exactly one bit, while ensuring all 2n numbers are unique.

The most effective way to build this is through Reflected Binary Code (the iterative/recursive approach).

The Intuitive Approach: Reflect and Prefix (This is purely pattern generation when there is limited data you need to build the ans for the first 3-4 numbers then see the pattern that they are forming)

The most common intuition is to build the n-bit sequence using the results of the (n−1)-bit sequence.

1. Mirroring (Reflection)

Imagine you have the Gray Code for n=1: [0, 1].
To get n=2, you take that list and "reflect" it (like a mirror) to get a new half: [1, 0].

    Original: 0, 1

    Reflected: 1, 0

    Combined: 0, 1, 1, 0

2. Prefixing

Now, to ensure they remain unique and maintain the "one-bit change" property at the junction:

    Add a 0 to the front of the original half.

    Add a 1 to the front of the reflected half. (when you add the one in the beginning you are essentially adding 1 >> n to the value)

    (In each step the array length is doubling so that is something you have to derive intuition from as well.)

Result for n=2:

    00, 01 (Original with 0)

    11, 10 (Reflected with 1)

    Sequence: [0, 1, 3, 2]

Why does this work?

    Internal Consistency: The first half is already a valid Gray Code. The second half is just a mirror, so it's also a valid Gray Code.

    The Junction: The last element of the first half (e.g., 01) and the first element of the reflected half (e.g., 11) differ only by the prefix bit we just added.

    The Loop: The very first element (00) and the very last element (10) also differ by only one bit, making it a cyclic code.

The Bit Manipulation Shortcut (The pure mathematical way is also something worth understanding reason being it deals with the associative and behavourial properties of XOR.)

If you prefer a direct mathematical approach, there is a formula to convert any binary number i to its Gray Code equivalent:
G(i)=i⊕(i>>1)
Intuition for the XOR trick:

When you shift a binary number to the right and XOR it with itself, the only bits that stay "1" are those where the bit and its neighbor are different. This effectively "smooths" the transitions so that as i increments, only one bit in the resulting G(i) flips at a time.
*/


// This is my implmenetation of the iterative generation. (using function which will use stack space. There is another direct implemntaion without using any function that i ahve put in the file name 89_Gray_Code_2.cpp)

const int mod = 1e9 + 7;

class Solution {
public:
    void increment(vector<int> &v){
        int n = v.size();

        for(int i=0;i<n;i++){
            v.push_back(n + v[n-i-1]);
        }
    }
    vector<int> grayCode(int n) {
        if(n == 0) return {0};

        n--;
        vector<int> v = {0,1};
        while(n--){
            increment(v);
        }

        return v;
    }
};

int main() {
    system("clear");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;
    vector<int> ans = sol.grayCode();

    printv(ans);
    return 0;
}