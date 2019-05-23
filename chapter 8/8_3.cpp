#include <iostream>
using namespace std;

template<class T>
class Set {
    template<class U>
    friend Set<U> operator+ (const Set<U> &x, const Set<U> &y);
    template<class U>
    friend Set<U> operator* (const Set<U> &x, const Set<U> &y);
    template<class U>
    friend Set<U> operator- (const Set<U> &x, const Set<U> &y);

    private:
        T *array;
        int size, maxSize;
        void doubleSpace();
        bool has(T x) const;

    public:
        Set();
        Set(const Set<T> &x);
        ~Set() {delete[] array;}
        
        int getSize() const {return size;}
        bool insert(T x);
        bool remove(T x);
        void show() const;
        Set<T> &operator= (const Set<T> &x);
};

template<class T>
Set<T>::Set() {
    size = 0;
    maxSize = 10;
    array = new T[maxSize];
}

template<class T>
Set<T>::Set(const Set<T> &x) {
    size = x.size;
    maxSize = x.maxSize;
    array = new T[maxSize];
    for(int i = 0; i < size; i++) {
        array[i] = x.array[i];
    }
}

template<class T>
void Set<T>::doubleSpace() {
    T *tmp = array;
    array = new T[maxSize * 2];
    for(int i = 0; i < maxSize; i++) {
        array[i] = tmp[i];
    }
    maxSize *= 2;
    delete[] tmp;
}

template<class T>
bool Set<T>::has(T x) const {
    for(int i = 0; i < size; i++) {
        if(array[i] == x) return true;
    }
    return false;
}

template<class T>
bool Set<T>::insert(T x) {
    if(has(x)) return false;
    if(size == maxSize) doubleSpace();
    array[size] = x;
    size++;
    return true;
}

template<class T>
bool Set<T>::remove(T x) {
    bool flag = false;
    for(int i = 0; i < size; i++) {
        if(array[i] == x) {
            flag = true;
            for(int j = i; j < size - 1; j++) {
                array[j] = array[j + 1];
            }
        }
    }
    size--;
    return flag;
}

template<class T>
void Set<T>::show() const {
    for(int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

template<class T>
Set<T>& Set<T>::operator= (const Set<T> &x) {
    size = x.size;
    maxSize = x.maxSize;
    delete[] array;
    array = new T[maxSize];
    for(int i = 0; i < size; i++) {
        array[i] = x.array[i];
    }
    return *this;
}

template<class U>
Set<U> operator+ (const Set<U> &x, const Set<U> &y) {
    //Set<U> tmp(x);
    Set<U> tmp;
    tmp = x;
    for(int i = 0; i < y.size; i++) {
        tmp.insert(y.array[i]);
    }
    return tmp;
}

template<class U>
Set<U> operator* (const Set<U> &x, const Set<U> &y) {
    Set<U> tmp;
    for(int i = 0; i < x.size; i++) {
        if(y.has(x.array[i])) {
            tmp.insert(x.array[i]);
        }
    }
    return tmp;
}

template<class U>
Set<U> operator- (const Set<U> &x, const Set<U> &y) {
    Set<U> tmp;
    for(int i = 0; i < x.size; i++) {
        if(!y.has(x.array[i])) {
            tmp.insert(x.array[i]);
        }
    }
    return tmp;
}

int main() {
    Set<int> a, b, c;
    a.insert(0);
    a.insert(1);
    a.insert(2);
    b.insert(1);
    b.insert(2);
    b.insert(3);
    cout << "a = "; a.show();
    cout << "b = "; b.show();
    c = a + b;
    cout << "a + b = "; c.show();
    c = a * b;
    cout << "a * b = "; c.show();
    c = a - b;
    cout << "a - b = "; c.show();
    return 0;
}