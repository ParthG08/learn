// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/


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

// This is quite possibly the worst solution to this question
// so what i am  doing is making a tree of pairs that will contain the range of elements each tree has
// rather than that i can use recursion to build the treeNodes everytime by keeping the preorder index 
// as global and calling left recursion and then right recursion. do this question again and this about 
// the solution

// i am making the second part of this questino just so that i remember that i need to do this question.


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct TreeNodeVec {
    pair<int,int> val;
    TreeNodeVec *left;
    TreeNodeVec *right;
    TreeNodeVec(pair<int,int> v) : val(v), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    void traverseAndCreate(TreeNodeVec* root, int idx){
        if(!root) return;
        int first = root->val.first;
        int second = root->val.second;

        if(idx < first){
            if(!root->left){
                root->left = new TreeNodeVec({idx, idx});
            } else {
                traverseAndCreate(root->left, idx);
            }
            return;
        }

        if(idx > second){
            if(!root->right){
                root->right = new TreeNodeVec({idx, idx});
            } else {
                traverseAndCreate(root->right, idx);
            }
            return;
        }

        // idx is inside [first, second]
        if(first == second){
            // already a point node
            return;
        }

        TreeNodeVec* leftChild = nullptr;
        TreeNodeVec* rightChild = nullptr;
        if(first <= idx - 1){
            leftChild = new TreeNodeVec({first, idx - 1});
        }
        if(idx + 1 <= second){
            rightChild = new TreeNodeVec({idx + 1, second});
        }

        root->val = {idx, idx};
        root->left = leftChild;
        root->right = rightChild;
    }

    TreeNodeVec* buildTreeVec(vector<int>& preorder, vector<int>& inorder, unordered_map<int,int>& valueToIndexes){
        int n = preorder.size();
        if(n == 0) return nullptr;

        TreeNodeVec* root = new TreeNodeVec({0, n - 1});
        for(int v : preorder){
            int idx = valueToIndexes[v];
            traverseAndCreate(root, idx);
        }
        return root;
    }

    TreeNode* convertTreeNodeVec(TreeNodeVec* root, vector<int>& inorder) {
        if(!root) return nullptr;

        // After building, we expect each node value range to be a single point
        if(root->val.first > root->val.second) return nullptr;

        if(root->val.first != root->val.second){
            // This should not happen after full insertion of all indexes.
            TreeNode* leftNode = convertTreeNodeVec(root->left, inorder);
            TreeNode* rightNode = convertTreeNodeVec(root->right, inorder);
            return leftNode ? leftNode : rightNode;
        }

        int idx = root->val.first;
        TreeNode* node = new TreeNode(inorder[idx]);
        node->left = convertTreeNodeVec(root->left, inorder);
        node->right = convertTreeNodeVec(root->right, inorder);
        return node;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int,int> valueToIndexes;
        for(int i = 0; i < (int)inorder.size(); i++){
            valueToIndexes[inorder[i]] = i;
        }
        if(preorder.empty()) return nullptr;

        TreeNodeVec* root = buildTreeVec(preorder, inorder, valueToIndexes);
        return convertTreeNodeVec(root, inorder);
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