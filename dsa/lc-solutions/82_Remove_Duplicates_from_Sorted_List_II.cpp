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

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptre) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void printList(ListNode* head) {
        ListNode* curr = head;
        while (curr != nullptr) {
            cout << curr->val;
            if (curr->next != nullptr) cout << " -> ";
            curr = curr->next;
        }
        cout << endl;
    }


class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* dummyHead = new ListNode(0);
        ListNode* dummyHeadStart = dummyHead;
        ListNode* tempHead = head;
        ListNode* tempHead2 = tempHead;
        int tempValue;


        while(tempHead){
            tempValue = tempHead->val;
            tempHead2 = tempHead;
            int numberOfNodes = 0;
            while(tempHead2 && tempHead2->val == tempValue){
                tempHead2 = tempHead2->next;
                numberOfNodes ++;
            }
            
            if(numberOfNodes == 1){
                dummyHead->next = tempHead;
                dummyHead = dummyHead->next;
            }

            tempHead = tempHead2;
        }

        dummyHead->next = tempHead;
        return dummyHeadStart->next;
    }
};

int main(){
system("clear");
    Solution sol;

    ListNode* head = new ListNode(8);
    head->next = new ListNode(8);
    head->next->next = new ListNode(8);
    head->next->next->next = new ListNode(7);
    head->next->next->next->next = new ListNode(7);
    head->next->next->next->next->next = new ListNode(6);
    head->next->next->next->next->next->next = new ListNode(6);
    head->next->next->next->next->next->next->next = new ListNode(9);
    head->next->next->next->next->next->next->next->next = new ListNode(9);

    ListNode* newHead = sol.deleteDuplicates(head);

    printList(newHead);
}