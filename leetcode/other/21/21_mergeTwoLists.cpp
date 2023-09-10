#include<iostream>

struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
};
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    if(!list1)
        return list2;
    if(!list2)
        return list1;
    ListNode* ret = new ListNode();
    ListNode* p = ret;
    while(list1 && list2){
        int val;
        if(list1->val < list2->val)
        {
             val = list1->val;
             list1 = list1->next;
        }
        else
        {
            val = list2->val;
            list2 = list2->next;
        }
        
        // int val = (list1->val < list2->val) ?  list1->val : list2->val;
        ListNode *node = new ListNode(val);
        p->next = node;
        p = p->next;
        // list1 = list1->next;
        // list2 = list2->next;
    }
    p->next = (list1 == nullptr) ? list2 : list1;
    return ret->next;
}
int main(){

}