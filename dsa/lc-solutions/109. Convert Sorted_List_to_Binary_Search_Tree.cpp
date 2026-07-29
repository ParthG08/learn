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

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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
    pair<ListNode*, ListNode*> middle(ListNode* head){  
        if(!head) return {NULL,NULL};
        
        ListNode* slow = head;
        ListNode* prev = NULL;
        ListNode* fast = head;
        
        while(fast->next && fast->next->next){
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        return {prev,slow};
    }

    TreeNode* sortedListToBST(ListNode* head) {
        if(!head) return NULL;

        auto [prev,mid] = middle(head);
        
        if(prev != NULL){
            prev->next = NULL; // break the left chain.
        }
        ListNode* next = mid->next;
        mid->next = NULL; // break the right chain

        TreeNode* root = new TreeNode(mid->val);
        
        root->left = sortedListToBST(prev == NULL ? NULL : head);
        root->right = sortedListToBST(next);

        return root;
    }
};

int main(){
    system("clear");
    Solution sol;
    
}