#include "BigNumber.h"

BigNumber::BigNumber(size_t new_capacity_)
{
   number = new short[new_capacity_];
   capacity = new_capacity_;
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
   //убрать ошибку С6386 Переполнение буфера при записи в "number".
   if (other_.size <= other_.capacity)
      number = new short[other_.capacity];
   else 
      number = new short[other_.size];


   for (size_t i = 0; i < other_.size; i++)
      number[i] = other_[i];

}

void BigNumber::Set_Number(const short* new_number_)
{
   Clear();

   size_t i = 0;

   while (new_number_[i] != '\0')
   {
      if (size == capacity)
         Expansion();

      number[i] = new_number_[i];
   }
}

void BigNumber::Set_Number(const short* new_number_, size_t new_size_)
{
   if (size != new_size_)
   {
      Clear();
      Expansion(new_size_);
      size = new_size_;
   }

   for (size_t i = 0; i < new_size_; i++)
   {
      number[i] = new_number_[i];
   }
}

void BigNumber::Set_Capacity(const size_t new_capacity_)
{
   capacity = new_capacity_;
}

void BigNumber::Set_Size(const size_t new_size_)
{
   size = new_size_;
}

short* BigNumber::Get_Number() const
{
   return number;
}

size_t BigNumber::Get_Capacity() const
{
   return capacity;
}

size_t BigNumber::Get_Size() const
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

BigNumber::operator bool() const
{
   return (size > 1 || (size == 1 && number[0] != 0));
}

BigNumber& BigNumber::operator++()
{
   if (size == 0)
   {
      number = new short[100];
      size = 1;
      capacity = 100;
      number[0] = 1;
   }
   short s_one[1] = { 1 };
   BigNumber one(s_one, 1);
   (*this) = (*this) + one;
   return *this;
}

BigNumber BigNumber::operator++(int)
{
   if (size == 0)
   {
      number = new short[100];
      size = 1;
      capacity = 100;
      number[0] = 1;
   }
   BigNumber temp = (*this);
   short s_one[1] = { 1 };
   BigNumber one(s_one, 1);
   (*this) = (*this) + one;
   return temp;
}

BigNumber& BigNumber::operator--()
{
   if (size == 0)
   {
      number = new short[100];
      size = 1;
      capacity = 100;
      number[0] = 0;
   }
   short s_one[1] = { 1 };
   BigNumber one(s_one, 1);
   (*this) = (*this) - one;
   return *this;
}

BigNumber BigNumber::operator--(int)
{
   if (size == 0)
   {
      number = new short[100];
      size = 1;
      capacity = 100;
      number[0] = 0;
   }
   BigNumber temp = (*this);
   short s_one[1] = { 1 };
   BigNumber one(s_one, 1);
   (*this) = (*this) - one;
   return temp;
}

