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

    cout << p1->Equal(F1) << endl;

    Comparer c;
    MemberFunc<Comparer, bool, int, int> F2(&c, &Comparer::Compare);
    
    //cout << p1->Equal(F2) << endl;

    return 0;
}