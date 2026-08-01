//https://leetcode.com/problems/sudoku-solver/

/// first i tried using the constrain method which was making the set of all the posisble integers of a particular block
// and then removing the numbers from the set that is not possible. and then from repeating the same by filling in the ones that have 
// only on possibility

// turns out that is a wrong approach as there are harder sudokus that are required to iterate through multiple possibilities so the obvious 
//second approach was backtracking

// the application of backtracking in this one is interesting as there is a use of boolean to represent weather the current iteration is valid or not 
// and then the process goes on for other iterations just like that

// earlier i was trying the iteration to be in a snake like pattern 

//something like
// if(row%2 == 0) col ++
// else col --
// if(col == 8) row += 1;
// if (col == 0) row+=1;

// but that is not nefcessary as the pattern in which you actually fill the matrix doesnt matter as it would take all the possibilities in 
//consideration for the solution.

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
#define f false;
#define Y cout << "YES" << endl;
#define no cout << "NO" << endl;
#define printvv(v) fo(i,v.size()){{fo(j,v[0].size())cout<<v[i][j]<<" ";}lb}
#define printbool(flag) if(flag){Y;}else{no;}
const int mod=1e9+7;


class Solution {
public:
    bool checkRow(vector<vector<char>>& board, int row, int val){
        for(int col=0;col<9;col++){
            if((board[row][col] -'0') == val)return false;
        }
        return true;
    }
    bool checkCol(vector<vector<char>>& board, int col, int val){
        for(int row=0;row<9;row++){
            if((board[row][col] -'0') == val)return false;
        }
        return true;
    }
    bool checkBox(vector<vector<char>>& board,int row, int col, int val){
        int rb = (row/3)*3;
        int cb = (col/3)*3;

        for(int i=rb;i<rb+3;i++){
            for(int j=cb;j<cb+3;j++){
                if((board[i][j] - '0') == val) return false;
            }
        }

        return true;
    }
    bool solve(vector<vector<char>>& board,int row,int col){
        if(row>=9)return true;

        int nextRow = (col == 8) ? row+1 : row; 
        int nextCol = (col == 8) ? 0 : col+1;

        if(board[row][col] != '.') return solve(board,nextRow,nextCol);

        for(int k=1;k<=9;k++){
            bool isValid = checkBox(board,row,col,k) && checkRow(board,row,k) && checkCol(board,col,k);

            // printf("row : %d  col : %d  checkingNumber : %d isValid: %d\n\n", row, col, k, isValid);
            if(isValid){
                board[row][col] = '0' + k;
                if(solve(board,nextRow,nextCol))return true;
                board[row][col] = '.';
            }
        }

        return false;
    }
    void solveSudoku(vector<vector<char>>& board) {
        solve(board,0,0);
    }
};

int main(){
    Solution sol;
    vector<vector<char>> vec ={{'.','.','9','7','4','8','.','.','.'},
                                {'7','.','.','.','.','.','.','.','.'},
                                {'.','2','.','1','.','9','.','.','.'},
                                {'.','.','7','.','.','.','2','4','.'},
                                {'.','6','4','.','1','.','5','9','.'},
                                {'.','9','8','.','.','.','3','.','.'},
                                {'.','.','.','8','.','3','.','2','.'},
                                {'.','.','.','.','.','.','.','.','6'},
                                {'.','.','.','2','7','5','9','.','.'}};


    sol.solveSudoku(vec);

    for(auto v:vec){
        for(auto i:v){
            cout << i << " ";
        }cout << endl;
    }
}