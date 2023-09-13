#include<bits/stdc++.h>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        using Elem =  pair<int, ListNode*> ;
        priority_queue<Elem, vector<Elem>, greater<Elem>> pq;
        for (ListNode* it : lists) {
            if (it) {
                pq.push({it->val, it});
            }
        }
        ListNode* dummtHead = new ListNode();
        ListNode* p = dummtHead;
        while (!pq.empty()) {
            Elem elem = pq.top();
            pq.pop();
            p->next = elem.second;
            p = p->next;
            if (elem.second->next) {
                pq.push({elem.second->next->val, elem.second->next});
            }
        }
        return dummtHead->next;


    }
};