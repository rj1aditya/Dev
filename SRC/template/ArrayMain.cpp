#include"Array.h"

int main()
{
    Array<int> objInt(10);
    Array<double> objDouble(10);

    for(int i = 0; i < objInt.getLength(); i++ )
    {
        objInt[i] = i;
        objDouble[i] = i+0.5;
    }

    for(int i = objInt.getLength() -1; i >= 0; i-- )
    {
        cout<<objInt[i]<<"   "<<objDouble[i]<<endl;
    }
};