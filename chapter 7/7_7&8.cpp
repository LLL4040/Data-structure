#include <iostream>
using namespace std;

template<class Type>
class priorityQueue
{
private:
    int currentSize;
    Type *array;
    int maxSize;

    void doubleSize();
    void buildHeap();
    void percolateDown(int hole);
public:
    priorityQueue();
    priorityQueue(int capacity);
    priorityQueue(const Type data[], int size);
    ~priorityQueue();
    bool isEmpty() const;
    void enQueue(const Type &x);
    Type deQueue();
    Type getHead() const;
    int findMin(Type x) const;
    void decreaseKey(int i, Type value);
    void show();
};

template<class Type>
priorityQueue<Type>::priorityQueue()
{
    array = new Type[10];
    maxSize = 10;
    currentSize = 0;
}

template<class Type>
priorityQueue<Type>::priorityQueue(int capacity)
{
    array = new Type[capacity];
    maxSize = capacity;
    currentSize = 0;
}

template<class Type>
priorityQueue<Type>::~priorityQueue()
{
    delete []array;
}

template<class Type>
bool priorityQueue<Type>::isEmpty() const
{
    return currentSize == 0;
}

template<class Type>
Type priorityQueue<Type>::getHead() const
{
    return array[1];
}

template<class Type>
void priorityQueue<Type>::enQueue(const Type &x)
{
    if(currentSize == maxSize - 1) doubleSize();

    int hole = ++currentSize;
    for(;hole > 1 && x < array[hole/2]; hole /= 2)
        array[hole] = array[hole/2];
    array[hole] = x;
}

template<class Type>
Type priorityQueue<Type>::deQueue()
{
    Type minItem;
    minItem = array[1];
    array[1] = array[currentSize--];
    percolateDown(1);
    return minItem;
}

template<class Type>
void priorityQueue<Type>::percolateDown(int hole)
{
    int child;
    Type tmp = array[hole];

    for(; hole * 2 < currentSize; hole = child){
        child = hole * 2;
        if(child != currentSize && array[child + 1] < array[child])
            child++;
        if(array[child] < tmp) array[hole] = array[child];
        else break;
    }
    array[hole] = tmp;
}

template<class Type>
void priorityQueue<Type>::buildHeap()
{
    for(int i = currentSize/2; i > 0; i--)
        percolateDown(i);
}

template<class Type>
priorityQueue<Type>::priorityQueue(const Type *items, int size):maxSize(size + 10), currentSize(size)
{
    array = new Type[maxSize];
    for(int i = 0; i < size; i++){
        array[i + 1] = items[i];
    }
    buildHeap();
}

template<class Type>
void priorityQueue<Type>::doubleSize()
{
    Type *tmp = array;
    maxSize *= 2;
    array = new Type[maxSize];
    for(int i = 1; i <= currentSize; i++){
        array[i] = tmp[i];
    }
    delete []tmp;
}

template<class Type>
int priorityQueue<Type>::findMin(Type x) const
{
    int m = 0;
    int i = 1;

    for(; i <= currentSize; i++){
        if(array[i] >= x){
            m = i;
            break;
        }
    }
    for(; i <= currentSize; i++){
        if(array[i] >= x){
            m = array[i] < array[m] ? i : m;
        }
    }
    return m;//找不到就返回0
}

template<class Type>
void priorityQueue<Type>::decreaseKey(int i, Type value)
{
    array[i] -= value;
    int p;
    for(; i > 1; i = p){
        p = i/2;
        if(array[i] < array[p]){
            Type tmp = array[i];
            array[i] = array[p];
            array[p] = tmp;
        }
    }
}

template<class Type>
void priorityQueue<Type>::show()
{
    for(int i = 1; i <= currentSize; i++){
        cout << array[i] << ' ';
    }
    cout << endl;
}

/* 找到最少背包数 */
int packNum(const double *item, int n)
{
    priorityQueue<double> a;
    int num = 0;
    for(int i = 0; i < n; i++)
        a.enQueue(1.0);
    for(int i = 0; i < n; i++){
        a.decreaseKey(a.findMin(item[i]), item[i]);
        if(!a.isEmpty() && a.getHead() == 0){
            num++;
            a.deQueue();
        }
    }
    while(!a.isEmpty())
        if(a.deQueue() < 1.0)
            num++;
    return num;
}

int main()
{
    /* 第七题测试 */
    priorityQueue<int> a;
    a.enQueue(1);
    a.enQueue(2);
    a.enQueue(8);
    a.enQueue(3);
    a.enQueue(7);
    a.enQueue(124);
    a.enQueue(999);
    a.enQueue(24);
    a.enQueue(78);
    a.enQueue(5);
    a.enQueue(6);
    a.enQueue(998);
    a.enQueue(996);
    a.show();
    cout << a.findMin(120) << endl;
    cout << a.findMin(1000) << endl;
    a.decreaseKey(7, 999);
    a.show();

    /* 第八题测试 */
    int n, num;
    double *ar;
    cout << "/***********************/" << endl;
    cout << "输入物品数n：" << endl;
    cin >> n;
    ar = new double[n];
    cout << "请依次输入物品重量" << endl;
    for(int i = 0; i < n; i++){
        cin >> ar[i];
    }
    num = packNum(ar, n);
    cout << "最少的背包数为：" << num << endl;
    return 0;
}
