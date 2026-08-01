//This is the first solution of the recover binary tree question
//This is the O(n) apparoach and there is one more optimized approach O(1)
// Give it time think about the solution.

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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<TreeNode*> inorder;
    void swap(TreeNode* node1, TreeNode* node2){
        TreeNode* temp = node1;
        node1 = node2;
        node2 = temp;
    }   
    void recur(TreeNode* root){
        if(!root) return;

        if(root->left){
            recur(root->left);
        }

        inorder.push_back(root);

        if(root->right){
            recur(root->right);
        }
    }
    void recoverTree(TreeNode* root) {
        recur(root);
        int n = inorder.size();

        for(int i=0;i<n;i++){
            cout << inorder[i]->val << " ";
        }cout << endl;

        TreeNode* left; TreeNode* right;
        int count = 0;
        for(int i=0;i<n-1;i++){
            if(inorder[i]->val>inorder[i+1]->val){
                count ++;
                if(left == NULL){
                    left = inorder[i];
                    right = inorder[i+1];

                    cout  << "setting left" << endl;
                    cout << inorder[i]->val << " " << inorder[i+1]->val;
                }else{
                    right = inorder[i+1];

                    cout  << "setting right" << endl;
                    cout << inorder[i+1]->val;
                }
            }
        }

        swap(left,right);
    }
};

int main(){
system("clear");
    Solution sol;

    TreeNode* node2 = new TreeNode(2);
    TreeNode* node3 = new TreeNode(3, nullptr, node2);
    TreeNode* root = new TreeNode(1, node3, nullptr);


    int ans =
    
    
}