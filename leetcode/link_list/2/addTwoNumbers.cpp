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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummtHead = new ListNode(0);
        ListNode* p = dummtHead;
        int flag = false;
        int carry = 0;
        while (l1 || l2) {
            int val1 = l1 ? l1->val : 0;
            int val2 = l2 ? l2->val : 0;
            int sum = val1 + val2 + carry;
            p->next = new ListNode(sum % 10);
            p = p->next;
            carry = sum/10;
            if (l1) {
                l1 = l1->next;
            }
            if (l2) {
                l2 = l2->next;
            }
        }
        if (carry > 0) {
            p->next = new ListNode(carry);
        }
       
        return dummtHead->next;
    }
};
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* result = new ListNode();
        ListNode* p = result;
    
    int over_vaule = 0;
    while (l1 || l2 || over_vaule)
    {
        int sum_value = 0;
        if(l1){
            sum_value += l1->val;
            l1 = l1->next;
        }
        if(l2){
            sum_value += l2->val;
            l2 = l2->next;
        }
        sum_value += over_vaule;
        ListNode* insert_node = new ListNode(sum_value % 10);
        p->next= insert_node;
        p = p->next;
        over_vaule = sum_value / 10;
    }
    return result->next;

    }
};