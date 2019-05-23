#include <iostream>
using namespace std;

template<class KEY, class OTHER>
struct SET {
    KEY key;
    OTHER other;
};

template<class KEY, class OTHER>
struct Node {
    SET<KEY, OTHER> value;
    Node* next;
};

/* function for question6 */
template<class KEY, class OTHER>
Node<KEY, OTHER> *seqSearch(Node<KEY, OTHER> *head, const KEY &x) {
    Node<KEY, OTHER> *p = head;
    while(p->next) {
        if(p->next->value.key == x) {
            Node<KEY, OTHER> *tmp = p->next;
            p->next = tmp->next;
            tmp->next = head->next;
            head->next = tmp;
            return tmp;
        }
        p = p->next;
    }
    return NULL;
}

int main() {
    Node<int, int> *head = new Node<int, int>;
    head->next = NULL;
    for(int i = 0; i < 10; i++) {
        Node<int, int> *tmp = new Node<int, int>;
        tmp->value.key = i;
        tmp->value.other = i * 2;
        tmp->next = head->next;
        head->next = tmp;
    }
    Node<int, int> *p = seqSearch(head, 5);
    Node<int, int> *q = head->next;
    while(q) {
        cout << q->value.key << " " << q->value.other << endl;
        q = q->next;
    }
    return 0;
}