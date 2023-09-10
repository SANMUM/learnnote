#include<iostream>
using namespace std;

class MyLinkedList {
public:
    struct LinkNode{
        int val;
        LinkNode* next;
        LinkNode(int value): val(value),next(nullptr) {}
    };

    MyLinkedList() {
        head = new LinkNode(0);
        _size = 0;
        
    }
    
    int get(int index) {
        if ( index > _size - 1 ) {
            return -1;
        }
        LinkNode* cur = head->next;
        while(index--){
            cur = cur->next;
        }
        return cur->val;
    }
    
    void addAtHead(int val) {
        LinkNode* node = new LinkNode(val);
        node->next = head->next;
        head->next = node;
        _size++;
    }
    
    void addAtTail(int val) {
        LinkNode* node = new LinkNode(val);
        LinkNode* cur = head;
        while(cur->next != nullptr) {
            cur = cur->next;
        }
        cur->next = node;
        _size++;
    }
    
    void addAtIndex(int index, int val) {
        if (index > _size ){
            return;
        }
        LinkNode* cur = head;
        LinkNode* newNode = new LinkNode(val);
        while (index--){
            cur = cur->next;
        }
       
        newNode->next = cur->next;
        cur->next = newNode;
        _size++;
        
    }
    
    void deleteAtIndex(int index) {
        if(index >= _size){
            return;
        }
        LinkNode* cur = head;
        while (index--)
        {
            cur = cur->next;
        }
        LinkNode* tmp = cur->next;
        cur->next = cur->next->next;
        delete tmp;
        tmp = nullptr;
        _size--;
    }
private:
    int _size;
    LinkNode* head;


};

int main(){


}