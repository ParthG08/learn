#include <bits/stdc++.h>
using namespace std;


#include <bits/stdc++.h>
using namespace std;

int main() {
    string str = "bbbbb";

    int n = str.size();
    unordered_set<char> st;

    int len = 0;
    int l = 0;

    for (int r = 0; r < n; r++) {
        while (st.find(str[r]) != st.end()) {
            st.erase(str[l]);
            l++;
        }

        st.insert(str[r]);
        len = max(len, r - l + 1);
    }

    cout << len << endl;
}
