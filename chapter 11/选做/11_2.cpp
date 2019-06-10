#include <iostream>
#include <fstream>
using namespace std;

void merge(const char *in1, const char *in2, const char *out);

int main()
{
    char f1[] = "1.txt";
    char f2[] = "2.txt";
    char f3[] = "0.txt";
    merge(f1, f2, f3);
    return 0;
}

void merge(const char *in1, const char *in2, const char *out)
{
    ifstream if1, if2;
    ofstream of;
    if1.open(in1);
    if2.open(in2);
    of.open(out);

    int a, b;
    if1 >> a;
    if2 >> b;

    while(!if1.eof() && !if2.eof())
    {
        if(a < b)
        {
            of << a << " ";
            if1 >> a;
        }
        else
        {
            of << b << " ";
            if2 >> b;
        }
    }

    while(!if1.eof())
    {
        of << a << " ";
        if1 >> a;
    }

    while(!if2.eof())
    {
        of << b << " ";
        if2 >> b;
    }

    if1.close();
    if2.close();
    of.close();
}