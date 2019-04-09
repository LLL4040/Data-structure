#include<iostream>
using namespace std;

template <class elemType>
class stack
{
	public:
        virtual bool isEmpty(const int id)const=0;// 判栈空
        virtual void push(const int id, const elemType &x)=0;// 进栈
        virtual elemType pop(const int id)=0;// 出栈
        virtual elemType top(const int id)const=0; // 取栈顶元素
        virtual ~stack() {} // 虚析构函数
};

template <class elemType>
class seqStack: public stack<elemType>
{
    private:
        elemType *elem;
        int top_p1, top_p2;
        int maxSize;
        void doubleSpace();
    public:
        seqStack(int initSize = 10);
        ~seqStack();
        bool isEmpty(const int id)const;
        void push(const int id, const elemType &x);
        elemType pop(const int id);
        elemType top(const int id)const;
};

template <class elemType>
seqStack<elemType>::seqStack(int initSize)
{
    elem = new elemType[initSize];
    maxSize = initSize;
    top_p1 = -1;
    top_p2 = maxSize;
}

template <class elemType>
seqStack<elemType>::~seqStack()
{
    delete[] elem;
}

template <class elemType>
bool seqStack<elemType>::isEmpty(const int id)const
{
    if (id == 1)
        return top_p1 == -1;
    else
        return top_p2 == maxSize;
}

template <class elemType>
void seqStack<elemType>::push(const int id, const elemType &x)
{
    if (top_p1 + 1 == top_p2)
        doubleSpace();

    if (id == 1)
        elem[++top_p1] = x;
    else
        elem[--top_p2] = x;
}

template <class elemType>
elemType seqStack<elemType>::pop(const int id)
{
    if (id == 1)
        return elem[top_p1--];
    return elem[top_p2++];
}

template <class elemType>
elemType seqStack<elemType>::top(const int id)const
{
    if (id == 1)
        return elem[top_p1];
    return elem[top_p2];
}

template <class elemType>
void seqStack<elemType>::doubleSpace()
{
    elemType *tmp = elem;

    elem = new elemType[2 * maxSize];

    for (int i = 0; i <= top_p1; ++i)
        elem[i] = tmp[i];
    for (int i = maxSize - 1; i >= top_p2; --i)
        elem[i + maxSize] = tmp[i];
    top_p2 += maxSize;
    maxSize *= 2;
    delete[] tmp;
}


int main()
{
    seqStack<int> a(10);
    cout << "栈a(int类型)是一个双栈，可分别对栈1和栈2进行pop、push、top和isEmpty操作" << endl;
    cout << "进行 pop 操作请输入 1" << endl;
    cout << "进行 push 操作请输入 2" << endl;
    cout << "进行 top 操作请输入 3" << endl;
    cout << "进行 isEmpty 操作请输入 4" << endl;
    cout << "退出请输入 0" << endl;

    int n, id, x;
    cin >> n;
    while (n)
    {
        cout << "请输入要操作的栈id (1或2)" << endl;
        cin >> id;
        switch (n)
        {
            case 1:
                if (a.isEmpty(id))
                {
                    cout << "a中id为" << id << "的栈为空，无法pop" << endl;
                }
                else
                {
                    cout << "a.pop(" << id << ") = " << a.pop(id) << endl;
                }
                break;
            case 2:
                cout << "请输入要push的整型数" << endl;
                cin >> x;
                a.push(id, x);
                cout << "成功push" << endl;
                break;
            case 3:
                if (a.isEmpty(id))
                {
                    cout << "a中id为" << id << "的栈为空，无法top" << endl;
                }
                else
                {
                    cout << "a.top(" << id << ") = " << a.top(id) << endl;
                }
                break;
            case 4:
                if (a.isEmpty(id))
                {
                    cout << "a中id为" << id << "的栈为空" << endl;
                }
                else
                {
                    cout << "a中id为" << id << "的栈不为空" << endl;
                }
                break;

            default:
                cout << "请输入0-4选择操作" << endl;
                break;
        }
        cout << "退出请输入0，否则输入1-4选择对应的操作" << endl;
        cin >> n;
    }

    cout << "Have a nice day :)" << endl;
    return 0;
}
