class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head == nullptr) {
            return nullptr;
        }
        Node* p = head;
        while (p) {
            Node* temp = new Node(p->val);
            temp->next = p->next;
            p->next = temp;
            p = p->next;
        }
        p = head;
        while (p) {
            if (p->random != nullptr) {
                p->next->random = p->random->next;
                
            }
            p = p->next->next;
        }
        p = head;
        Node* cur = head->next;
        Node* ans = head->next;
        while (cur->next != nullptr) {
            p->next = p->next->next;
            cur->next = cur->next->next;
            p = p->next;
            cur = cur->next;
        }
        p->next = nullptr;
        return ans;
    }
};