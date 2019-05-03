#include "linkQueue.h"

template<class T>
class bTree {
    public:
        virtual void clear() = 0;
        virtual bool isEmpty() const = 0;
        virtual T Root(T flag) const = 0;
        virtual T parent(T x, T flag) const = 0;
        virtual T lchild(T x, T flag) const = 0;
        virtual T rchild(T x, T flag) const = 0;
        virtual void delLeft(T x) = 0;
        virtual void delRight(T x) = 0;
        virtual void preOrder() const = 0;
        virtual void midOrder() const = 0;
        virtual void postOrder() const = 0;
        virtual void levelOrder() const = 0;
};

template<class T>
class binaryTree:public bTree<T> {
    template<typename U>
    friend void printTree(const binaryTree<U> &t, U flag);

    private:
        struct Node {
            Node *left, *right;
            T data;

            Node():left(NULL),right(NULL) {}
            Node(T item, Node *L = NULL, Node *R = NULL):data(item), left(L), right(R) {}
            ~Node() {}
        };

        struct list {
            Node *p;
            int num;
        };

        Node *root;
    
    public:
        binaryTree():root(NULL) {}
        binaryTree(T x) {root = new Node(x);}
        ~binaryTree();
        void clear();
        bool isEmpty() const;
        T Root(T flag) const;
        T lchild(T x, T flag) const;
        T rchild(T x, T flag) const;
        void delLeft(T x);
        void delRight(T x);
        void preOrder() const;
        void midOrder() const;
        void postOrder() const;
        void levelOrder() const;
        void createTree(T flag);
        T parent(T x, T flag) const {return flag;}

        bool isCompleteTree() const;//判断是否是完全二叉树

    private:
        Node *find(T x, Node *t) const;
        void clear(Node *&t);
        void preOrder(Node *t) const;
        void midOrder(Node *t) const;
        void postOrder(Node *t) const;
};

template<class T>
bool binaryTree<T>::isEmpty() const {
    return root == NULL;
}

template<class T>
T binaryTree<T>::Root(T flag) const {
    if (root == NULL) return flag;
    else return root->data;
}

template<class T>
void binaryTree<T>::clear(binaryTree<T>::Node *&t) {
    if (t == NULL) return;
    clear(t->left);
    clear(t->right);
    delete t;
    t = NULL;
}

template<class T>
void binaryTree<T>::clear() {
    clear(root);
}

template<class T>
binaryTree<T>::~binaryTree() {
    clear(root);
}

template<class T>
void binaryTree<T>::preOrder(binaryTree<T>::Node *t) const {
    if (t == NULL) return;
    cout << t-> data << ' ';
    preOrder(t->left);
    preOrder(t->right);
}

template<class T>
void binaryTree<T>::preOrder() const {
    cout << "\n前序遍历：";
    preOrder(root);
}

template<class T>
void binaryTree<T>::postOrder(binaryTree<T>::Node *t) const {
    if (t == NULL) return;
    postOrder(t->left);
    postOrder(t->right);
    cout << t->data << ' ';
}

template<class T>
void binaryTree<T>::postOrder() const {
    cout << "\n后序遍历：";
    postOrder(root);
}

template<class T>
void binaryTree<T>::midOrder(binaryTree<T>::Node *t) const {
    if (t == NULL) return;
    midOrder(t->left);
    cout << t->data << ' ';
    midOrder(t->right);
}

template<class T>
void binaryTree<T>::midOrder() const {
    cout << "\n中序遍历：";
    midOrder(root);
}

template<class T>
void binaryTree<T>::levelOrder() const {
    linkQueue<Node *> que;
    Node *tmp;

    cout << "\n层次遍历：";
    que.enQueue(root);

    while (!que.isEmpty()) {
        tmp = que.deQueue();
        cout << tmp->data << ' ';
        if (tmp->left) que.enQueue(tmp->left);
        if (tmp->right) que.enQueue(tmp->right);
    }
}

template<class T>
typename binaryTree<T>::Node* binaryTree<T>::find(T x, binaryTree<T>::Node *t) const {
    Node *tmp;
    if (t == NULL) return NULL;
    if (t->data == x) return t;
    if (tmp = find(x, t->left)) return tmp;
    else return find(x, t->right);
}

template<class T>
void binaryTree<T>::delLeft(T x) {
    Node *tmp = find(x, root);
    if (tmp == NULL) return;
    clear(tmp->left);
}

template<class T>
void binaryTree<T>::delRight(T x) {
    Node *tmp = find(x, root);
    if (tmp == NULL) return;
    clear(tmp->right);
}

template<class T>
T binaryTree<T>::lchild(T x, T flag) const {
    Node *tmp = find(x, root);
    if (tmp == NULL || tmp->left == NULL) return flag;

    return tmp->left->data;
}

template<class T>
T binaryTree<T>::rchild(T x, T flag) const {
    Node *tmp = find(x, root);
    if (tmp == NULL || tmp->right == NULL) return flag;

    return tmp->right->data;
}

template<class T>
void binaryTree<T>::createTree(T flag) {
    linkQueue<Node *> que;
    Node *tmp;
    T x, ldata, rdata;

    cout << "\n输入根结点：";
    cin >> x;
    root = new Node(x);
    que.enQueue(root);

    while (!que.isEmpty()) {
        tmp = que.deQueue();
        cout << "\n输入" << tmp->data << "的两个儿子（" << flag << "表示空结点）：";
        cin >> ldata >> rdata;
        if (ldata != flag) que.enQueue(tmp->left = new Node(ldata));
        if (rdata != flag) que.enQueue(tmp->right = new Node(rdata));
    }

    cout << "\ncreate completed!\n";
}

template<class U>
void printTree(const binaryTree<U> &t, U flag) {
    linkQueue<U> q;
    q.enQueue(t.root->data);
    cout << endl;
    while (!q.isEmpty()) {
        U p, l, r;
        p = q.deQueue();
        l = t.lchild(p, flag);
        r = t.rchild(p, flag);
        cout << p << " " << l << " " << r << endl;
        if (l != flag) q.enQueue(l);
        if (r != flag) q.enQueue(r);
    }
}

template<class T>
bool binaryTree<T>::isCompleteTree() const {
    
    
    list cur, child;
    linkQueue<list> q;
    int count = 1, last = 1;

    if (root == NULL) return true;

    cur.p = root;
    cur.num = 1;
    q.enQueue(cur);
    while (!q.isEmpty()) {
        cur = q.deQueue();
        if (cur.p->left != NULL) {
            count++;
            child.p = cur.p->left;
            last = child.num = cur.num * 2;
            q.enQueue(child);
        }
        if (cur.p->right != NULL) {
            count++;
            child.p = cur.p->right;
            last = child.num = cur.num * 2 + 1;
            q.enQueue(child);
        }
    }
    return count == last;
}

int main()
{
    binaryTree<char> tree;

    tree.createTree('@');
    if (tree.isCompleteTree()) cout << "该树是完全二叉树！" << endl;
    else cout << "该树不是完全二叉树！" << endl;
    tree.preOrder();
    tree.midOrder();
    tree.postOrder();
    tree.levelOrder();
    printTree(tree, '@');

    return 0;
}