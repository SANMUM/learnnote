#include<bits/stdc++.h>
using std::cout;
using std::endl;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
    ListNode* dummp = new ListNode(0);
    dummp->next = head;
    ListNode* cur = dummp;
    while (cur->next != nullptr){
        if(cur->next->val == val){
            ListNode* tmp = cur->next;
            cur->next = cur->next->next;
        }
        else{
            cur = cur->next;
        }
    }
    return dummp->next;
    }
};
 