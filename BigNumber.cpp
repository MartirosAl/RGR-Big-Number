#include "BigNumber.h"

BigNumber::BigNumber(size_t new_cap_)
{
   number = new short[new_cap_];
   capacity = new_cap_;
   size = 0;
}

BigNumber::BigNumber(const short* number_, const size_t size_)
{
   size_t i = 1;
   for (i = 1; 100 * i < size_; i++);
   capacity = 100 * i;
   number = new short[capacity];
   size = size_;

   for (i = 0; i < size; i++)
      number[i] = number_[i];
}

BigNumber::~BigNumber()
{
   if (number)
      delete[] number;
   number = nullptr;
   size = 0;
   capacity = 0;
}

BigNumber::BigNumber(const BigNumber& other_)
{
   size = other_.size;
   capacity = other_.capacity;
   number = new short[other_.capacity];
   
   for (size_t i = 0; i < other_.size; i++)
      number[i] = other_[i];

}

size_t BigNumber::Get_Capacity()
{
   return capacity;
}

size_t BigNumber::Get_Size()
{
   return size;
}

short& BigNumber::operator[](size_t index_) const
{
   if (index_ > capacity)
      throw "Out of range";
   return number[index_];
}

short& BigNumber::operator[](size_t index_) 
{
   if (index_ > capacity)
      throw "Out of range";
   return number[index_];
}

BigNumber& BigNumber::operator=(const BigNumber& other_)
{
   if (other_.size >= capacity)
   {
      this->Clear();
      capacity = other_.capacity;
      number = new short[other_.capacity];
   }

   size = other_.size;
   for (size_t i = 0; i < size; i++)
      number[i] = other_[i];

   return *this;
}

BigNumber BigNumber::operator+(BigNumber& other_) 
{
   if (size == 0 || other_.size == 0)
   {
      BigNumber result(size == 0 ? other_ : *this);
      return result;
   }

   BigNumber* max_number = (size > other_.size ? this : &other_);
   BigNumber* min_number = (size < other_.size ? this : &other_);


   //Выбираем где больше места + 1, чтобы не трогать Expansion 
   // //Можно было реализовать и с *max_number, но тогда ножно было бы делать расширение, а это менее эффективно
   BigNumber result(max_number ->capacity);
   result.size = max_number->size;

   short adddigit = 0;

   for (size_t i = 0; i < min_number->size; i++)
   {
      result[i] = ((*max_number)[i] + (*min_number)[i] + adddigit) % 10;
      adddigit = ((*max_number)[i] + (*min_number)[i] + adddigit) / 10;
   }

   //Смотрим что больше и дополняем до него
   for (size_t i = min_number->size; i < max_number->size; i++)
   {
      result[i] = (adddigit + (*max_number)[i]) % 10;
      adddigit = (adddigit + (*max_number)[i]) / 10;
   }

   if (adddigit)
   {
      result[max_number->size] = adddigit;
      result.size++;
   }
   
   return result;
}

BigNumber BigNumber::operator*(BigNumber& other_)
{
   BigNumber* result = new BigNumber(size + other_.size);
   for (size_t i = 0; i < result->capacity; i++)
      (*result)[i] = 0;

   for (size_t i = 0; i < size; i++)
   {
      for (size_t j = 0; j < other_.size; j++)
      {
         (*result)[i + j] += number[i] * other_[j];
         (*result)[i + j + 1] += (*result)[i + j] / 10;
         (*result)[i + j] %= 10;
      }
   }
   result->size = size + other_.size - 1;
   if ((*result)[result->size] != 0)
      size++;
   return (*result);
}

BigNumber BigNumber::operator-(BigNumber& other_)
{
   if (*this < other_)
   {
      BigNumber result(1);
      result[0] = 0;
      result.size = 1;
      return result;
   }
   
   BigNumber* max_number = this;
   BigNumber* min_number = &other_;

   BigNumber result(*max_number);

   for (size_t i = 0; i < min_number->size; i++)
   {
     
      result[i] = result[i] - (*min_number)[i];
      result[i + 1] = result[i] < 0 ? result[i + 1] - 1 : result[i + 1];
      result[i] = result[i] < 0 ? 10 + result[i] : result[i];
      
   }

   for (size_t i = size - 1; result[i] == 0 && i > 0; i--)
      result.size--;

   return result;
}

bool BigNumber::operator<(BigNumber& other_)
{
   if (size != other_.size)
      return size < other_.size;
   for (size_t i = size; i > 0; i--)
   {
      if (number[i - 1] != other_[i - 1])
         return number[i - 1] < other_[i - 1];
   }

   return false;
}



void BigNumber::Clear()
{
   delete[] number;
   number = nullptr;
   size = 0;
   capacity = 0;
}


void BigNumber::Number_Shift(size_t index_)
{
   if (index_ == 0)
      return;
   while (capacity < size + index_)
      Expansion();
   //size_t i = 0 - 1 это очень много
   if (size == 0)
   {
      number[0] = 0;
      size++;
      return;
   }
   
   //Идем от последнего числа
   for (size_t i = size - 1; i > 0; i--)
   {
      number[i + index_] = number[i];
   }
   number[index_] = number[0];
   for (size_t i = 0; i < index_; i++)
      number[i] = 0;
   size += index_;
}

void BigNumber::Expansion()
{
   short* temp_arr = new short[size];

   for (size_t i = 0; i < size; i++)
      temp_arr[i] = number[i];

   if (capacity > 0)
      delete[] number;
   
   number = new short[capacity + 100];
   capacity += 100;

   for (size_t i = 0; i < size; i++)
      number[i] = temp_arr[i];
   
}

void BigNumber::Expansion(size_t new_cap_)
{
   if (new_cap_ <= capacity)
      return;

   short* temp_arr = new short[size];

   for (size_t i = 0; i < size; i++)
      temp_arr[i] = number[i];

   
   number = new short[new_cap_];
   capacity = new_cap_;

   for (size_t i = 0; i < size; i++)
      number[i] = temp_arr[i];
}

ostream& operator<<(ostream& stream, const BigNumber& object_)
{
   if (object_.size > 0)
   {
      for (size_t i = object_.size - 1; i > 0; i--)
      {
         stream << object_[i];
      }
      // Отдельно, т.к. если i >= 0, то тип size_t будет заменять отрицательные числа на 0 
      // и получится, что 0 - 1 = 0 -> продолжаем цикл
      stream << object_[0];
   }

   return stream;
}

istream& operator>>(istream& stream, BigNumber& object_)
{
   short* mercy = new short[object_.size];
   for (size_t i = 0; i < object_.size; i++)
      mercy[i] = object_[i];
   size_t mercy_size = object_.size;
   size_t mercy_capacity = object_.capacity;

   if (object_.size != 0)
      object_.Clear();

   object_.number = new short[100];

   char digit[2];

   while (stream.peek() != '\n')
   {
      stream.get(digit, 2);
      if (digit[0] < '0' || digit[0] > '9')
      {
         stream.clear();
         stream.setstate(ios::badbit);

         delete[] object_.number;
         object_.number = new short[mercy_capacity];
         for (size_t i = 0; i < mercy_size; i++)
            object_[i] = mercy[i];
         
         object_.size = mercy_size;
         object_.capacity = mercy_capacity;
         cerr << "Corraption input!";
         return stream;
      }

      object_.Number_Shift(1);

      object_[0] = digit[0] - '0';
   }
   stream.ignore();//Игнорируем \n

   return stream;
}


