#pragma once
#include <iostream>

using namespace std;

class BigNumber
{
   unsigned short int* number;   //������� ����� ���������� � ���� ������� ����� ��������������� �����
   size_t size;                  //���������� ���� � �����
   size_t capasity;              //���������� ���� ��� ������� �������� ������

public:

   BigNumber(unsigned short int* number_ = nullptr, size_t size_ = 0);

   BigNumber(const BigNumber& other_);

   unsigned short int& operator[](int index) const;

   unsigned short int& operator[](int index);

   BigNumber& operator=(const BigNumber& other_);

   BigNumber& operator+=(const BigNumber& other_) const;

   void Number_Shift(int index);

   void Expansion();

};

