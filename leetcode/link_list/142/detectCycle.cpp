struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast) {
               ListNode* index_1 = fast;
               ListNode* index_2 = head;
               while (index_1 != index_2) {
                    index_1 = index_1->next;
                    index_2 = index_2->next;
               }
               return index_1;
            }
        }
        return nullptr;
    }
};
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
       
        ListNode* slow = head;
        ListNode* fast = head;
        while (true) {
            if (fast == nullptr || fast->next == nullptr) {
                return nullptr;
            }
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) break;
        }
        fast = head;
        while (fast != slow) {
            slow = slow->next;
            fast = fast->next;
        }
        return fast;
    }
};