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
    int getListLen(ListNode* list) {
        int ret = 0;
        while(list != nullptr) {
            ret++;
            list = list->next;
        }
        return ret;
    }
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA == nullptr || headB == nullptr) {
            return nullptr;
        }
        ListNode* curA = headA;
        ListNode* curB = headB;
        int lenA = getListLen(curA);
        int lenB = getListLen(curB);
        curA = headA;
        curB = headB;
        if (lenA < lenB) {
            swap(lenA,lenB);
            swap(curA,curB);
        }
        
        int gap = lenA - lenB;
        while(gap--) {
            curA = curA->next;
        }
        while(curA != nullptr) {
            if(curA == curB) {
                return curA;
            }
            curA = curA->next;
            curB = curB->next;
        }
        return nullptr;
    }
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* a = headA;
        ListNode* b = headB;
        while (a!=b) {
            a = a==nullptr ? headB: a->next;
            b = b == nullptr ? headA: b->next;
        }
        return a;
    }
};