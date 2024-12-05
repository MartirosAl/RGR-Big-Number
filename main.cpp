#include <iostream>
#include "BigNumber.h"


int main()
{
   

   //{ 1, 2, 3} <---> [0] = 1, [1] = 2, [3] = 3 <---> 321

   //const size_t size = 3;
   //short number[size] = { 9, 1, 2 };
   BigNumber object(2);

   //const size_t size2 = 3;
   //short number2[size2] = { 1, 9, 2};
   BigNumber object2(2);
   BigNumber object3;

         
   while (1)
   {
      cin >> object;
      cin >> object2;
      cout << object << ' ' << object.Get_Capacity() << ' ' << object.Get_Size() << endl;
      cout << object2 << ' ' << object2.Get_Capacity() << ' ' << object2.Get_Size() << endl;



      object3 = object * object2;
      cout << object3 << ' ' << object3.Get_Capacity() << ' ' << object3.Get_Size() << endl << endl;
      //object = object - object2;
   }

   return 0;
}