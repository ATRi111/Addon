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
    Comparer c1, c2;
    
    Func<int> Fs;
    for (int i = 0; i < 3; i++)
    {
        Fs.Add(&c1, &Comparer::Print);
        Fs.Invoke();
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < 3; i++)
    {
        Fs.Remove(&c1, &Comparer::Print);
        Fs.Invoke();
        cout << endl;
    }

    return 0;
}