#include<iostream>
using namespace std;

struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode* p = new ListNode();
    p->next = head;
    ListNode* lNode = head;
    ListNode* rNode = head;
    int i = 0;
    while(i<n)
    {
        rNode = rNode->next;
        i++;
    }
    ListNode* preNode = p;
    while(rNode != nullptr)
    {
        rNode = rNode->next;
        preNode = preNode->next;
        lNode = lNode->next;
    }
    preNode->next = lNode->next;
    return p->next;

}

int main(){

}


