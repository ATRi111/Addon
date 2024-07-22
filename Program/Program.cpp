#include "Program.h"
using namespace std;
using namespace Tools;

class Comparer
{
public:
    bool Compare(int a, int b)
    {
        return a > b;
    }
    int Print()
    {
        cout << this << endl;
        return 1;
    }
};

bool StataicCompare(int a, int b)
{
    return a > b;
}

int main()
{
    StaticFunc<bool,int,int> F1(StataicCompare);
    IFunc<bool, int, int>* p1 = &F1;

    Comparer c1, c2;
    MemberFunc<Comparer, bool, int, int> F2(&c1, &Comparer::Compare);
    MemberFunc<Comparer, bool, int, int> F3(&c2, &Comparer::Compare);
    
    cout << F1.Equal(F2) << endl;
    cout << F2.Equal(F1) << endl;
    cout << F2.Equal(F3) << endl;
    cout << F3.Equal(F2) << endl;
    cout << F1.Equal(F1) << endl;
    cout << F2.Equal(F2) << endl;
    cout << F3.Equal(F3) << endl;

    return 0;
}