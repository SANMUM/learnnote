class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* dummyHead = new ListNode();
        dummyHead->next = head;
        ListNode* pre = dummyHead;
        ListNode* cur = head;
        while (cur) {
            ListNode* nextNode = cur;
            for (int i = 0; i < k -1; i++) {
                nextNode = nextNode->next;
                if (!nextNode){
                    return dummyHead->next;
                }
            }
           for (int i = 0; i < k - 1; i++) {
               ListNode* next = cur->next;
               cur->next = next->next;
               next->next = pre->next;
               pre->next = next;
           }
           pre = cur;
           cur = pre->next;
        }
        return dummyHead->next;
    }
};