// what you doing was you were making a trie of the matrix and not the strings
// making the trie of the matrix is not a good idea as the size of Trie increases a lot as the 
//size of the matrix increases also because we are iterating on the strings there is no way to acutally 
// kind of store the solution of the search of the previous string if you use the Trie on matrix 
// if you use the Trie on strings then the solution is already stored for the previous strings

// so the logic is make Trie of the strings 
// dfs on the matrixx while searching each string  in the Trie and you are done.


#include <bits/stdc++.h>
#include <cstdlib>
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

class TrieNode {
public:
    TrieNode* children[26] = {};
    string word = ""; // stores complete word at the leaf
};

class Solution {
public:
    void insertWord(TrieNode* root, const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children[c - 'a'])
                node->children[c - 'a'] = new TrieNode();
            node = node->children[c - 'a'];
        }
        node->word = word;  // mark the end of a word
    }

    void dfs(vector<vector<char>>& board, int i, int j, TrieNode* node, vector<string>& result) {
        char c = board[i][j];
        if (c == '#' || !node->children[c - 'a']) return;

        node = node->children[c - 'a'];
        if (!node->word.empty()) {
            result.push_back(node->word);
            node->word = ""; // avoid duplicates
        }

        board[i][j] = '#'; // mark visited
        vector<pair<int, int>> dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}};
        for (auto [dx, dy] : dirs) {
            int ni = i + dx, nj = j + dy;
            if (ni >= 0 && ni < board.size() && nj >= 0 && nj < board[0].size()) {
                dfs(board, ni, nj, node, result);
            }
        }
        board[i][j] = c; // backtrack
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        TrieNode* root = new TrieNode();

        // Build trie from words
        for (const string& word : words) {
            insertWord(root, word);
        }

        vector<string> result;
        int n = board.size(), m = board[0].size();

        // DFS from each cell
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                dfs(board, i, j, root, result);
            }
        }

        return result;
    }
};


int main(){
    system("clear");
    Solution sol;
    vector<vector<char>> board = {
        {'o','a','a','n'},
        {'e','t','a','e'},
        {'i','h','k','r'},
        {'i','f','l','v'}
    };

    vector<string> words = {"oath", "pea", "eat", "rain"};

    vector<string> res = sol.findWords(board,words);

    for(auto str:res){
        cout << str << endl;
    }
}