BigNumber& BigNumber::operator=(const BigNumber& other_)
{
   if (other_.size >= capacity)
   {
      this->Clear();
      capacity = other_.capacity;
      //убрать ошибку С6386 Переполнение буфера при записи в "number".
      if (other_.size <= other_.capacity)
         number = new short[other_.capacity];
      else
         number = new short[other_.size];
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
   BigNumber* min_number = (size > other_.size ? &other_: this);


   //Выбираем где больше места + 1, чтобы не трогать Expansion 
   //Можно было реализовать и с *max_number, но тогда нужно было бы делать расширение, а это менее эффективно
   BigNumber result((max_number ->capacity) + 1);
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
   if (size == 0 || other_.size == 0)
   {
      BigNumber result;
      result.number[0] = 0;
      result.size = 1;
      return result;
   }
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
   if (*this <= other_)
   {
      BigNumber result(1);
      result[0] = 0;
      result.size = 1;
      return result;
   }

   if (other_.size == 0 || (other_.size == 1 && other_[0] == 0))
   {
      BigNumber result(*this);
      return result;
   }
   
   BigNumber* max_number = this;
   BigNumber* min_number = &other_;
   
   BigNumber result(*max_number);

   short subdigit = 0;

   for (size_t i = 0; i < min_number->size; i++)
   {
      result[i] = (*max_number)[i] - (*min_number)[i] - subdigit;
      if (result[i] < 0)
      {
         subdigit = 1;
         result[i] = 10 + result[i];
      }
      else 
         subdigit = 0;
   }

   for (size_t i = min_number->size; i < max_number->size && subdigit; i++)
   {
      result[i] = (*max_number)[i] - subdigit;
      if (result[i] < 0)
      {
         subdigit = 1;
         result[i] = 10 + result[i];
      }
      else
         subdigit = 0;
   }

   for (size_t i = size - 1; i > 0 && result[i] == 0; i--)
      result.size--;

   return result;
}

BigNumber BigNumber::operator/(BigNumber& other_)
{
   if (*this < other_ || other_.size == 0)
   {
      BigNumber result(1);
      result[0] = 0;
      result.size = 1;
      return result;
   }

   if (other_.size == 1 && other_.number[0] == 0)
   {
      throw "You can't divide by zero";
   }

   BigNumber dividend(*this);
   BigNumber* divider = &other_;

   BigNumber result;
   result[0] = 0;
   result.size = 1;

   while (dividend)
   {
      result++;
      dividend = (dividend - (*divider));
   }
   return result;
}

BigNumber BigNumber::operator%(BigNumber& other_)
{
   if (*this < other_)
   {
      BigNumber result(1);
      result[0] = 0;
      result.size = 1;
      return result;
   }

   BigNumber dividend(*this);
   BigNumber* divider = &other_;

   BigNumber result;
   result[0] = 0;
   result.size = 1;

   BigNumber zero;
   zero[0] = 0;
   zero.size = 1;

   while (dividend)
   {
      result = dividend;
      dividend = (dividend - (*divider));
   }

   return ((result == (*divider)) ? zero : result);
}

bool BigNumber::operator!()
{
   return (!size || (size <= 1 && number[0] == 0));
}

bool BigNumber::operator<(BigNumber& other_)
{
   if (this == &other_)
      return false;

   if (size != other_.size)
      return size < other_.size;
   for (size_t i = size; i > 0; i--)
   {
      if (number[i - 1] != other_[i - 1])
         return number[i - 1] < other_[i - 1];
   }

   return false;
}

bool BigNumber::operator==(BigNumber& other_)
{
   if (this == &other_)
      return true;

   if (size != other_.size)
      return false;
   for (size_t i = size; i > 0; i--)
   {
      if (number[i - 1] != other_[i - 1])
         return false;
   }

   return true;
}

bool BigNumber::operator<=(BigNumber& other_)
{
   if (this == &other_)
      return true;

   if (size != other_.size)
      return size < other_.size;
   for (size_t i = size; i > 0; i--)
   {
      if (number[i - 1] != other_[i - 1])
         return number[i - 1] < other_[i - 1];
   }

   return true;
}

bool BigNumber::operator>(BigNumber& other_)
{
   if (this == &other_)
      return false;

   if (size != other_.size)
      return size > other_.size;
   for (size_t i = size; i > 0; i--)
   {
      if (number[i - 1] != other_[i - 1])
         return number[i - 1] > other_[i - 1];
   }

   return false;
}

bool BigNumber::operator>=(BigNumber& other_)
{
   if (this == &other_)
      return true;

   if (size != other_.size)
      return size > other_.size;
   for (size_t i = size; i > 0; i--)
   {
      if (number[i - 1] != other_[i - 1])
         return number[i - 1] > other_[i - 1];
   }

   return true;
}

bool BigNumber::operator!=(BigNumber& other_)
{
   return !(*this == other_);
}

//bool BigNumber::operator<(short digit_)
//{
//   if (digit_ < 0 || digit_ > 9)
//      throw "Wrong digit";
//   return (size == 1 && number[0] < digit_);
//}
//
//bool BigNumber::operator==(short digit_)
//{
//   if (digit_ < 0 || digit_ > 9)
//      throw "Wrong digit";
//   return (size == 1 && number[0] == digit_);
//}
//
//bool BigNumber::operator<=(short digit_)
//{
//   if (digit_ < 0 || digit_ > 9)
//      throw "Wrong digit";
//   return (size == 1 && number[0] <= digit_);
//}
//
//bool BigNumber::operator>(short digit_)
//{
//   if (digit_ < 0 || digit_ > 9)
//      throw "Wrong digit";
//   return (size == 1 && number[0] > digit_);
//}
//
//bool BigNumber::operator>=(short digit_)
//{
//   if (digit_ < 0 || digit_ > 9)
//      throw "Wrong digit";
//   return (size == 1 && number[0] >= digit_);
//}
//
//bool BigNumber::operator!=(short digit_)
//{
//   if (digit_ < 0 || digit_ > 9)
//      throw "Wrong digit";
//   return (size == 1 && number[0] != digit_);
//}


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

void BigNumber::Push_Back(short digit_)
{
   if (digit_ < '0' || digit_ > '9')
      throw "Wrong digit";

   Number_Shift(1);
   number[0] = digit_;
}

void BigNumber::Push_Back(short* digit_, size_t size_)
{
   for (size_t i = 0; i < size_; i++)//Итератор
   {
      if (digit_[i] < '0' || digit_[i] > '9')
         throw "Wrong digit";
   }
   Number_Shift(size_);
   for (size_t i = 0; i < size_; i++)
   {
      number[i] = digit_[i];
   }
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

void BigNumber::Expansion(size_t new_capacity_)
{
   if (new_capacity_ <= capacity)
      return;

   short* temp_arr = new short[size];

   for (size_t i = 0; i < size; i++)
      temp_arr[i] = number[i];

   
   number = new short[new_capacity_];
   capacity = new_capacity_;

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


