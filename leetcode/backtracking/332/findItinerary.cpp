#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool backtracking(int tickernum, vector<string>& ret) {
        if (ret.size() ==  tickernum + 1) {
            return true;
        }
        for(pair<const string,int>& target : targets[ret[ret.size()-1]]) {
            if (target.second > 0) { // 是否已经重复
                ret.push_back(target.first);
                target.second--;
                if (backtracking(tickernum,ret)) return true;
                ret.pop_back();
                target.second++;
            }
        }
        return false;
    }
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        vector<string> ret;
        targets.clear();
        for (const vector<string>& vec: tickets ) {
            targets[vec[0]][vec[1]]++;  // 建立关系
        }
        ret.push_back("JFK");
        backtracking(tickets.size(), ret);
        return ret;
    }
private:
    
    unordered_map<string, map<string,int>> targets;
};

int main() {
    // vector<vector<string>> tickets = {{"MUC","LHR"},{"JFK","MUC"},{"SFO","SJC"},{"LHR","SFO"}};
    vector<vector<string>> tickets = {{"JFK","SFO"},{"JFK","ATL"}, {"SFO","ATL"}, {"ATL","JFK"},{"ATL","SFO"}};
    Solution ob;
    vector<string> ret = ob.findItinerary(tickets);
    for (auto it : ret) {
        cout << it << "\t";
    }
    cout <<endl;
}