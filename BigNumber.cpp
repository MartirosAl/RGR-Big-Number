#include "BigNumber.h"


BigNumber::BigNumber(unsigned short int* number_, size_t size_)
{
   if (!number_)
   {
      number = new unsigned short int[100];
      capasity = 100;
      size = 0;
      return;
   }

   size_t i = 1;
   for (i = 1; 100 * i < size_; i++);
   capasity = 100 * i;
   number = new unsigned short int[capasity];
   size = size_;

   for (i = 0; i < size; i++)
      number[i] = number_[i];
}

BigNumber::BigNumber(const BigNumber& other_)
{
   size = other_.size;
   capasity = other_.capasity;
   number = new unsigned short int[capasity];
      
   try 
   {
      for (size_t i = 0; i < size; i++)
         number[i] = other_[i];
   }
   catch (char* messege)
   {
      cout << messege;
      delete[] number;
   }
}

unsigned short int& BigNumber::operator[](int index) const //l-value
{
   if (index >= 0 && index < size)
      return number[index];

   throw "Out of array";
}

unsigned short int& BigNumber::operator[](int index)       //r-value
{
   if (index >= 0 && index < size)
      return number[index];

   throw "Out of array";
}


void BigNumber::Expansion()
{
   ;
}