
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode* cur = dummyHead;
        while(cur->next != nullptr && cur->next->next != nullptr) {
            ListNode* tmp_1 = cur->next;
            ListNode* tmp_2 = cur->next->next->next;

            cur->next = tmp_1->next;
            cur->next->next = tmp_1;
            cur->next->next->next = tmp_2;

            cur = cur->next->next;
        }
        return dummyHead->next;
    }
};