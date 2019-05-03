#include <iostream>
#include <string>
#include <stack>
using namespace std;

template <class T>
class hfTree{
    private:
        struct node {
            T data;
            int weight;
            node *left, *right;

            node(int w, node *l = NULL, node *r = NULL):weight(w), left(l), right(r){}
            node(const T &d, int w, node *l = NULL, node *r = NULL):data(d), weight(w), left(l), right(r){}
        };

        node *root;

        struct stacknode {
            node *n;
            string s;
            stacknode(node * node = NULL, string str = ""):n(node), s(str){}
        };

        void clear(node *t) {
            if(t == NULL) return;
            clear(t->left);
            clear(t->right);
            delete t;
        }

    public:
        struct hfCode {
            T data;
            string code;
        };

        hfTree(const T *v, const int *w, int size);
        void getCode(hfCode result[]);
        ~hfTree(){clear(root);}
};

template<class T>
hfTree<T>::hfTree(const T *v, const int *w, int size)
{
    int MAX = ((unsigned int)(1 << 31) - 1);
    int min1,min2;
    int x,y;
    node **ptr;

    ptr = new node *[size];
    for (int i = 0; i < size; i++) {
        ptr[i] = new node(v[i], w[i]);
    }

    for (int i = 1; i < size; i++) {
        min1 = min2 = MAX;
        for (int j = 0; j < size; j++) {
            if (ptr[j] == NULL) continue;
            if (ptr[j]->weight < min1) {
                min2 = min1;
                min1 = ptr[j]->weight;
                x = y;
                y = j;
            }else if (ptr[j]->weight < min2) {
                min2 = ptr[j]->weight;
                x = j;
            }
        }
        ptr[x] = new node(min1 + min2, ptr[x], ptr[y]);
        ptr[y] = NULL;
    }
    root = ptr[x];
    delete [] ptr;
}

template<class T>
void hfTree<T>::getCode(hfCode result[])
{
    stack<stacknode> s;
    int num = 0;
    stacknode now;

    if(root == NULL) return;
    s.push(stacknode(root, ""));

    while (!s.empty()) {
        now = s.top();
        s.pop();
        if (now.n->left == NULL) {
            result[num].data = now.n->data;
            result[num].code = now.s;
            num++;
            continue;
        }
        s.push(stacknode(now.n->left,now.s+'0'));
        s.push(stacknode(now.n->right,now.s+'1'));
    }
}

int main()
{
    char ch[] = {"abcdefg"};
    int w[] = {10,2,3,6,8,1,20};
    hfTree<char> tree(ch, w, 7);
    hfTree<char>::hfCode result[7];
    tree.getCode(result);

    for(int i = 0; i < 7; i++){
        cout << result[i].data << ' '<< result[i].code << endl;
    }
    return 0;
}