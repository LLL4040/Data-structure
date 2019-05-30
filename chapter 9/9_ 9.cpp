#include <iostream>
using namespace std;

/* KEY表示优先级，KEY越大优先级越高 */
template <class KEY>
class BinarySearchQueue
{ 
    private:
        struct BinaryNode
        {
            KEY data;
            BinaryNode *left;
            BinaryNode *right;
            BinaryNode(const KEY &thedata, BinaryNode *lt = NULL, BinaryNode *rt = NULL):data(thedata), left(lt), right(rt) {}
        };
        BinaryNode *root;

    public:
        BinarySearchQueue(const KEY &x);
        ~BinarySearchQueue();

        /* 优先级队列的操作 */
        bool isEmpty() const;
        void enQueue(const KEY &x);
        KEY deQueue();

    private:    
        void insert(const KEY &x, BinaryNode *&t);
        KEY remove(BinaryNode *&t);
        void makeEmpty(BinaryNode *t);
};

template <class KEY>
BinarySearchQueue<KEY>::BinarySearchQueue(const KEY &x)
{
    root = new BinaryNode(x, NULL, NULL);
}

template <class KEY>
BinarySearchQueue<KEY>::~BinarySearchQueue()
{
    makeEmpty(root);
}
template <class KEY>
void BinarySearchQueue<KEY>::makeEmpty(BinaryNode *t)
{
    if (t == NULL) return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
    t = NULL;
}

template <class KEY>
bool BinarySearchQueue<KEY>::isEmpty() const
{
    return root == NULL;
}

template <class KEY>
void BinarySearchQueue<KEY>::enQueue(const KEY &x)
{
    insert(x, root);
}
template <class KEY>
void BinarySearchQueue<KEY>::insert(const KEY &x, BinaryNode *&t)
{	    
    if (t == NULL) t = new BinaryNode(x, NULL, NULL);
    else if (x < t->data) insert(x, t->left);
	else if (t->data < x) insert(x, t->right);
}

template <class KEY>
KEY BinarySearchQueue<KEY>::deQueue()
{
    return remove(root);
}
template <class KEY>
KEY  BinarySearchQueue<KEY>::remove(BinaryNode *&t)
{
    if (t->right == NULL) 
    {
        BinaryNode *oldNode = t;
        KEY x = t->data;
        t = (t->left != NULL) ? t->left : t->right;
        return x;
    }
    return remove(t->right);
}

int main()
{
    BinarySearchQueue<int> queue(0);
    queue.deQueue();
    cout << queue.isEmpty() << endl;
    queue.enQueue(1);
    queue.enQueue(9);
    queue.enQueue(3);
    cout << queue.deQueue() << endl;
    queue.enQueue(2);
    queue.enQueue(7);
    queue.enQueue(8);
    cout << queue.deQueue() << endl;
    queue.enQueue(5);
    queue.enQueue(4);
    queue.enQueue(6);
    cout << queue.deQueue() << endl;
    return 0;
}