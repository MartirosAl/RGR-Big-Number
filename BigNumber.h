#pragma once
#include <iostream>
#include "Iterator.h"

using namespace std;

class BigNumber
{
   //����� ���������� � ������ 0, � ������������� � size - 1
   //BigNumber 123  ->   [0] = 3   [1] = 2   [2] = 1
   short* number;   //������� ����� ���������� � ���� ������� ����� ��������������� �����
   size_t size;                  //���������� ���� � �����
   size_t capacity;              //���������� ���� ��� ������� �������� ������

public:

   BigNumber(size_t new_cap_ = 100);

   BigNumber(const short* number_, const size_t size_);

   ~BigNumber();

   BigNumber(const BigNumber& other_);

   void Set_Number(const short* new_number_);

   void Set_Number(const short* new_number_, size_t new_size_);

   void Set_Capacity(const size_t new_capacity_);

   void Set_Size(const size_t new_size_);

   short* Get_Number() const;

   size_t Get_Capacity() const;

   size_t Get_Size() const;

   short& operator[](size_t index_) const;

   short& operator[](size_t index_);

   operator bool() const;

   BigNumber& operator++();

   BigNumber operator++(int);

   BigNumber& operator--();

   BigNumber operator--(int);

   BigNumber& operator=(const BigNumber& other_);

   BigNumber operator+(BigNumber& other_);

   BigNumber operator*(BigNumber& other_);

   //�������� �����
   BigNumber operator-(BigNumber& other_);

   BigNumber operator/(BigNumber& other_);

   BigNumber operator%(BigNumber& other_);

   bool operator!();

   bool operator<(BigNumber& other_);

   bool operator==(BigNumber& other_);

   bool operator<=(BigNumber& other_);

   bool operator>(BigNumber& other_);

   bool operator>=(BigNumber& other_);

   bool operator!=(BigNumber& other_);

/*   bool operator<(short digit_);

   bool operator==(short digit_);

   bool operator<=(short digit_);

   bool operator>(short digit_);

   bool operator>=(short digit_);

   bool operator!=(short digit_);  */ 
   
/*bool operator<(short* digit_);

   bool operator==(short* digit_);

   bool operator<=(short* digit_);

   bool operator>(short* digit_);

   bool operator>=(short* digit_);

   bool operator!=(short* digit_);*/

   //������ �������� �������
   void Clear();

   //����� �����. ���������� �������� �� index_
   void Number_Shift(size_t index_);

   void Push_Back(short digit_);

   void Push_Back(short* digit_, size_t size_);

   //���������� ������� �� capacity + 100
   void Expansion();

   //���������� ������� �� new_cap_, ���� new_cap_ > capacity
   void Expansion(size_t new_cap_);

   //����� ������ ���� �� size - 1 �� 0, �.�. ����� ����� � 0 ������, � ������ � size - 1
   // BigNumber 123  ->   [0] = 3   [1] = 2   [2] = 1
   friend ostream& operator<<(ostream& stream, const BigNumber& object_);

   //���� ������ ���� �� size - 1 �� 0, �.�. ����� ����� � 0 ������, � ������ � size - 1
   // BigNumber 123  ->   [0] = 3   [1] = 2   [2] = 1
   friend istream& operator>>(istream& stream, BigNumber& object_);

   Iterator begin() const
   {
      return Iterator(number);
   }

   Iterator end() const
   {
      return Iterator(nullptr);
   }
};


