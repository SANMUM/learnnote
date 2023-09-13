#include<bits/stdc++.h>
using namespace std;
class LRUCache {
public:
    struct Node {
        int key, val;
        Node* pre;
        Node* next;
        Node(int k, int v) {
            key = k;
            val = v;
            pre = nullptr;
            next = nullptr;
        }
    };
    LRUCache(int capacity) {
        len = capacity;
        head = new Node(-1,-1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->pre = head;
    }
    
    int get(int key) {
       if (!umap.count(key)) {
        return -1;
       }
        Node* ptr = umap[key];
        remove(ptr);
        insert(ptr);
        return ptr->val;
    }
    
    void put(int key, int value) {
         if (!umap.count(key)) {
            // 双向链表中没有key的时候，需要执行插入操作
            // 双向链表满了
            
            if (umap.size() == len) {
                Node* ptr = tail->pre;
                remove(ptr);
                umap.erase(ptr->key);
                delete ptr;
                
            }
            Node* ptr = new Node(key, value);
            umap[ptr->key] = ptr;
            insert(ptr);
            return;
        }
        // 双向链表中有key，需要执行更新操作
        Node* ptr = umap[key];
        ptr->val = value;
        // umap[key] = ptr;
        remove(ptr); 
        insert(ptr);
        
    }
    void insert(Node* ptr) {
        Node* a = head->next;
        a->pre = ptr;
        ptr->next = a;
        ptr->pre = head;
       
        head->next = ptr;
    }
    void remove(Node* ptr) {
        Node* a = ptr->pre;
        Node* b = ptr->next;
        a->next = b;
        b->pre = a;
        ptr->next = nullptr;
        ptr->pre = nullptr;
    }
private:
    Node* head;
    Node* tail;
    unordered_map<int, Node*> umap;
    int len;
};