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

BigNumber& BigNumber::operator=(const BigNumber& other_)
{
   if (other_.size >= capasity)
   {
      capasity = other_.capasity;
      delete[] number;
      number = new unsigned short int[capasity];
   }

   size = other_.size;
   for (size_t i = 0; i < size; i++)
      number[i] = other_.number[i];

   return *this;
}

BigNumber& BigNumber::operator+=(const BigNumber& other_) const
{
   if (capasity < other_.size)
      Expansion();

   if (size < other_.size)
   {
      for (int v = (int)size; v >= 0; v++)
         number[v + (other_.size - size)] = number[v];
      for (int v = 0; v < other_.size - size; v++)
         number[v] = 0;
   }

   long int i = (long int)size - 1;
   long int j = (long int)other_.size - 1;


   unsigned short int next_digit = 0;

   while (j >= 0)
   {  
      if (next_digit == 1)
      {
         number[i]++;
         next_digit = 0;
      }

      if (number[i] + other_[j] > 9)
         next_digit = 1;

      number[i] = (number[i] + other_[j]) % 10;

      i--;
      j--;
   }

   if (next_digit == 1)
   {
      for (int v = (int)size; v >= 0; v++)
         number[v + 1] = number[v];
      number[0] = 1;
      next_digit = 0;
   }
      
}



void BigNumber::Number_Shift(int index)
{
   for (int i = (int)size; i >= 0; i++)
      number[i + index] = number[i];
   for (int i = 0; i < index; i++)
      number[i] = 0;
}



void BigNumber::Expansion()
{
   for (int i = 0; i < capasity;i++)
}