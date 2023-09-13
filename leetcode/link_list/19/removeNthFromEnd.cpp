class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummyhead = new ListNode();
        dummyhead->next = head;
        ListNode* fast = dummyhead;
        ListNode* slow = dummyhead;
        while (n--) {
            fast = fast->next;
        }
        ListNode* pre = slow;
        while(fast != nullptr) {
            fast = fast->next;
             pre = slow;
            slow = slow->next;
        }
        
           
       
            pre->next = slow->next;
        
        return dummyhead->next;

    }
};