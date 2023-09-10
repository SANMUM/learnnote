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
    ListNode* reverseList(ListNode* head) {
        ListNode* ret = new ListNode(0);
        // ListNode* p = ret;
        ListNode* cur = head;
        while (cur->next != nullptr) {
            ListNode* node = new ListNode(cur->next->val);
            node->next = ret->next;
            ret->next = node;
            // p = ret;
            // delete node;
            cur = cur->next;
        }
        return ret->next;

    }
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* dummyhead = new ListNode();
        dummyhead->next = nullptr;
        ListNode* p =  head;
        
        while (p!=nullptr) {
            ListNode* media = new ListNode(p->val);
            media->next = dummyhead->next;
            dummyhead->next = media;
            p = p->next;
            
            // media = dummyhead;
        }
        return dummyhead->next;
    }
};
int main() { 

}