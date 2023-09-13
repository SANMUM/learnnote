class Solution {
public:
    bool isPalindrome(ListNode* head) {
        vector<int> result;
        ListNode* p = head;
        while (p != nullptr) {
            result.push_back(p->val);
            p = p->next;
        }
        for (int i = 0, j = result.size() - 1; i < j; i++,j--) {
            if (result[i] != result[j]) {
                return false;
            }            
        }
        return true;

    }
};