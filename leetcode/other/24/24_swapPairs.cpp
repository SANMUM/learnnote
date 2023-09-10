#include<iostream>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* swapPairs(ListNode* head) {
    if(!head) return nullptr;
    ListNode* ret = new ListNode(0);
    ListNode* p = ret;
    ListNode* pre = head;
    ListNode* next = pre->next;
    if(!next) return head;
    while (next)
    {
        // p->next = next;
        // next->next = pre;
        pre->next = next->next;
        next->next = pre;
        p->next = next;
        p = pre;
        pre = pre->next;
        if( !pre) break;
            next = pre->next;
    }
    return ret->next;
    
}

int main(){

}