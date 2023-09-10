#include<iostream>
#include<vector>
// #include<priority_queue>
#include<queue>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
ListNode* mergeKLists(vector<ListNode*>& lists) {
    using Elem = pair<int,ListNode*>;
    priority_queue<Elem,vector<Elem>,greater<Elem>> pq;

    for(ListNode* node: lists){
        if(node){
            pq.push({node->val,node});
        }
    }
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    while(!pq.empty()){
        Elem elem = pq.top();
        pq.pop();
       
        if(!head){
            head=tail=elem.second;
        }
        else
        {
           tail->next = elem.second;
           tail = elem.second; 
        }
        if(elem.second->next){
            pq.push({elem.second->val,elem.second->next});
        }
        
    }
    return head;
}

/*

class Solution {
public:
    // 小根堆的回调函数
    struct cmp{  
       bool operator()(ListNode *a,ListNode *b){
          return a->val > b->val;
       };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, cmp> pri_queue;
        // 建立大小为k的小根堆
        for(auto elem : lists){
            if(elem) pri_queue.push(elem);
        }
        // 可以使用哑节点/哨兵节点
        ListNode dummy(-1);
        ListNode* p = &dummy;
        // 开始出队
        while(!pri_queue.empty()){
            ListNode* top = pri_queue.top(); pri_queue.pop();
            p->next = top; p = top;
            if(top->next) pri_queue.push(top->next);
        }
        return dummy.next;  
    }
};
*/
int main(){
    ListNode
}