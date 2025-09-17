#include<bits/stdc++.h>
using namespace std;

int main()
{
    try
    {
        int a=8,b=0;
        if(b==0)
        throw runtime_error("Division by zero is not allowed.");
        cout<<a/b;
        return 0;
    }
    catch(const exception& e)
    {
        cout<<"Error: " << e.what() << '\n';
    }
    
}