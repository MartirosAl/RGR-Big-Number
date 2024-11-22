#include <iostream>
#include "BigNumber.h"


int main()
{
   Nial number[5] = { 1, 2, 3, 4, 5 };
   BigNumber object(number, 5);
   cout << object << ' ' << object.Get_Capacity() << ' ' << object.Get_Size() << endl;

   cin >> object;

   cout << object << ' ' << object.Get_Capacity() << ' ' << object.Get_Size() << endl;
   return 0;
}