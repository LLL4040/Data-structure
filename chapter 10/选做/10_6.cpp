#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;
};

void selectSort(Node *head);

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
    selectSort(head);
    while(head->next)
    {
        cout << head->next->data << " ";
        head = head->next;
    }
    return 0;
}

void selectSort(Node *head)
{
    Node *pre = head;
    Node *tmp;
    while(pre->next)
    {
        Node *p = pre;
        Node *q = p->next;
        while(p->next)
        {
            if(q->data > p->next->data)
            {
                tmp = p;
                q = p->next;
            }
            p = p->next;
        }
        if(q != pre->next)
        {
            tmp->next = q->next;
            q->next = pre->next;
            pre->next = q;
        }
        pre = pre->next;
    }
}