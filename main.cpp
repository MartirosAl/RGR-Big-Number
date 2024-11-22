#include <iostream>
#include "BigNumber.h"


int main()
{
   

   //{ 1, 2, 3} ---> [0] = 1, [1] = 2, [3] = 3 ---> 321

   const size_t size = 2;
   Nial number[size] = { 1, 1 };
   BigNumber object(number, size);

   const size_t size2 = 4;
   Nial number2[size2] = { 1, 9, 4, 2};
   BigNumber object2(number2, size2);

   cout << object << ' ' << object.Get_Capacity() << ' ' << object.Get_Size() << endl;


   /*cin >> object;*/

   BigNumber object3(object * object2);
   cout << object3 << ' ' << object3.Get_Capacity() << ' ' << object3.Get_Size() << endl;


   return 0;
}