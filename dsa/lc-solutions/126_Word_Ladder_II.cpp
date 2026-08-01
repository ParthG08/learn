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

const int mod = 1e9 + 7;

// Even though the logic that i was thinking of was pretty correct the code that i have submitted has the time complexity better than just 5% of the submissions also i have missed some things that eventually got corrected by gemini so ols practice writing this solution again once.

class Solution {
public:
    // Pass 'res' by reference so updates persist
    void completeVector(map<string, vector<string>>& parents, vector<string> resPart, vector<vector<string>>& res) {
        string lastWord = resPart.back();
        
        // Base case: if no parents, we've reached the startWord
        if (parents[lastWord].empty()) {
            vector<string> path = resPart;
            reverse(path.begin(), path.end()); // Paths are built backwards
            res.push_back(path);
            return;
        }

        for (string p : parents[lastWord]) {
            resPart.push_back(p);
            completeVector(parents, resPart, res);
            resPart.pop_back(); // Backtrack
        }
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if (dict.find(endWord) == dict.end()) return {};

        map<string, int> dist;
        map<string, vector<string>> parents;
        for (const string& word : wordList) dist[word] = INT_MAX;
        dist[beginWord] = 0;

        queue<string> q;
        q.push(beginWord);

        while (!q.empty()) {
            string node = q.front();
            q.pop();

            string nb = node;
            for (int i = 0; i < nb.size(); i++) {
                char original = nb[i];
                for (char c = 'a'; c <= 'z'; c++) {
                    nb[i] = c;
                    if (dict.count(nb)) {
                        if (dist[nb] > dist[node] + 1) {
                            dist[nb] = dist[node] + 1;
                            parents[nb].clear();
                            parents[nb].push_back(node);
                            q.push(nb);
                        } else if (dist[nb] == dist[node] + 1) {
                            parents[nb].push_back(node);
                        }
                    }
                }
                nb[i] = original;
            }
        }

        vector<vector<string>> res;
        if (dist.count(endWord) && dist[endWord] != INT_MAX) {
            vector<string> resPart = {endWord};
            completeVector(parents, resPart, res);
        }
        return res;
    }
};

int main() {
    system("clear");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto start = chrono::high_resolution_clock::now();

    Solution s;
    // TODO: add code to invoke solution and print output

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Execution time: " << duration << " microseconds\n";

    return 0;
}