//143. Reorder List
//https://leetcode.com/problems/reorder-list/description/


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
#define Y cout << "YES" << endl;
#define no cout << "NO" << endl;
#define printvv(v) fo(i,v.size()){{fo(j,v[0].size())cout<<v[i][j]<<" ";}lb}
#define printbool(flag) if(flag){Y;}else{no;}
const int mod=1e9+7;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0),next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x,ListNode *next) : val(x),next(next) {}
};


class Solution {
public:
    ListNode* reverse(ListNode*& head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
        return head;
    }
    void reorderList(ListNode* head) {
        if(!head || !head->next)return;
        int len = 0;
        ListNode* curr = head;
        while(curr){
            curr = curr->next;
            len++;
        }

        ListNode* half = head;
        ListNode* prev_half = nullptr;
        int t = len/2;
        while(t--){
            prev_half = half;
            half = half->next;
        }

        prev_half->next = nullptr;

        ListNode* h2 = reverse(half);
        ListNode* h1 = head;

        bool one = true;
        while(h1 and h2){
            if(one){
                ListNode* h1_next = h1->next;
                h1->next = h2;
                h1 = h1_next;
            }else{
                ListNode* h2_next = h2->next;
                h2->next = h1;
                h2 = h2_next;
            }
            one = !one;
        }
    }
};

int main(){
    Solution sol;
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);

    sol.reorderList(head);
}