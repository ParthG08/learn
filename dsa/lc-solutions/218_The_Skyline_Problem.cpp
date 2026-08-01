#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        multiset<int> pq{0};
        vector<vector<int>> points;
        int heightTillNow = 0;
        vector<vector<int>> ans;

        for(auto building: buildings){
            points.push_back({building[0],-building[2]});
            points.push_back({building[1],building[2]});
        }

        sort(points.begin(), points.end());

        for(auto point: points){
            int currentPoint = point[0];
            int heightAtCurrentPoint = point[1];

            if(heightAtCurrentPoint < 0){
                pq.insert(-heightAtCurrentPoint);
            }else{
                pq.erase(pq.find(heightAtCurrentPoint));
            }

            auto pqTop = *pq.rbegin();
            if(heightTillNow != pqTop){
                heightTillNow = pqTop;
                ans.push_back({currentPoint, heightTillNow});
            }

        }

        return ans;
    }
};

int main() {
    vector<vector<int>> buildings = {
        {2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}
    };

    Solution sol;
    vector<vector<int>> skyline = sol.getSkyline(buildings);

    cout << "Skyline key points:\n";
    for (auto& p : skyline) {
        cout << "(" << p[0] << ", " << p[1] << ")\n";
    }

    return 0;
}
