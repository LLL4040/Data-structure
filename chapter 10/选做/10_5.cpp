#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;
};

void insertSort(Node *head);

int main()
{
    Node *head = new Node(), 
        *a0 = new Node(), 
        *a1 = new Node(), 
        *a2 = new Node(), 
        *a3 = new Node(), 
        *a4 = new Node();
    a0->data = 3;
    a1->data = 1;
    a2->data = 2;
    a3->data = 5;
    a4->data = 4;

    head->next = a0;
    a0->next = a1;
    a1->next = a2;
    a2->next = a3;
    a3->next = a4;
    a4->next = NULL;
    insertSort(head);
    while(head->next)
    {
        cout << head->next->data << " ";
        head = head->next;
    }
    return 0;
}

void insertSort(Node *head)
{
    Node *cur = head->next;
    Node *pre = head;
    while(cur)
    {
        Node *p = head;
        while(p->next && p != pre)
        {
            if(cur->data < p->next->data)
            {
                pre->next = cur->next;
                cur->next = p->next;
                p->next = cur;
                break;
            }
            p = p->next;
        }
        pre = cur;
        cur = cur->next;
    }
}