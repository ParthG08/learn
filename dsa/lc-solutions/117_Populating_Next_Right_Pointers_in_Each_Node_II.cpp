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



class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
    void printNext(Node* root){
        if(root){
            if(root->next){
                cout << "The next of " << root->val << " is: " << root->next->val << endl;
            }
        }else{
            return;
        }

        if(root->left) printNext(root->left);
        if(root->right) printNext(root->right);
    }
    Node* connect(Node* root) {
        int level = 1;
        queue<Node*> odd_queue;
        queue<Node*> even_queue;
        odd_queue.push(root);


        while(!(odd_queue.size() == 0 && even_queue.size() == 0)){
            queue<Node*> *active_queue;
            queue<Node*> *inactive_queue;

            if(level%2 == 1){
                active_queue = &odd_queue;
                inactive_queue = &even_queue;
            }else{
                active_queue = &even_queue;
                inactive_queue = &odd_queue;
            }

            Node* prev = NULL;
            while(!active_queue->empty()){
                Node* curr = active_queue->front();
                active_queue->pop();

                if(prev){
                    prev->next = curr;
                }

                if(curr->left){
                    inactive_queue->push(curr->left);
                }

                if(curr->right){
                    inactive_queue->push(curr->right);
                }
                prev = curr;
            }

            level ++;
        }

        return root;
    }
};

int main(){
system("clear");
    Solution sol;
    Node* root = new Node(3);
    root->left = new Node(2);
    root->right = new Node(4);
    root->left->left = new Node(5);
    root->left->right = new Node(9);
    root->right->left = new Node(10);
    root->right->right = new Node(9);

    Node* res = sol.connect(root);

    sol.printNext(res);
}