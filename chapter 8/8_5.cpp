#include <iostream>
using namespace std;

template<class KEY, class OTHER>
struct SET
{
    KEY key;
    OTHER other;
};

template<class KEY, class OTHER>
int seqSearch(SET<KEY, OTHER> data[], int size, const KEY &x) {
    data[0].key = x;
    int i = size;
    for(; x != data[i].key; i--);
    if(i != 0 && i != size) {
        SET<KEY, OTHER> tmp;
        tmp.key = data[i].key;
        tmp.other = data[i].other;
        data[i].key = data[i + 1].key;
        data[i].other = data[i + 1].other;
        data[i + 1].key = tmp.key;
        data[i + 1].other = tmp.other; 
    }
    return i;
} 

int main() {
    SET<int, int> s[11];
    for(int i = 1; i < 11; i++) {
        s[i].key = i;
        s[i].other = i;
    }
    int x = seqSearch(s, 10, 5);
    cout << x << endl;
    for(int i = 1; i < 11; i++) {
        cout << s[i].key << " ";
    }
    cout << endl;
    return 0;
}