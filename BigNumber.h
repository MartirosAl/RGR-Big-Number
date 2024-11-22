#pragma once
#include <iostream>
typedef unsigned short int Nial; //Non-negative integers of arbitrary length

using namespace std;

class BigNumber
{
   //Число начинается с ячейки 0, а заканчивается в size - 1
   //BigNumber 123  ->   [0] = 3   [1] = 2   [2] = 1
   Nial* number;   //Большое число записанное в виде массива целых неотрицательных чисел
   size_t size;                  //Количество цифр в числе
   size_t capacity;              //Количество цифр для которых выделена память

public:

   BigNumber(size_t new_cap_ = 100);

   BigNumber(const Nial* number_, const size_t size_);

   ~BigNumber();

   BigNumber(const BigNumber& other_);

   size_t Get_Capacity();

   size_t Get_Size();

   Nial& operator[](size_t index_) const;

   Nial& operator[](size_t index_);

   BigNumber& operator=(const BigNumber& other_);

   BigNumber operator+(BigNumber& other_);

   BigNumber operator*(BigNumber& other_);



   //Полное очищение массива
   void Clear();

   //Сдвиг чисел. Увеличение разрядов на index_
   void Number_Shift(size_t index_);


   //Расширение массива на capacity + 100
   void Expansion();

   //Расширение массива до new_cap_, если new_cap_ > capasity
   void Expansion(size_t new_cap_);

   //Вывод должен быть от size - 1 до 0, т.к. конец числа в 0 ячейке, а начало в size - 1
   // BigNumber 123  ->   [0] = 3   [1] = 2   [2] = 1
   friend ostream& operator<<(ostream& stream, const BigNumber& object_);

   friend istream& operator>>(istream& stream, BigNumber& object_);
};

