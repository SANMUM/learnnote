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
    ListNode* mergeSort(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }
        ListNode* slowNode = head;
        ListNode* fastNode = head;
        ListNode* midNode = nullptr;
        while (fastNode) {
            midNode = slowNode;
            slowNode = slowNode->next;
            fastNode = fastNode->next;
            if (!fastNode) {
                break;
            } 
            fastNode = fastNode->next;
        }
        midNode->next = nullptr;
        ListNode* dummyhead = new ListNode(0);
        ListNode* p = dummyhead;
        ListNode* left = mergeSort(head);
        ListNode* right = mergeSort(slowNode);
        while (left && right) 
        {
            if (left->val < right->val) {
                p->next = left;
                
                left = left->next;
            }
            else {
                p->next = right;
                right = right->next;
            }
            p = p->next;          
        }
        if (left) p->next = left;
        if (right) p->next = right;
        return dummyhead->next;
    }
    ListNode* sortList(ListNode* head) {
        return mergeSort(head);
    }
};