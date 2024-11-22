#include <iostream>
#include "BigNumber.h"


int main()
{
   const size_t size = 5;
   Nial number[size] = { 1, 2, 3, 4, 5 };
   BigNumber object(number, size);

   const size_t size2 = 3;
   Nial number2[size2] = { 1, 2, 3};
   BigNumber object2(number2, size2);

   cout << object << ' ' << object.Get_Capacity() << ' ' << object.Get_Size() << endl;


   /*cin >> object;*/
   BigNumber object3(object + object2);
   cout << object3 << ' ' << object3.Get_Capacity() << ' ' << object3.Get_Size() << endl;

   //cout << object2<< ' ' << object2.Get_Capacity() << ' ' << object2.Get_Size() << endl;
   return 0;
}