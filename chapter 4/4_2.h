#ifndef SEQQUEUE
#define SEQQUEUE

# include <stdlib.h>
# include <time.h>
# include <iostream>
using namespace std;

/* ���г����� */
template<class elemType>
class queue
{
    public:
        virtual bool isEmpty()const =0;                   //�п�
        virtual void enQueue(const elemType &x)=0;  //����
        virtual elemType deQueue()=0;               //����
        virtual elemType getHead()const =0;               //�õ�����Ԫ��
        virtual ~queue() {}
};

/* ѭ�������� */
template<class elemType>
class seqQueue: public queue<elemType>
{
    private:
        elemType *elem;
        int maxSize;
        int front, rear;
        void doubleSpace();

    public:
        seqQueue(int size = 10);
        ~seqQueue();
        bool isEmpty() const;
        void enQueue(const elemType &x);
        elemType deQueue();
        elemType getHead() const;
};

template<class elemType>
seqQueue<elemType>::seqQueue(int size)
{
    elem = new elemType[size];
    maxSize = size;
    front = rear = 0;
}

template<class elemType>
seqQueue<elemType>::~seqQueue()
{
    delete[] elem;
}

template<class elemType>
void seqQueue<elemType>::enQueue(const elemType &x)
{
    if ((rear + 1) % maxSize == front)
        doubleSpace();
    rear = (rear + 1) % maxSize;
    elem[rear] = x;
}

template<class elemType>
void seqQueue<elemType>::doubleSpace()
{
    elemType *tmp = elem;
    elem = new elemType[2 * maxSize];
    for (int i = 1; i < maxSize; i++)
        elem[i] = tmp[(front + i) % maxSize];
    
    front = 0;
    rear = maxSize - 1;
    maxSize *= 2;
    delete[] tmp;
}

template<class elemType>
elemType seqQueue<elemType>::deQueue()
{
    front = (front + 1) % maxSize;
    return elem[front];
}

template<class elemType>
elemType seqQueue<elemType>::getHead() const
{
    return elem[(front + 1) % maxSize];
}

template<class elemType>
bool seqQueue<elemType>::isEmpty() const
{
    return front == rear;
}

#endif // SEQQUEUE