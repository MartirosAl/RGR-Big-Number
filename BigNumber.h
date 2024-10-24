#pragma once
#include <iostream>

using namespace std;

class BigNumber
{
   unsigned short int* number;   //Большое число записанное в виде массива char
   size_t size;                  //Количество цифр в числе
   size_t capasity;              //Количество цифр для которых выделена память

public:

   BigNumber(unsigned short int* number_ = nullptr, size_t size_ = 0);

   BigNumber(const BigNumber& other_);

   unsigned short int& operator[](int index) const;

   unsigned short int& operator[](int index);

   void Expansion();

};

