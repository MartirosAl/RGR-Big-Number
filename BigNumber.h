#pragma once
#include <iostream>
typedef unsigned short int Nial; //Non-negative integers of arbitrary length

using namespace std;

class BigNumber
{
   //����� ���������� � ������ 0, � ������������� � size - 1
   //BigNumber 123  ->   [0] = 3   [1] = 2   [2] = 1
   Nial* number;   //������� ����� ���������� � ���� ������� ����� ��������������� �����
   size_t size;                  //���������� ���� � �����
   size_t capacity;              //���������� ���� ��� ������� �������� ������

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



   //������ �������� �������
   void Clear();

   //����� �����. ���������� �������� �� index_
   void Number_Shift(size_t index_);


   //���������� ������� �� capacity + 100
   void Expansion();

   //���������� ������� �� new_cap_, ���� new_cap_ > capasity
   void Expansion(size_t new_cap_);

   //����� ������ ���� �� size - 1 �� 0, �.�. ����� ����� � 0 ������, � ������ � size - 1
   // BigNumber 123  ->   [0] = 3   [1] = 2   [2] = 1
   friend ostream& operator<<(ostream& stream, const BigNumber& object_);

   friend istream& operator>>(istream& stream, BigNumber& object_);
};

